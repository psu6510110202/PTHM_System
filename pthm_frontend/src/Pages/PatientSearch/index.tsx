import { useState, useRef, useEffect } from "react";
import { Box, TextField, InputAdornment, Typography } from "@mui/material";
import {Grid2} from "@mui/material";
import SearchIcon from "@mui/icons-material/Search";
import { PatientInfoCard } from "../../Components";
import PatientInfoModel from "../../Models/PatientInfoModel";
import { userData } from "../../Helper";
import Repo from "../../Repositories";

export const PatientSearch = () => {
  const [patients, setPatients] = useState<PatientInfoModel[]>([]);
  const [searchQuery, setSearchQuery] = useState("");
  const user = userData();

  const fetchPatients = async () => {
      try {
          const response = await Repo.PatientInfoRepository.getAll(user.jwt);
          if(response){
              setPatients(response);
          }
      } catch (error) {
          console.error("Error fetching patients:", error);
          setPatients([]); // Set to empty array on failure
      }
  };

  const intervalRef = useRef<NodeJS.Timeout | number | null>(null);
  
  useEffect(() => {
      fetchPatients();

      intervalRef.current = setInterval(() => {
          fetchPatients();
      }, 5000);

      return () => {
          if (intervalRef.current) clearInterval(intervalRef.current);
      };
  }, []);

  // Filter patients based on name or room number
  const filteredPatients = patients.filter(patient => 
    patient.first_name.toLowerCase().includes(searchQuery.toLowerCase()) ||
    patient.last_name.toLowerCase().includes(searchQuery.toLowerCase()) ||
    patient.room.toString().includes(searchQuery) ||
    patient.patient_id.toString().includes(searchQuery)
);

  return (
    <Box display="flex" flexDirection="column" alignItems="center" p={4}>
      <Typography variant="h5" fontWeight={700} mb={3}>
        Searching For Patient
      </Typography>

      {/* Search Input Field */}
      <TextField
        variant="outlined"
        placeholder="Search by Name, Room or ID"
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
              <Grid2 size={{xs:12, sm:6, md:4}} key={patient.patient_id} display="flex" justifyContent="center" maxWidth={450}>
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
