import { LocalHospital, NotificationsActive, Warning, Shield } from "@mui/icons-material";
import { DashboardMetricCard, DashboardPatientCard } from "../../Components";
import { Grid2, Box, Typography } from "@mui/material";
import PatientDashboard from "../../Models/PatientDashboard";
import SensorDashboard from "../../Models/SensorDashboard";
import { useState, useEffect, useRef } from "react";
import Repo from "../../Repositories";
import { userData } from "../../Helper";

type RiskCount = {
    Normal: number;
    Risk: number;
    Critical: number;
    All: number;
};

type PatientWithRisk = PatientDashboard & {
    risk: string;
    status: string;
};

export const Dashboard = () => {
    const [patients, setPatients] = useState<PatientDashboard[]>([]);
    const [sensors, setSensors] = useState<SensorDashboard[]>([]);
    const user = userData();

    const fetchPatients = async () => {
        try {
            const response = await Repo.PatientRepository.getAll(user.jwt);
            if(response){
                setPatients(response);
            }
        } catch (error) {
            console.error("Error fetching patients:", error);
            setPatients([]); // Set to empty array on failure
        }
    };

    const fetchSensors = async () => {
        try {
            const response = await Repo.SensorRepository.getAll(user.jwt);
            if(response){
                setSensors(response);
                console
            }
        } catch (error) {
            console.error("Error fetching sensors:", error);
            setSensors([]); // Set to empty array on failure
        }
    };

    const intervalRef = useRef<number | null>(null);

    useEffect(() => {
        fetchPatients();
        fetchSensors();

        intervalRef.current = setInterval(() => {
            fetchPatients();
            fetchSensors();
        }, 3000);

        return () => {
            if (intervalRef.current) clearInterval(intervalRef.current);
        };
    }, []);

    const categorizeCase = (
        heart_rate: number,
        body_temp: number,
        room_temp: number,
        room_humidity: number,
        blood_oxy: number, // Added blood oxygen level
        updatedAt: string // ISO timestamp format (e.g., "2025-02-08T14:46:58.705Z")
    ): string => {
    
        // Calculate time difference in minutes
        const updatedAtTime = new Date(updatedAt).getTime();
        const currentTime = new Date().getTime();
        const timeDifferenceMinutes = (currentTime - updatedAtTime) / 60000; // Convert milliseconds to minutes
    
        // 🚨 If data is older than 2 minutes, mark as Critical
        if (timeDifferenceMinutes > 2) {
            return "Critical";
        }
    
        // Critical conditions (life-threatening)
        if (
            (heart_rate < 40 || heart_rate > 120) || // Critical HR thresholds
            (body_temp < 35.5 || body_temp > 38.5) || // Critical body temperature
            (room_temp < 10 || room_temp > 35) || // Extreme room temperature
            (room_humidity < 20 || room_humidity > 75) || // Extreme humidity
            (blood_oxy < 90) // 🚨 Critical blood oxygen level
        ) {
            return "Critical";
        } 
        // Risk conditions (borderline abnormal)
        else if (
            ((heart_rate < 50 && heart_rate >= 40) || (heart_rate > 100 && heart_rate <= 120)) || // Risk HR range
            ((body_temp < 36.1 && body_temp >= 35.5) || (body_temp > 37.5 && body_temp <= 38.5)) || // Risk temp range
            ((room_temp < 18 && room_temp >= 10) || (room_temp > 30 && room_temp <= 35)) || // Risk room temp
            ((room_humidity < 30 && room_humidity >= 20) || (room_humidity > 60 && room_humidity <= 75)) || // Risk humidity
            (blood_oxy >= 90 && blood_oxy < 95) // ⚠️ Risky blood oxygen level
        ) {
            return "Risk";
        } 
        // Normal conditions
        else {
            return "Normal";
        }
    };
    

    const getUpdatedPatients = (): PatientWithRisk[] => {
        if (!Array.isArray(patients) || patients.length === 0) return []; // Ensure it's an array
    
        return patients.map(patient => {
            const sensorData = sensors.find(sensor => sensor.patient_id === patient.patient_id);
    
            if (!sensorData) {
                return {
                    ...patient,
                    risk: "Unknown",
                    status: "offline"
                };
            }
    
            const updatedAtTime = new Date(sensorData.updatedAt).getTime(); // ✅ Convert string to Date
            const currentTime = new Date().getTime();
            const timeDifferenceMinutes = (currentTime - updatedAtTime) / 60000;
    
            const isOffline = timeDifferenceMinutes > 2;
            
            const riskLevel = categorizeCase(
                sensorData.heart_rate,
                sensorData.body_temp,
                sensorData.room_temp,
                sensorData.room_humidity,
                sensorData.blood_oxy,
                new Date(sensorData.updatedAt).toISOString() // ✅ Convert string to Date before using .toISOString()
            );
    
            return {
                ...patient,
                risk: riskLevel,
                status: isOffline ? "offline" : "online"
            };
        });
    };
    
    
    
    // 🚀 Use the function
    const patientsWithUpdatedRisk: PatientWithRisk[] = getUpdatedPatients();


    // Counting Cases with Proper Typing
    const countCases = (): RiskCount => {
        return patientsWithUpdatedRisk.reduce(
            (acc: RiskCount, patient) => {
                acc[patient.risk as keyof RiskCount] += 1; // Type assertion ensures correct indexing
                acc["All"] += 1;
                return acc;
            },
            { Normal: 0, Risk: 0, Critical: 0, All: 0 } // Initial values
        );
    };

    const caseCounts = countCases();

    const sortedPatients = [...patientsWithUpdatedRisk]
    .map(patient => ({
        ...patient,
        priority: patient.risk === "Critical" ? 0 : patient.risk === "Risk" ? 1 : patient.risk === "Normal" ? 2 : 3,
    }))
    .sort((a, b) => a.priority - b.priority);

    return (
        <>
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
                    <Typography variant="h5" fontWeight="bold">
                        Welcome {user.username} to PTHM System
                    </Typography>
                </Box>
            </Box>


            <Grid2 container spacing={8} justifyContent="center">
                <Grid2>
                    <DashboardMetricCard 
                        icon={<LocalHospital sx={{ fontSize: 100 }} />} 
                        count={caseCounts.All} 
                        label="Total Patient" 
                    />
                </Grid2>
                <Grid2>
                    <DashboardMetricCard 
                        icon={<NotificationsActive sx={{ fontSize: 100 }} />} 
                        count={caseCounts.Critical} 
                        label="Critical Case" 
                        bgcolor="#FF3D3D" 
                    />
                </Grid2>
                <Grid2 >
                    <DashboardMetricCard 
                        icon={<Warning sx={{ fontSize: 100 }} />} 
                        count={caseCounts.Risk} 
                        label="Risk Case" 
                        bgcolor="#FF6A00" 
                    />
                </Grid2>
                <Grid2>
                    <DashboardMetricCard 
                        icon={<Shield sx={{ fontSize: 100 }} />} 
                        count={caseCounts.Normal} 
                        label="Normal Case" 
                        bgcolor="#43A047" // Slightly softer green
                    />
                </Grid2>
            </Grid2>
            <Box 
                mt={4} 
                p={2} 
                sx={{ 
                    backgroundColor: "#FFF", 
                    borderRadius: 4, 
                    boxShadow: "0px 2px 8px rgba(0, 0, 0, 0.1)",
                    marginBottom: 3
                }}
            >
                <Box display="flex" alignItems="center" justifyContent="space-between">
                    <Typography variant="body1" fontWeight="bold">
                        All Patients
                    </Typography>
                    <Box display="flex" alignItems="center" gap={1}>
                        <Typography variant="body2" sx={{ cursor: "pointer" }}>1</Typography>
                        <Typography variant="body2" sx={{ cursor: "pointer" }}>2</Typography>
                        <Typography variant="body2" sx={{ cursor: "pointer" }}>{">>"}</Typography>
                    </Box>
                </Box>
            </Box>
            
            <Grid2 container spacing={4}>
                {sortedPatients.map((patient, index) => (
                    <Grid2 
                        key={index} 
                        size={{
                            xs: 12,  // Full width on extra small screens
                            sm: 6,   // Half width on small screens
                            md: 4,   // One-third width on medium screens
                            lg: 3,   // One-fourth width on large screens
                        }}
                    >   
                        <DashboardPatientCard
                            patient_id={patient.patient_id}
                            first_name={patient.first_name}
                            last_name={patient.last_name}
                            gender={patient.gender}
                            age={patient.age}
                            room={patient.room}
                            status={patient.status}
                            risk={patient.risk}
                        />
                    </Grid2>
                ))}
            </Grid2>
        </>
    );
};
