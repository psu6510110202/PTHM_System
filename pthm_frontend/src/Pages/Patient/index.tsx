import { Typography, Box } from "@mui/material";
import { Grid2 } from "@mui/material"; // Ensure you import Grid2
import { BodyTempCard, HeartRateCard, BloodOxygenCard, ECGCard, PatientInfoCard, RoomEnvCard } from "../../Components";
import { useState, useEffect, useRef } from "react";
import { useLocation } from "react-router-dom";
import PatientInfoModel from "../../Models/PatientInfoModel";
import SensorInfoModel from "../../Models/SensorInfoModel";
import Repo from "../../Repositories";
import { userData } from "../../Helper";
import mqtt from "mqtt"; // Import MQTT.js



export const Patient = () => {
  const [ecgData, setEcgData] = useState<number[]>([]);
  const [patients, setPatients] = useState<PatientInfoModel[]>([]);
  const [sensors, setSensors] = useState<SensorInfoModel[]>([]);
  const location = useLocation();
  const patientId = location.state?.patientId; // Retrieve the patient ID from state
  const user = userData();
  
  const fetchPatients = async () => {
    try {
        const response = await Repo.PatientInfoRepository.getById(patientId ,user.jwt);
        if(response){
            setPatients([response]);
        }
    } catch (error) {
        console.error("Error fetching patients:", error);
        setPatients([]); // Set to empty array on failure
    }
  };

  const fetchSensors = async () => {
    try {
        const response = await Repo.SensorRepository.getByPatientId(patientId ,user.jwt);
        if(response){
            setSensors([response]);
        }
    } catch (error) {
        console.error("Error fetching patients:", error);
        setPatients([]); // Set to empty array on failure
    }
  };


  const intervalRef = useRef<NodeJS.Timeout | number | null>(null);
  
  useEffect(() => {
      fetchPatients();
      fetchSensors();
      intervalRef.current = setInterval(() => {
          fetchPatients();
          fetchSensors();
      }, 5000);

      return () => {
          if (intervalRef.current) clearInterval(intervalRef.current);
      };
  }, []);

  const mqttClientRef = useRef<mqtt.MqttClient | null>(null);

  useEffect(() => {
    if (!patientId) return;
  
    // If the MQTT client already exists, subscribe only
    if (!mqttClientRef.current) {
      const mqttBrokerUrl = "ws://localhost:9001"; // Change to your broker
      const client = mqtt.connect(mqttBrokerUrl, {
        clientId: `ecg-client-${Math.random().toString(16).slice(2, 10)}`,
        clean: true,
        reconnectPeriod: 1000, // Adjust to prevent aggressive reconnections
      });
  
      mqttClientRef.current = client;
  
      client.on("connect", () => {
        console.log("MQTT Connected");
      });
  
      client.on("error", (err) => {
        console.error("MQTT Error:", err);
      });
    }
  
    const topic = `ecg/patient/${patientId}`;
  
    // Subscribe to the ECG topic
    mqttClientRef.current.subscribe(topic, (err) => {
      if (err) {
        console.error("MQTT Subscription Error:", err);
      }
    });
    
    const handleMessage = (receivedTopic: string, message: Buffer) => {
      if (receivedTopic === topic) {
        try {
          const jsonMessage = JSON.parse(message.toString());
          const ecgValue = jsonMessage.value;
  
          if (typeof ecgValue === "number") {
            // Only update state every 5 messages to reduce load
            setEcgData((prev) => [...prev.slice(-125), ecgValue]);
          }
        } catch (err) {
          console.error("Error parsing ECG JSON data:", err);
        }
      }
    };
  
    mqttClientRef.current.on("message", handleMessage);
  
    return () => {
      if (mqttClientRef.current) {
        console.log(`Unsubscribing from ${topic}`);
  
        mqttClientRef.current.removeListener("message", handleMessage);
        mqttClientRef.current.unsubscribe(topic, () => {
          console.log(`Unsubscribed from ${topic}`);
        });
  
        console.log("Disconnecting MQTT client...");
        mqttClientRef.current.end(true, () => {
          console.log("MQTT client fully disconnected");
        });
  
        mqttClientRef.current = null;
      }
    };
  }, [patientId]);
  
  
  

  

  // useEffect(() => {
  //   let t = 0; // Time step
  //   const interval = setInterval(() => {
  //     setEcgData((prev) => [
  //       ...prev.slice(-99), // Keep the last 100 values
  //       generateECGWaveform(t), // Use a function to generate ECG-like waves
  //     ]);
  //     t += 1;
  //   }, 10); // Faster updates for a smoother look
  
  //   return () => clearInterval(interval);
  // }, []);

  return (
    <Box sx={{ p: 4 }}>
      <Box display="flex" justifyContent="center" mb={3}>
          <Box 
              sx={{ 
                  display: "flex", 
                  alignItems: "center", 
                  justifyContent: "center", 
                  backgroundColor: "#FFF", // Light blue background
                  paddingX: 4, // Horizontal padding for width
                  paddingY: 2, // Vertical padding for height
                  borderRadius: 20, // Rounded corners
              }}
          >
              <Typography variant="h4" fontWeight="bold">
                  Monitoring on Patient ID : {patientId}
              </Typography>
          </Box>
      </Box>
      <Box display="flex" justifyContent="center" gap={5} flexWrap="wrap">
        <BodyTempCard temperature={sensors[0]?.body_temp} minTemp={28} maxTemp={45} />
        <HeartRateCard heartRate={sensors[0]?.heart_rate} />
        <BloodOxygenCard bloodOxygen={sensors[0]?.blood_oxy} />
        <RoomEnvCard temperature={sensors[0]?.room_temp} humidity={sensors[0]?.room_humidity} />
      </Box>
      <Box sx={{ flexGrow: 1, mt: 4 }}>
        <Grid2 container spacing={4} justifyContent="center" alignItems="start">
          {/* ECG Card - Takes More Space */}
          <Grid2 size={{xs:12, md:8}}>
            <ECGCard ecgData={ecgData} />
          </Grid2>

          {/* Patient Info Card - Takes Less Space */}
          <Grid2 size={{xs:12, md:4}}>
            <PatientInfoCard
              patient_id={patients[0]?.patient_id}
              first_name={patients[0]?.first_name}
              last_name={patients[0]?.last_name}
              age={patients[0]?.age}
              gender={patients[0]?.gender}
              family_phone={patients[0]?.family_phone}
              family_email={patients[0]?.family_email}
              address={patients[0]?.address}
              doctor_name={patients[0]?.doctor_name}
              room={patients[0]?.room}
            />
          </Grid2>
        </Grid2>
      </Box>

    </Box>
  );
};
