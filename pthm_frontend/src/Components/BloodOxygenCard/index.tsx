import { Card, Typography, Stack, Box } from "@mui/material";
import { styled } from "@mui/material/styles";

const StyledBloodOxygenCard = styled(Card)(({ theme }) => ({
  borderRadius: theme.shape.borderRadius * 2, // Rounded corners
  padding: theme.spacing(4), // Increase padding for a larger card
  boxShadow: "0px 8px 20px rgba(0, 0, 0, 0.1)", // Shadow for emphasis
  maxWidth: 450, // Increase card width for larger content
  display: "flex",
  flexDirection: "column",
  alignItems: "center",
  justifyContent: "center",
  background: "white", // Background color
}));

export const BloodOxygenCard: React.FC<{ bloodOxygen: number }> = ({ bloodOxygen }) => {
  return (
    <StyledBloodOxygenCard>
      <Stack spacing={6} alignItems="center"> {/* Increased spacing between elements */}
        {/* Heart Rate Monitoring Title */}
        <Typography variant="h5" fontWeight={700} color="primary" >
          Blood Oxygen Monitoring
        </Typography>

        {/* Row layout for heart icon and heart rate value */}
        <Stack direction="row" spacing={4} alignItems="center"> {/* Increased spacing between the icon and value */}
          {/* Heart Icon Placeholder */}
          <Box>
            <img src="/blood_oxygen.png" alt="Blood Icon" style={{ width: 100, height: 100 }} /> {/* Larger heart icon */}
          </Box>

          {/* Heart Rate Value */}
          <Typography variant="h1" fontWeight={700} color="text.primary">
            {bloodOxygen}
          </Typography> {/* Larger heart rate value */}
        </Stack>

        {/* Beats Per Minute Label */}
        <Typography variant="body1" fontWeight={500} color="text.secondary" mt={4}> {/* Added margin-top for extra space */}
         Percent of SpO2
        </Typography>
      </Stack>
    </StyledBloodOxygenCard>
  );
};
