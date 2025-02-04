import { LocalHospital, NotificationsActive, Warning, Shield } from "@mui/icons-material";
import { MetricCard } from "../../Components";
import { Grid2, Box, Typography } from "@mui/material";

export const Patient = () => {
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
                    <MetricCard 
                        icon={<LocalHospital sx={{ fontSize: 100 }} />} 
                        count={12} 
                        label="Total Patient" 
                    />
                </Grid2>
                <Grid2>
                    <MetricCard 
                        icon={<NotificationsActive sx={{ fontSize: 100 }} />} 
                        count={2} 
                        label="Critical Case" 
                        bgcolor="#FF3D3D" 
                    />
                </Grid2>
                <Grid2 >
                    <MetricCard 
                        icon={<Warning sx={{ fontSize: 100 }} />} 
                        count={1} 
                        label="Risk Case" 
                        bgcolor="#FF6A00" 
                    />
                </Grid2>
                <Grid2>
                    <MetricCard 
                        icon={<Shield sx={{ fontSize: 100 }} />} 
                        count={9} 
                        label="Normal Case" 
                        bgcolor="#43A047" // Slightly softer green
                    />
                </Grid2>
            </Grid2>
        </>
    );
};
