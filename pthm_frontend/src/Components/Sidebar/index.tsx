import { Drawer, List, ListItem, ListItemButton, ListItemIcon, ListItemText, Box, Divider } from "@mui/material";
import { Person, Search, Logout } from "@mui/icons-material";
import { Link } from "react-router-dom";
import Avatar from '@mui/material/Avatar';
import logo from '../../assets/logo-2.png';
import { styled } from '@mui/material/styles';


export const Sidebar = () => {

  const Div = styled('div')(({ theme }) => ({
    ...theme.typography.button,
    backgroundColor: theme.palette.background.paper,
    padding: theme.spacing(1),
  }));  

  return (
    <Drawer
      variant="permanent"
      sx={{
        width: 150,
        flexShrink: 0,
        "& .MuiDrawer-paper": {
          width: 150,
          boxSizing: "border-box",
          backgroundColor: "#f8f9fa", // Light gray background
          color: "#000", // Text color
          display: "flex",
          flexDirection: "column",
          alignItems: "center",
          paddingTop: 1,
        },
      }}
    >
      {/* Logo Section */}
      <Box sx={{ width: "100%", paddingY: 2, display: "flex", justifyContent: "center" }}>
        <img src={logo} alt="Logo" style={{ width: 140, height: 60 }} />
      </Box>

      {/* Divider to separate logo and menu */}
      <Divider sx={{ width: "80%" }} />

      {/* Menu Items */}
      <List sx={{ width: "100%", paddingY: 1 }}>
        <ListItem disablePadding>
          <ListItemButton component={Link} to="/" sx={{ display: "flex", justifyContent: "flex-start", gap: 1 }}>
            <ListItemIcon sx={{ color: "#007bff", minWidth: "30px" }}>
              <Person />
            </ListItemIcon>
            <ListItemText primary="Patient" />
          </ListItemButton>
        </ListItem>

        <ListItem disablePadding>
          <ListItemButton component={Link} to="/search" sx={{ display: "flex", justifyContent: "flex-start", gap: 1 }}>
            <ListItemIcon sx={{ color: "#007bff", minWidth: "30px" }}>
              <Search />
            </ListItemIcon>
            <ListItemText primary="Search" />
          </ListItemButton>
        </ListItem>
      </List>

      {/* Spacer to push Sign Out to the bottom */}
      <Box sx={{ flexGrow: 1 }} />
      <div style={{ display: "flex", flexDirection: "column", alignItems: "center" }}>
        <Avatar>U</Avatar>
        <Div>{"Login as : "}</Div>
        <span>Staff</span>
      </div>
      <Divider sx={{ width: "80%" }} />
      
      {/* Sign Out Section */}
      <List sx={{ width: "100%" }}>
        <ListItem disablePadding>
          <ListItemButton component={Link} to="/signout" sx={{ display: "flex", justifyContent: "flex-start", gap: 1, color: "red" }}>
            <ListItemIcon sx={{ color: "red", minWidth: "30px" }}>
              <Logout />
            </ListItemIcon>
            <ListItemText primary="Sign Out" />
          </ListItemButton>
        </ListItem>
      </List>
    </Drawer>
  );
};
