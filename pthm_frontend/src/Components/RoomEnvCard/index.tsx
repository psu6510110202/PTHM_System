import { Card, Typography, Stack, Box } from "@mui/material";
import { styled } from "@mui/material/styles";

const StyledRoomCard = styled(Card)(({ theme }) => ({
  borderRadius: theme.shape.borderRadius * 2, // Rounded corners
  padding: theme.spacing(4), // Padding for larger card
  boxShadow: "0px 8px 20px rgba(0, 0, 0, 0.1)", // Smooth shadow
  maxWidth: 385, // Card width
  display: "flex",
  flexDirection: "column",
  alignItems: "center",
  justifyContent: "center",
  background: "white", // White background
}));

export const RoomEnvCard: React.FC<{ temperature: number; humidity: number }> = ({ temperature, humidity }) => {
  return (
    <StyledRoomCard>
      <Stack spacing={4} alignItems="center"> {/* Increased spacing between elements */}  
        {/* Room Condition Title */}
        <Typography variant="h5" fontWeight={700} color="primary">
          Room Conditions
        </Typography>

        {/* Temperature Display */}
        <Stack direction="row" spacing={4} alignItems="center">
          {/* Thermometer Icon */}
          <Box>
            <img src="/room_temp.png" alt="Temperature Icon" style={{ width: 75, height: 75 }} /> {/* Thermometer icon */}
          </Box>

          {/* Temperature Value */}
          <Typography variant="h2" fontWeight={700} color="text.primary">
            {temperature}°C
          </Typography>
        </Stack>

        {/* Humidity Display */}
        <Stack direction="row" spacing={4} alignItems="center">
          {/* Humidity Icon */}
          <Box>
            <img src="/room_humidity.png" alt="Humidity Icon" style={{ width: 75, height: 75 }} /> {/* Humidity drop icon */}
          </Box>

          {/* Humidity Value */}
          <Typography variant="h2" fontWeight={700} color="text.primary">
            {humidity}%
          </Typography>
        </Stack>

        {/* Labels */}
        <Typography variant="body1" fontWeight={500} color="text.secondary" mt={4}>
          Room Temperature & Humidity
        </Typography>
      </Stack>
    </StyledRoomCard>
  );
};
