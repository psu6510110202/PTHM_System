import React, { useState, useEffect } from 'react';
import Box from '@mui/material/Box';
import Button from '@mui/material/Button';
import FormControl from '@mui/material/FormControl';
import TextField from '@mui/material/TextField';
import Typography from '@mui/material/Typography';
import Stack from '@mui/material/Stack';
import MuiCard from '@mui/material/Card';
import { styled } from '@mui/material/styles';
import { useNavigate } from 'react-router-dom';
import axios from 'axios';
import toast from 'react-hot-toast';
import conf from '../../conf';
import { storeUser, userData } from '../../Helper';

const Card = styled(MuiCard)(({ theme }) => ({
  display: 'flex',
  flexDirection: 'column',
  alignItems: 'center',
  width: '100%',
  padding: theme.spacing(4),
  gap: theme.spacing(2),
  margin: 'auto',
  [theme.breakpoints.up('sm')]: {
    maxWidth: '400px',
  },
  borderRadius: theme.spacing(2),
  boxShadow: '0px 5px 15px rgba(0, 0, 0, 0.1), 0px 15px 35px rgba(0, 0, 0, 0.05)',
  background: 'rgba(255, 255, 255, 0.9)', // Transparent background for a glass effect
  backdropFilter: 'blur(5px)', // Blur effect to enhance visibility
  zIndex: 2, // Keeps card above the video
}));

const SignInContainer = styled(Stack)({
  position: 'relative', 
  height: '100vh',
  display: 'flex',
  justifyContent: 'center',
  alignItems: 'center',
  padding: '16px',
  zIndex: 2, // Keeps the form above the video
});

const BackgroundVideo = styled('video')({
  position: 'fixed', // Covers entire screen
  top: 0,
  left: 0,
  width: '100vw',
  height: '100vh',
  objectFit: 'cover', // Ensures full coverage
  zIndex: -1, // Stays in the background
});

const initialUser = { identifier: '', password: '' };

export const SignIn = () => {
  const [user, setUser] = useState(initialUser);
  const navigate = useNavigate();

  // Check if user is already logged in
  useEffect(() => {
    const data = userData();
    if (data?.jwt) {
      navigate('/');
    }
  }, [navigate]);

  // Handle input changes
  const handleChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = event.target;
    setUser({ ...user, [name]: value });
  };

  // Handle login
  const handleLogin = async (event: React.FormEvent<HTMLFormElement> | React.MouseEvent<HTMLButtonElement>) => {
    event.preventDefault();
    if (!user.identifier || !user.password) {
      toast.error("Please enter both email and password");
      return;
    }

    const url = `${conf.apiPrefix}/api/auth/local`;

    try {
      const { data } = await axios.post(url, user);
      if (data.jwt) {
        storeUser(data);
        toast.success("Login successful");

        setTimeout(() => {
          navigate('/');
        }, 2000);
      }
    } catch (error) {
      toast.error("Invalid email or password");
    }
  };

  return (
    <>
      {/* Video Background */}
      <BackgroundVideo autoPlay loop muted>
        <source src="/background_mute.mp4" type="video/mp4" />
        Your browser does not support the video tag.
      </BackgroundVideo>

      {/* Login Form */}
      <SignInContainer>
        <Card variant="outlined">
          <img src="/logo.svg" alt="Logo" style={{ width: '100px', marginBottom: '10px' }} />
          <Typography component="h1" variant="h5" sx={{ fontWeight: 'bold', textAlign: 'center' }}>
            Patient Health Monitoring System
          </Typography>
          <Typography sx={{ color: 'gray', textAlign: 'center', fontSize: '16px' }}>
            Sign into your account
          </Typography>

          <Box
            component="form"
            onSubmit={handleLogin}
            noValidate
            sx={{
              display: 'flex',
              flexDirection: 'column',
              width: '100%',
              gap: 2,
            }}
          >
            <FormControl>
              <TextField
                id="identifier"
                type="email"
                name="identifier"
                placeholder="Enter email"
                autoComplete="email"
                autoFocus
                required
                fullWidth
                variant="outlined"
                onChange={handleChange}
                sx={{ backgroundColor: '#f9f9f9', borderRadius: '10px' }}
              />
            </FormControl>

            <FormControl>
              <TextField
                id="password"
                type="password"
                name="password"
                placeholder="Enter password"
                autoComplete="current-password"
                required
                fullWidth
                variant="outlined"
                onChange={handleChange}
                sx={{ backgroundColor: '#f9f9f9', borderRadius: '10px' }}
              />
            </FormControl>

            <Typography sx={{ fontSize: '14px', textAlign: 'right', color: 'gray' }}>
              Forgot password? Please contact the administrator.
            </Typography>

            <Button
              type="submit"
              fullWidth
              variant="contained"
              sx={{
                backgroundColor: '#F12027',
                borderRadius: '25px',
                width: '100%',
                height: '50px',
                fontSize: '18px',
                fontWeight: 'bold',
                color: 'white',
                '&:hover': { backgroundColor: '#D81B24' },
              }}
            >
              Login
            </Button>
          </Box>
        </Card>
      </SignInContainer>
    </>
  );
};
