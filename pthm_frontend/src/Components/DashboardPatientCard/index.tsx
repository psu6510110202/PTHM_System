import { Card, CardContent, Typography, Box } from "@mui/material";
import { styled } from "@mui/material/styles";
import { Link } from "react-router-dom";
import { NotificationsActive, Warning, Shield } from "@mui/icons-material";

interface PatientCardProps {
  status: string; // Status can toggle between "online" or "offline"
  patient_id: string;
  first_name: string;
  last_name: string;
  gender: string;
  age: number;
  room: string;
  risk: string;
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
  patient_id,
  first_name,
  last_name,
  gender,
  age,
  room,
  risk
}) => {

  const getBorderColor = (risk: string): string => {
    switch (risk) {
        case "Normal":
            return "#43A047"; // Green
        case "Risk":
            return "#FFC107"; // Yellow
        case "Critical":
            return "#D32F2F"; // Red
        default:
            return "#43A047"; // Default to Green
    }
  }

  const getIcon = (risk: string) => {
    switch (risk) {
      case "Normal":
          return (<Shield sx={{ fontSize: 30, color: "#43A047" }} />); // Green
      case "Risk":
          return (<Warning sx={{ fontSize: 30, color: "#FF6A00" }} />); // Yellow
      case "Critical":
          return (<NotificationsActive sx={{ fontSize: 30, color: "#FF3D3D" }}/>); // Red
      default:
          return (<Shield sx={{ fontSize: 30, color: "#43A047" }} />); // Default to Green
  }
  }
  return (
    <StyledPatientCard borderColor={getBorderColor(risk)}>
      <Link 
        to={{
            pathname: "/patients/dashboard",  // Redirect to a generic details page
        }} 
        state={{ patientId: patient_id }} // Pass the patient ID in state
        style={{ textDecoration: "none" }}
      >
        <Box display="flex" justifyContent="space-between" alignItems="center">
          <Typography variant="subtitle2" fontWeight={600} color="text.secondary">
              Patient ID: {patient_id}
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
            {gender === "male" ? "Mr.":"Mrs."} {first_name} {last_name}
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Age: <Typography component="span" fontWeight={600}>{age}</Typography>
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Floor: <Typography component="span" fontWeight={600}>{room[0]}</Typography>
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Room: <Typography component="span" fontWeight={600}>{room}</Typography>
          </Typography>
        </CardContent>
        <Box display="flex" justifyContent="flex-end" alignItems="center">
          {getIcon(risk)}
          <Typography variant="subtitle2" fontWeight={600} color="text.secondary">
            {risk}
          </Typography>
        </Box>
      </Link>
    </StyledPatientCard>
  );
};
