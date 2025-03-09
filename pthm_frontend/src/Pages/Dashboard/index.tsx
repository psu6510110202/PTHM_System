import { LocalHospital, NotificationsActive, Warning, Shield, Search } from "@mui/icons-material";
import { DashboardMetricCard, DashboardPatientCard } from "../../Components";
import { Grid2, Box, Typography, TextField, InputAdornment } from "@mui/material";
import PatientDashboard from "../../Models/PatientDashboard";
import { useState, useEffect, useRef } from "react";
import Repo from "../../Repositories";
import { userData } from "../../Helper";
import SensorInfoModel from "../../Models/SensorInfoModel";

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
    const [sensors, setSensors] = useState<SensorInfoModel[]>([]);
    const [searchQuery, setSearchQuery] = useState("");
    const [currentPage, setCurrentPage] = useState(1);
    const patientsPerPage = 12;
    const user = userData();

    const fetchPatients = async () => {
        try {
            const response = await Repo.PatientDashboardRepository.getAll(user.jwt);
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

    const categorizeCase = (
        heart_rate: number,
        body_temp: number,
        room_temp: number,
        room_humidity: number,
        blood_oxy: number, // Added blood oxygen level
        updatedAt: string // ISO timestamp format (e.g., "2025-02-08T14:46:58.705Z")
    ): string => {
    
        const updatedAtTime = new Date(updatedAt).getTime();
        const currentTime = new Date().getTime(); // This gets local time like Date.now()
        const utcOffset = 7 * 60 * 60000; // UTC+7 offset in milliseconds
        const updatedAtLocal = updatedAtTime + utcOffset;
        const timeDifferenceMinutes = (currentTime - updatedAtLocal) / 60000; // Convert milliseconds to minutes

        // 🚨 If data is older than 2 minutes, mark as Critical
        if (timeDifferenceMinutes > 2) {
            return "Critical";
        }
    
        // Critical conditions (life-threatening)
        if (
            (heart_rate < 40 || heart_rate > 120) || // Critical HR thresholds
            (body_temp < 28 || body_temp > 40) || // Critical body temperature
            (room_temp < 10 || room_temp > 35) || // Extreme room temperature
            (room_humidity < 20 || room_humidity > 75) || // Extreme humidity
            (blood_oxy < 90) // 🚨 Critical blood oxygen level
        ) {
            return "Critical";
        } 
        // Risk conditions (borderline abnormal)
        else if (
            ((heart_rate < 50 && heart_rate >= 40) || (heart_rate > 100 && heart_rate <= 120)) || // Risk HR range
            ((body_temp < 35 && body_temp >= 28) || (body_temp > 37.5 && body_temp <= 40)) || // Risk temp range
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
    
    const filteredPatients = patients.filter(patient => 
        patient.first_name.toLowerCase().includes(searchQuery.toLowerCase()) ||
        patient.last_name.toLowerCase().includes(searchQuery.toLowerCase()) ||
        patient.room.toString().includes(searchQuery) ||
        patient.patient_id.toString().includes(searchQuery)
    );

    const getUpdatedPatients = (): PatientWithRisk[] => {
        if (!Array.isArray(filteredPatients) || filteredPatients.length === 0) return []; // Ensure it's an array
    
        return filteredPatients
            .filter(patient => sensors.some(sensor => sensor.patient_id === patient.patient_id)) // ✅ Filter out unmatched patients
            .map(patient => {
                const sensorData = sensors.find(sensor => sensor.patient_id === patient.patient_id);
    
                if (!sensorData) {
                    return {
                        ...patient,
                        risk: "Unknown",
                        status: "offline"
                    };
                }
    
                const updatedAtTime = new Date(sensorData.updatedAt).getTime();
                const currentTime = new Date().getTime(); // This gets local time like Date.now()
                const utcOffset = 7 * 60 * 60000; // UTC+7 offset in milliseconds
                const updatedAtLocal = updatedAtTime + utcOffset;
                const timeDifferenceMinutes = (currentTime - updatedAtLocal) / 60000; // Convert milliseconds to minutes
            
                const isOffline = timeDifferenceMinutes > 2;
                console.log(timeDifferenceMinutes + " | "+ isOffline)
    
                const riskLevel = categorizeCase(
                    sensorData.heart_rate,
                    sensorData.body_temp,
                    sensorData.room_temp,
                    sensorData.room_humidity,
                    sensorData.blood_oxy,
                    new Date(sensorData.updatedAt).toISOString()
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

    const totalPages = Math.ceil(sortedPatients.length / patientsPerPage);
    const paginatedPatients = sortedPatients.slice(
        (currentPage - 1) * patientsPerPage,
        currentPage * patientsPerPage
    );

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
                display="flex" 
                alignItems="center" 
                justifyContent="space-between" 
                gap={2} 
                p={2} 
                bgcolor="background.paper" 
                borderRadius={2} 
                boxShadow={1}
                mt={4} // Added margin-top to create space above
                mb={4} // Added margin-bottom to create space below
            >
                <Box display="flex" alignItems="center" gap={2} flex={1}>
                    <Typography variant="h6" fontWeight="bold">
                        All Patients
                    </Typography>
                    <TextField
                        fullWidth
                        variant="outlined"
                        size="small"
                        placeholder="Search by Name, Room, or ID"
                        value={searchQuery}
                        onChange={(e) => setSearchQuery(e.target.value)}
                        InputProps={{
                            startAdornment: (
                                <InputAdornment position="start">
                                    <Search color="primary" />
                                </InputAdornment>
                            ),
                            sx: { borderRadius: 2, boxShadow: "0 2px 6px rgba(0,0,0,0.1)" },
                        }}
                        sx={{ maxWidth: 300 }}
                    />
                </Box>
                <Box display="flex" justifyContent="center" mt={4} gap={1}>
                    {[...Array(totalPages)].map((_, index) => (
                        <Typography 
                            key={index} 
                            variant="body2" 
                            sx={{ cursor: "pointer", p: 1, borderRadius: 1, bgcolor: currentPage === index + 1 ? "primary.main" : "transparent", color: currentPage === index + 1 ? "white" : "black", "&:hover": { bgcolor: "action.hover" } }}
                            onClick={() => setCurrentPage(index + 1)}
                        >
                            {index + 1}
                        </Typography>
                    ))}
                </Box>
            </Box>
            
            <Grid2 container spacing={4}>
                {paginatedPatients.map((patient, index) => (
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
