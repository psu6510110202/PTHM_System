import { BrowserRouter, Routes, Route, useLocation } from 'react-router-dom';
import 'bootstrap/dist/css/bootstrap.min.css';
import './App.css';
import { Dashboard, Patient, PatientSearch, SignIn } from './Pages';
import { Sidebar } from './Components';
import { Box } from "@mui/material";
import { ProtectRoute, ScrollToTop } from './Helper';
import { Toaster } from "react-hot-toast";

function Layout() {
  const location = useLocation();
  const hideSidebar = location.pathname === "/signin"; // Hide sidebar on SignIn page

  return (
    <Box sx={{ display: "flex" }}> 
      {!hideSidebar && <Sidebar />} {/* Conditionally render Sidebar */}
      <Box sx={{ flexGrow: 1, padding: 3 }}> 
        <Routes>
          <Route index element={<ProtectRoute><Dashboard /></ProtectRoute>} />
          <Route path="/patients/:id" element={<ProtectRoute><Patient /></ProtectRoute>} />
          <Route path="/search" element={<ProtectRoute><PatientSearch /></ProtectRoute>} />
          <Route path="/signin" element={<SignIn />} />
          <Route path="*" element={<h1>Not Found</h1>} />
        </Routes>
      </Box>
    </Box>
  );
}

function App() {
  return (
    <BrowserRouter>
      <ScrollToTop />
      <Toaster position="top-center" reverseOrder={false} />
      <Layout />
    </BrowserRouter>
  );
}

export default App;
