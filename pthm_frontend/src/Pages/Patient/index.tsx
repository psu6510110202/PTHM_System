import { Typography, Box } from "@mui/material";
import { Grid2 } from "@mui/material"; // Ensure you import Grid2
import { BodyTempCard, HeartRateCard, BloodOxygenCard, ECGCard, PatientInfoCard, RoomEnvCard } from "../../Components";
import { useState, useEffect, useRef } from "react";
import { useLocation } from "react-router-dom";
import PatientInfoModel from "../../Models/PatientInfoModel";
import SensorInfoModel from "../../Models/SensorInfoModel";
import Repo from "../../Repositories";
import { userData } from "../../Helper";

export const Patient = () => {
  const [patients, setPatients] = useState<PatientInfoModel[]>([]);
  const [sensors, setSensors] = useState<SensorInfoModel[]>([]);
  const location = useLocation();
  const patientId = location.state?.patientId;
  const user = userData();

  const fetchPatients = async () => {
      try {
          const response = await Repo.PatientInfoRepository.getById(patientId, user.jwt);
          if (response) {
              setPatients([response]);
          }
      } catch (error) {
          console.error("Error fetching patients:", error);
          setPatients([]);
      }
  };

  const fetchSensors = async () => {
      try {
          const response = await Repo.SensorRepository.getByPatientId(patientId, user.jwt);
          if (response) {
              setSensors([response]);
          }
      } catch (error) {
          console.error("Error fetching sensors:", error);
          setSensors([]); // Corrected from setPatients([])
      }
  };

  const intervalRef = useRef<NodeJS.Timeout | number | null>(null);

  useEffect(() => {
      if (!patientId) return;
      
      fetchPatients();
      fetchSensors();

      intervalRef.current = setInterval(() => {
          fetchPatients();
          fetchSensors();
      }, 10000);

      return () => {
          if (intervalRef.current) clearInterval(intervalRef.current);
      };
  }, [patientId]); // Ensure it only runs when patientId changes

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
            <ECGCard bpm={sensors[0]?.heart_rate} />
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

      <Grid2 size={{ xs: 12 }}>
        <Box
            sx={{
            display: "flex",
            flexDirection: "column",
            alignItems: "center",
            mt: 4,
            width: "100%",
            }}
        >
            {/* Camera Stream Title */}
            <Typography variant="h5" fontWeight="bold" mb={2} sx={{ color: "#333" }}>
            Live Patient Camera Stream
            </Typography>

            {/* Styled Camera Stream Box */}
            <Box
            sx={{
                display: "flex",
                justifyContent: "center",
                alignItems: "center",
                backgroundColor: "#f9f9f9", // Light grey background
                borderRadius: "12px",
                boxShadow: "0px 4px 10px rgba(0, 0, 0, 0.1)", // Soft shadow
                padding: 2,
                maxWidth: "1000px",
                width: "100%",
            }}
            >
            { sensors[0]?.camera && (
                <img
                    src={sensors[0].camera} // Ensure it only renders when a valid URL exists
                    alt="Live Video Stream"
                    style={{
                        width: "100%",
                        borderRadius: "8px",
                        border: "2px solid #ddd", // Subtle border
                    }}
                />
            )}
            </Box>
        </Box>
      </Grid2>
    </Box>
  );
};
