import { Card, Typography, Stack, Box } from "@mui/material";
import { styled } from "@mui/material/styles";

const StyledHeartRateCard = styled(Card)(({ theme }) => ({
  borderRadius: theme.shape.borderRadius * 2, // Rounded corners
  padding: theme.spacing(4), // Increase padding for a larger card
  boxShadow: "0px 8px 20px rgba(0, 0, 0, 0.1)", // Shadow for emphasis
  maxWidth:375, // Increase card width for larger content
  display: "flex",
  flexDirection: "column",
  alignItems: "center",
  justifyContent: "center",
  background: "white", // Background color
}));

export const HeartRateCard: React.FC<{ heartRate: number }> = ({ heartRate }) => {
  return (
    <StyledHeartRateCard>
      <Stack spacing={8} alignItems="center"> {/* Increased spacing between elements */}
        {/* Heart Rate Monitoring Title */}
        <Typography variant="h5" fontWeight={700} color="primary" >
          Heart Rate Monitoring
        </Typography>

        {/* Row layout for heart icon and heart rate value */}
        <Stack direction="row" spacing={4} alignItems="center"> {/* Increased spacing between the icon and value */}
          {/* Heart Icon Placeholder */}
          <Box>
            <img src="/heart_rate.png" alt="Heart Icon" style={{ width: 125, height: 100 }} /> {/* Larger heart icon */}
          </Box>

          {/* Heart Rate Value */}
          <Typography variant="h1" fontWeight={800} color="text.primary">
            {heartRate}
          </Typography> {/* Larger heart rate value */}
        </Stack>

        {/* Beats Per Minute Label */}
        <Typography variant="body1" fontWeight={500} color="text.secondary" mt={4}> {/* Added margin-top for extra space */}
          Beats per minute (BPM)
        </Typography>
      </Stack>
    </StyledHeartRateCard>
  );
};
