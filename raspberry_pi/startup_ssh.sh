#!/bin/bash
sleep 30
ssh -p 443 -R0:{YourESP32CAM_IP}:80 -L4300:localhost:4300 -o StrictHostKeyChecking=no -o ServerAliveInterval=30 {Your Pinggy Token}@ap.a.pinggy.io