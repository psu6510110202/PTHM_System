import { LocalHospital, NotificationsActive, Warning, Shield } from "@mui/icons-material";
import { DashboardMetricCard, DashboardPatientCard } from "../../Components";
import { Grid2, Box, Typography } from "@mui/material";

export const Dashboard = () => {

    const patients = [
        {
            patientId: "P001",
            name: "Mr. John Doe",
            age: 59,
            floor: 4,
            room: 4405,
            status: "online",
            icon: <Shield sx={{ fontSize: 30, color: "#43A047" }} />,
            borderColor: "#43A047",
        },
        {
            patientId: "P002",
            name: "Ms. Jane Smith",
            age: 34,
            floor: 3,
            room: 3302,
            status: "offline",
            icon: <Warning sx={{ fontSize: 30, color: "#FF6A00" }} />,
            borderColor: "#FF6A00",
        },
        {
            patientId: "P003",
            name: "Mr. Mike Johnson",
            age: 72,
            floor: 2,
            room: 2201,
            status: "online",
            icon: <NotificationsActive sx={{ fontSize: 30, color: "#FF3D3D" }} />,
            borderColor: "#FF3D3D",
        },
        {
            patientId: "P004",
            name: "Mrs. Alice Brown",
            age: 45,
            floor: 5,
            room: 5502,
            status: "online",
            icon: <Shield sx={{ fontSize: 30, color: "#43A047" }} />,
            borderColor: "#43A047",
        },
        {
            patientId: "P001",
            name: "Mr. John Doe",
            age: 59,
            floor: 4,
            room: 4405,
            status: "online",
            icon: <Shield sx={{ fontSize: 30, color: "#43A047" }} />,
            borderColor: "#43A047",
        },
        {
            patientId: "P002",
            name: "Ms. Jane Smith",
            age: 34,
            floor: 3,
            room: 3302,
            status: "offline",
            icon: <Warning sx={{ fontSize: 30, color: "#FF6A00" }} />,
            borderColor: "#FF6A00",
        },
        {
            patientId: "P003",
            name: "Mr. Mike Johnson",
            age: 72,
            floor: 2,
            room: 2201,
            status: "online",
            icon: <NotificationsActive sx={{ fontSize: 30, color: "#FF3D3D" }} />,
            borderColor: "#FF3D3D",
        },
        {
            patientId: "P004",
            name: "Mrs. Alice Brown",
            age: 45,
            floor: 5,
            room: 5502,
            status: "online",
            icon: <Shield sx={{ fontSize: 30, color: "#43A047" }} />,
            borderColor: "#43A047",
        },
        
    ];

    const sortedPatients = [...patients]
    .map(patient => ({
        ...patient,
        borderColor: patient.status === "offline" ? "#FF3D3D" : patient.borderColor, // Turn offline patients Red
        priority: patient.status === "offline" ? 0 : patient.borderColor === "#FF3D3D" ? 1 : patient.borderColor === "#FF6A00" ? 2 : 3,
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
                        Welcome Staff to PTHM System
                    </Typography>
                </Box>
            </Box>


            <Grid2 container spacing={8} justifyContent="center">
                <Grid2>
                    <DashboardMetricCard 
                        icon={<LocalHospital sx={{ fontSize: 100 }} />} 
                        count={12} 
                        label="Total Patient" 
                    />
                </Grid2>
                <Grid2>
                    <DashboardMetricCard 
                        icon={<NotificationsActive sx={{ fontSize: 100 }} />} 
                        count={2} 
                        label="Critical Case" 
                        bgcolor="#FF3D3D" 
                    />
                </Grid2>
                <Grid2 >
                    <DashboardMetricCard 
                        icon={<Warning sx={{ fontSize: 100 }} />} 
                        count={1} 
                        label="Risk Case" 
                        bgcolor="#FF6A00" 
                    />
                </Grid2>
                <Grid2>
                    <DashboardMetricCard 
                        icon={<Shield sx={{ fontSize: 100 }} />} 
                        count={9} 
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
                            patientId={patient.patientId}
                            name={patient.name}
                            age={patient.age}
                            floor={patient.floor}
                            room={patient.room}
                            status={patient.status}
                            icon={patient.icon}
                            borderColor={patient.borderColor}
                        />
                    </Grid2>
                ))}
            </Grid2>
        </>
    );
};
