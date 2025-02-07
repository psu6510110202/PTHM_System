import { BrowserRouter, Routes, Route } from 'react-router-dom';
import 'bootstrap/dist/css/bootstrap.min.css';
import './App.css';
import { Dashboard, Patient } from './Pages';
import { Sidebar } from './Components';
import { Box } from "@mui/material";

function App() {
  return (
    <BrowserRouter>
      <Box sx={{ display: "flex" }}> {/* Flex container */}
        <Sidebar />
        <Box sx={{ flexGrow: 1, padding: 3 }}> {/* Main content area */}
          <Routes>
            <Route index element={<Dashboard />} />
            <Route path="/patients" element={<Patient/>} />
          </Routes>
        </Box>
      </Box>
    </BrowserRouter>
  );
}

export default App;
