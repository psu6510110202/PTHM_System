import { Typography, Box } from "@mui/material";
import { Grid2 } from "@mui/material"; // Ensure you import Grid2
import { BodyTempCard, HeartRateCard, BloodOxygenCard, ECGCard, PatientInfoCard } from "../../Components";
import { useState, useEffect } from "react";

export const Patient = () => {
  const [ecgData, setEcgData] = useState<number[]>([]);

  const generateECGWaveform = (t: number) => {
    const heartRate = 1.2; // Simulate a heart rate factor (affects frequency of the wave)
  
    // P-wave: small, smooth wave before the QRS complex
    const pWave = Math.sin(t * heartRate * 0.3) * 1.5;
  
    // QRS complex: sharp, large spike (Q wave down, R wave up, S wave down)
    const qrsComplex =
      Math.sin(t * heartRate * 2) * 15 * Math.exp(-Math.pow(t % 50 - 25, 2) / 50);
  
    // T-wave: larger smooth wave after the QRS complex
    const tWave = Math.sin(t * heartRate * 0.15) * 4;
  
    // Baseline wander and random noise
    const baselineWander = Math.sin(t * heartRate * 0.02) * 0.5; // slow baseline drift
    const noise = (Math.random() - 0.5) * 0.5;
  
    return pWave + qrsComplex + tWave + baselineWander + noise;
  };
  
  

  useEffect(() => {
    let t = 0; // Time step
    const interval = setInterval(() => {
      setEcgData((prev) => [
        ...prev.slice(-99), // Keep the last 100 values
        generateECGWaveform(t), // Use a function to generate ECG-like waves
      ]);
      t += 1;
    }, 10); // Faster updates for a smoother look
  
    return () => clearInterval(interval);
  }, []);
  

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
                  Monitoring on Patient ID : 000001
              </Typography>
          </Box>
      </Box>
      <Grid2 container spacing={3} justifyContent="center">
        <Grid2 size={{ xs: 12, sm: 6, md: 4 }}>
          <BodyTempCard temperature={36.2} minTemp={35} maxTemp={40} />
        </Grid2>
        <Grid2 size={{ xs: 12, sm: 6, md: 4 }}>
          <HeartRateCard heartRate={140} />
        </Grid2>
        <Grid2 size={{ xs: 12, sm: 6, md: 4 }}>
          <BloodOxygenCard bloodOxygen={98.67} />
        </Grid2>
      </Grid2>
      <Box sx={{ flexGrow: 1, mt: 4 }}>
        <Grid2 container spacing={4} justifyContent="center" alignItems="start">
          {/* ECG Card - Takes More Space */}
          <Grid2 size={{xs:12, md:8}}>
            <ECGCard ecgData={ecgData} />
          </Grid2>

          {/* Patient Info Card - Takes Less Space */}
          <Grid2 size={{xs:12, md:4}}>
            <PatientInfoCard
              patientId="xxxxx1"
              name="Mr. John ABC"
              age={59}
              gender="Male"
              phone="xxx-xxx-xxxx"
              email="john.abc@gmail.com"
              address="14/29 Gp 7 Phetkasem Nong Klang Ploo Nong Khaem"
              doctor="Dr. Smith ABC"
              room="4405"
            />
          </Grid2>
        </Grid2>
      </Box>

    </Box>
  );
};
