import { useState } from "react";
import { Drawer, List, ListItem, ListItemButton, ListItemIcon, ListItemText, Box, Divider, IconButton } from "@mui/material";
import { Person, Search, Logout, Menu } from "@mui/icons-material";
import { Link, useNavigate } from "react-router-dom";
import Avatar from "@mui/material/Avatar";
import logo from "../../assets/logo-2.png";
import { useTheme } from "@mui/material/styles";
import useMediaQuery from "@mui/material/useMediaQuery";
import toast from "react-hot-toast";
import { userData } from "../../Helper";

export const Sidebar = () => {
  const [open, setOpen] = useState(true);
  const theme = useTheme();
  const isMobile = useMediaQuery(theme.breakpoints.down("md")); // Detect mobile screens
  const navigate = useNavigate(); // ✅ Use navigate to redirect
  const user = userData(); // Get user data from session
  

  // Toggle Sidebar
  const handleDrawerToggle = () => {
    setOpen(!open);
  };

  // ✅ Fix: Handle Logout
  const handleLogout = () => {
    sessionStorage.removeItem("user"); // Clear session
    toast.success("Sign Out Successful."); // Show toast
    navigate("/signin"); // Redirect to SignIn
  };

  return (
    <>
      {/* Toggle Button for Mobile */}
      {isMobile && (
        <IconButton onClick={handleDrawerToggle} sx={{ position: "absolute", top: 10, left: 10 }}>
          <Menu />
        </IconButton>
      )}

      <Drawer
        variant={isMobile ? "temporary" : "permanent"}
        open={open}
        onClose={handleDrawerToggle}
        sx={{
          width: open ? 150 : 50,
          flexShrink: 0,
          "& .MuiDrawer-paper": {
            width: open ? 150 : 50,
            boxSizing: "border-box",
            backgroundColor: "#f8f9fa",
            color: "#000",
            display: "flex",
            flexDirection: "column",
            alignItems: "center",
            paddingTop: 1,
            transition: "width 0.3s ease",
          },
        }}
      >
        {/* Logo */}
        <Box sx={{ width: "100%", paddingY: 2, display: "flex", justifyContent: "center" }}>
          {open && <img src={logo} alt="Logo" style={{ width: 140, height: 60 }} />}
        </Box>

        <Divider sx={{ width: "80%" }} />

        {/* Menu Items */}
        <List sx={{ width: "100%", paddingY: 1 }}>
          <ListItem disablePadding>
            <ListItemButton component={Link} to="/" sx={{ display: "flex", justifyContent: open ? "flex-start" : "center" }}>
              <ListItemIcon sx={{ color: "#007bff", minWidth: "30px" }}>
                <Person />
              </ListItemIcon>
              {open && <ListItemText primary="Patient" />}
            </ListItemButton>
          </ListItem>

          <ListItem disablePadding>
            <ListItemButton component={Link} to="/search" sx={{ display: "flex", justifyContent: open ? "flex-start" : "center" }}>
              <ListItemIcon sx={{ color: "#007bff", minWidth: "30px" }}>
                <Search />
              </ListItemIcon>
              {open && <ListItemText primary="Search" />}
            </ListItemButton>
          </ListItem>
        </List>

        {/* Spacer */}
        <Box sx={{ flexGrow: 1 }} />

        {/* Profile Section */}
        {open && (
          <div style={{ display: "flex", flexDirection: "column", alignItems: "center" }}>
            <Avatar>{user.username ? user.username[0] : "S"}</Avatar>
            <Box sx={{ fontWeight: "bold", padding: 1 }}>Login as:</Box>
            <span>{user.username ? user.username : "Staff"}</span>
          </div>
        )}
        
        <Divider sx={{ width: "80%" }} />

        {/* ✅ Updated Logout Button */}
        <List sx={{ width: "100%" }}>
          <ListItem disablePadding>
            <ListItemButton onClick={handleLogout} sx={{ display: "flex", justifyContent: open ? "flex-start" : "center", color: "red" }}>
              <ListItemIcon sx={{ color: "red", minWidth: "30px" }}>
                <Logout />
              </ListItemIcon>
              {open && <ListItemText primary="Sign Out"/>}
            </ListItemButton>
          </ListItem>
        </List>
      </Drawer>
    </>
  );
};
