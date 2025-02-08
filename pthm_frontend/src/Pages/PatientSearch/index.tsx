import { useState } from "react";
import { Box, TextField, InputAdornment, Typography } from "@mui/material";
import {Grid2} from "@mui/material";
import SearchIcon from "@mui/icons-material/Search";
import { PatientInfoCard } from "../../Components";

// Sample patient data
const patients = [
  {
    patientId: "xxxxx1",
    name: "Mr. John ABC",
    age: 59,
    gender: "Male",
    phone: "xxx-xxx-xxxx",
    email: "john.abc@gmail.com",
    address: "14/29 Gp 7 Phetkasem Nong Klang Ploo Nong Khaem",
    doctor: "Dr. Smith ABC",
    room: "4405",
  },
  {
    patientId: "xxxxx2",
    name: "Ms. Jane Doe",
    age: 45,
    gender: "Female",
    phone: "xxx-xxx-xxxx",
    email: "jane.doe@email.com",
    address: "22/5 Bang Kapi Road",
    doctor: "Dr. Wilson",
    room: "2301",
  },
  // Add more sample data...
];

export const PatientSearch = () => {
  const [searchQuery, setSearchQuery] = useState("");

  // Filter patients based on name or room number
  const filteredPatients = patients.filter(
    (patient) =>
      patient.name.toLowerCase().includes(searchQuery.toLowerCase()) ||
      patient.room.includes(searchQuery)
  );

  return (
    <Box display="flex" flexDirection="column" alignItems="center" p={4}>
      <Typography variant="h5" fontWeight={700} mb={3}>
        Searching For Patient
      </Typography>

      {/* Search Input Field */}
      <TextField
        variant="outlined"
        placeholder="Search by name or room"
        value={searchQuery}
        onChange={(e) => setSearchQuery(e.target.value)}
        sx={{
          width: "50%",
          background: "#f5f5f5",
          borderRadius: 5,
          "& fieldset": { border: "none" },
        }}
        InputProps={{
          startAdornment: (
            <InputAdornment position="start">
              <SearchIcon color="action" />
            </InputAdornment>
          ),
        }}
      />

      {/* Search Results */}
      <Box mt={4} width="100%">
        {filteredPatients.length > 0 ? (
          <Grid2 container spacing={3} justifyContent="center">
            {filteredPatients.map((patient) => (
              <Grid2 size={{xs:12, sm:6, md:4}} key={patient.patientId} display="flex" justifyContent="center" maxWidth={450}>
                <PatientInfoCard {...patient}/>
              </Grid2>
            ))}
          </Grid2>
        ) : (
          <Typography variant="body1" color="text.secondary" textAlign="center">
            No patient found.
          </Typography>
        )}
      </Box>
    </Box>
  );
};
