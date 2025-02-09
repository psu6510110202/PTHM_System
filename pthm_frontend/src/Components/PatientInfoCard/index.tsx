import { Card, Typography, Stack, Divider } from "@mui/material";
import { styled } from "@mui/material/styles";
import PersonIcon from "@mui/icons-material/Person";
import CalendarTodayIcon from "@mui/icons-material/CalendarToday";
import WcIcon from "@mui/icons-material/Wc";
import PhoneIcon from "@mui/icons-material/Phone";
import EmailIcon from "@mui/icons-material/Email";
import HomeIcon from "@mui/icons-material/Home";
import LocalHospitalIcon from "@mui/icons-material/LocalHospital";
import MeetingRoomIcon from "@mui/icons-material/MeetingRoom";
import PatientSearchModel from "../../Models/PatientSeachModel";

const StyledPatientCard = styled(Card)(({ theme }) => ({
  borderRadius: theme.shape.borderRadius * 2, // Rounded corners
  padding: theme.spacing(3),
  boxShadow: "0px 8px 20px rgba(0, 0, 0, 0.15)", // Smooth shadow
  width: "100%", // Full width
  maxWidth: 450, // Card max width
  background: "linear-gradient(135deg, #f8f9fb, #ffffff)", // Soft gradient background
  border: "1px solid #e0e0e0", // Light border
}));


export const PatientInfoCard: React.FC<PatientSearchModel> = ({
  patient_id,
  first_name,
  last_name,
  age,
  gender,
  family_phone,
  family_email,
  address,
  doctor_name,
  room,
}) => {
  return (
    <StyledPatientCard>
      <Stack spacing={1.25}>
        <Typography variant="h6" fontWeight={700} align="center">
          🏥 Patient Information
        </Typography>
        <Divider />
        <Stack direction="row" alignItems="center" spacing={1}>
          <PersonIcon color="primary" />
          <Typography variant="body1"><b>Patient ID:</b> {patient_id}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <PersonIcon color="primary" />
          <Typography variant="body1"><b>Name:</b>{gender === "male" ? "Mr." : "Mrs."} {first_name} {last_name}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <CalendarTodayIcon color="primary" />
          <Typography variant="body1"><b>Age:</b> {age}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <WcIcon color="primary" />
          <Typography variant="body1"><b>Gender:</b> {gender}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <PhoneIcon color="primary" />
          <Typography variant="body1"><b>Phone:</b> {family_phone}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <EmailIcon color="primary" />
          <Typography variant="body1"><b>Email:</b> {family_email}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <HomeIcon color="primary" />
          <Typography variant="body1"><b>Address:</b> {address}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <LocalHospitalIcon color="primary" />
          <Typography variant="body1"><b>Doctor:</b> {doctor_name}</Typography>
        </Stack>
        <Stack direction="row" alignItems="center" spacing={1}>
          <MeetingRoomIcon color="primary" />
          <Typography variant="body1"><b>Room:</b> {room}</Typography>
        </Stack>
      </Stack>
    </StyledPatientCard>
  );
};
