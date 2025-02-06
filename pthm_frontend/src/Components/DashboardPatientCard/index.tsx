import { Card, CardContent, Typography, Box } from "@mui/material";
import { styled } from "@mui/material/styles";

interface PatientCardProps {
  status: string; // Status can toggle between "online" or "offline"
  icon: React.ReactNode; // Icon displayed at the bottom right of the card
  patientId: string;
  name: string;
  age: number;
  floor: number;
  room: number;
  borderColor: string; // Border color based on case type (red, orange, green)
}

const StyledPatientCard = styled(Card)<{ borderColor: string }>(({ theme, borderColor }) => ({
  border: `3px solid ${borderColor}`, // Dynamic border color
  borderRadius: theme.shape.borderRadius * 2, // Rounded corners
  padding: theme.spacing(2),
  boxShadow: "0px 4px 12px rgba(0, 0, 0, 0.1)", // Subtle shadow
  maxWidth: 350, // Card width
  display: "flex",
  flexDirection: "column",
  justifyContent: "space-between",
  backgroundColor: theme.palette.background.paper,
}));

const StatusDot = styled(Box)<{ status: string }>(({ status }) => ({
  width: 10,
  height: 10,
  borderRadius: "50%",
  backgroundColor: status === "online" ? "green" : "red", // Green for online, red for offline
}));

export const DashboardPatientCard: React.FC<PatientCardProps> = ({
  status,
  icon,
  patientId,
  name,
  age,
  floor,
  room,
  borderColor,
}) => {
  return (
    <StyledPatientCard borderColor={borderColor}>
      <Box display="flex" justifyContent="space-between" alignItems="center">
        <Typography variant="subtitle2" fontWeight={600} color="text.secondary">
          Patient ID: {patientId}
        </Typography>
        <Box display="flex" alignItems="center" gap={1}>
          <StatusDot status={status} />
          <Typography variant="subtitle2" fontWeight={600} color={status === "online" ? "green" : "red"}>
            {status.charAt(0).toUpperCase() + status.slice(1)}
          </Typography>
        </Box>
      </Box>
      <CardContent sx={{ padding: 0, marginTop: 1 }}>
        <Typography variant="h6" fontWeight={700} gutterBottom>
          {name}
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Age: <Typography component="span" fontWeight={600}>{age}</Typography>
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Floor: <Typography component="span" fontWeight={600}>{floor}</Typography>
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Room: <Typography component="span" fontWeight={600}>{room}</Typography>
        </Typography>
      </CardContent>
      <Box display="flex" justifyContent="flex-end" alignItems="center">
        {icon}
      </Box>
    </StyledPatientCard>
  );
};
