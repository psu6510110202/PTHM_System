import ReactApexChart from "react-apexcharts";
import { Card, Typography, Box } from "@mui/material";
import { styled } from "@mui/material/styles";
import { useEffect, useState, useRef } from "react";
import { ApexOptions } from "apexcharts";

const StyledECGCard = styled(Card)(({ theme }) => ({
  borderRadius: theme.shape.borderRadius * 2,
  padding: theme.spacing(4),
  boxShadow: "0px 8px 20px rgba(0, 0, 0, 0.1)",
  width: "100%", // Full width inside the container
  maxWidth: "90vw", // Responsive max width
  minWidth: 300, // Prevents it from shrinking too much
  maxHeight: 480, // Increased to accommodate BPM display
  background: "white", // Black background to match the image
}));

const BPMDisplay = styled(Box)(({ theme }) => ({
  display: "flex",
  alignItems: "center",
  justifyContent: "flex-end",
  marginBottom: theme.spacing(2),
}));

type ECGCardProps = {
  bpm: number;
  windowSize?: number; // Number of data points visible at once
};

export const ECGCard: React.FC<ECGCardProps> = ({ bpm, windowSize = 500 }) => {
  const [ecgData, setEcgData] = useState<number[]>([]);
  const [displayData, setDisplayData] = useState<Array<{x: number, y: number}>>([]);
  const animationRef = useRef<number>();
  const positionRef = useRef<number>(0);
  
  // Generate a larger pool of ECG data
  useEffect(() => {
    if (bpm > 0) {
      // Calculate parameters for a full ECG cycle
      const samplingRate = 250; // 250Hz sampling rate
      const secondsPerBeat = 60 / bpm;
      const pointsPerBeat = Math.round(secondsPerBeat * samplingRate);
      
      // Create enough data for multiple beats (at least 4x window size)
      const totalPoints = Math.max(windowSize * 4, pointsPerBeat * 10);
      
      // Generate ECG waveform
      const generateECG = () => {
        const data: number[] = [];
        
        // Function to generate a single heartbeat waveform
        const generateHeartbeat = (offset: number) => {
          // P wave
          for (let i = 0; i < pointsPerBeat * 0.1; i++) {
            const x = i / (pointsPerBeat * 0.1);
            data[offset + i] = 0.1 * Math.sin(x * Math.PI);
          }
          
          // PR segment (flat line before QRS)
          for (let i = 0; i < pointsPerBeat * 0.05; i++) {
            data[offset + Math.floor(pointsPerBeat * 0.1) + i] = 0.02;
          }
          
          // QRS complex (main spike)
          const qrsStart = offset + Math.floor(pointsPerBeat * 0.15);
          data[qrsStart] = -0.2; // Q wave (small dip)
          for (let i = 1; i < pointsPerBeat * 0.05; i++) {
            const progress = i / (pointsPerBeat * 0.05);
            if (progress < 0.5) {
              // R upstroke (main spike up)
              data[qrsStart + i] = -0.2 + 1.4 * progress;
            } else {
              // R downstroke (main spike down)
              data[qrsStart + i] = 0.7 - 1.1 * (progress - 0.5);
            }
          }
          data[qrsStart + Math.floor(pointsPerBeat * 0.05)] = -0.25; // S wave (small dip after spike)
          
          // ST segment (flat line after QRS)
          for (let i = 0; i < pointsPerBeat * 0.1; i++) {
            data[qrsStart + Math.floor(pointsPerBeat * 0.05) + 1 + i] = 0.05;
          }
          
          // T wave (rounded bump after flat segment)
          const tStart = qrsStart + Math.floor(pointsPerBeat * 0.15) + 1;
          for (let i = 0; i < pointsPerBeat * 0.2; i++) {
            const x = i / (pointsPerBeat * 0.2);
            data[tStart + i] = 0.3 * Math.sin(x * Math.PI);
          }
          
          // Rest of the cycle (baseline)
          const restStart = tStart + Math.floor(pointsPerBeat * 0.2);
          for (let i = restStart; i < offset + pointsPerBeat; i++) {
            data[i] = 0;
          }
        };
        
        // Initialize the data array with zeros
        for (let i = 0; i < totalPoints; i++) {
          data[i] = 0;
        }
        
        // Generate heartbeats
        const beatsCount = Math.ceil(totalPoints / pointsPerBeat);
        for (let beat = 0; beat < beatsCount; beat++) {
          generateHeartbeat(beat * pointsPerBeat);
        }
        
        // Add some noise to make it look realistic
        for (let i = 0; i < totalPoints; i++) {
          data[i] += (Math.random() - 0.5) * 0.03;
        }
        
        return data;
      };
      
      setEcgData(generateECG());
      positionRef.current = 0;
    }
  }, [bpm, windowSize]);

  // Animation function that updates display data
  useEffect(() => {
    if (ecgData.length === 0) return;
  
    let lastPauseTime = performance.now(); // Track the last pause time
    const pauseDuration = 500; // 1 second
    const updateInterval = 10000; // 9 seconds
    
    const updateDisplayData = () => {
      const now = performance.now();
  
      // If 9 seconds have passed since last pause, stop updates for 1 second
      if (now - lastPauseTime >= updateInterval) {
        lastPauseTime = now; // Reset pause time
        setTimeout(() => {
          animationRef.current = requestAnimationFrame(updateDisplayData);
        }, pauseDuration);
        return; // Skip this update to create a pause
      }
  
      const startIdx = positionRef.current;
      let newData = [];
  
      for (let i = 0; i < windowSize; i++) {
        const idx = (startIdx + i) % ecgData.length;
        newData.push({ x: i, y: ecgData[idx] });
      }
  
      setDisplayData(newData);
  
      // Move position forward for next frame (scrolling effect)
      positionRef.current = (positionRef.current + 3) % ecgData.length;
  
      // Continue animation
      animationRef.current = requestAnimationFrame(updateDisplayData);
    };
  
    animationRef.current = requestAnimationFrame(updateDisplayData);
  
    return () => {
      if (animationRef.current) {
        cancelAnimationFrame(animationRef.current);
      }
    };
  }, [ecgData, windowSize]);  

  const options: ApexOptions = {
    chart: {
      id: "ecg-chart",
      animations: {
        enabled: false, // We're handling animation ourselves
      },
      toolbar: { show: false },
      zoom: { enabled: false },
      background: "white", // Black background like in the image
      sparkline: {
        enabled: false
      }
    },
    colors: ["#00BFFF"], // Bright blue color as in the image
    stroke: { 
      curve: "smooth", 
      width: 2,
    },
    markers: { size: 0 }, // Remove pointers
    tooltip: { enabled: false }, // Disable tooltip
    xaxis: { 
      labels: { show: false },
      axisBorder: { show: false },
      axisTicks: { show: false },
      range: windowSize,
      tickAmount: 0,
    },
    yaxis: {
      min: -0.5,
      max: 1.5,
      tickAmount: 4,
      labels: { 
        show: true, 
        style: { colors: "#00BFFF" }, // Match chart color
        formatter: (val: number) => val.toFixed(1)
      }
    },
    grid: { 
      show: true,
      borderColor: "#333333",
      strokeDashArray: 5,
      position: "back" as "back",
      yaxis: {
        lines: { show: true }
      },
      xaxis: {
        lines: { show: false }
      }
    },
    theme: {
      mode: "dark"
    },
    annotations: {
      yaxis: [
        {
          y: 0,
          borderColor: "#444",
          strokeDashArray: 0
        },
        {
          y: 0.5,
          borderColor: "#444",
          strokeDashArray: 5 
        },
        {
          y: 1.0,
          borderColor: "#444",
          strokeDashArray: 5
        },
        {
          y: -0.5,
          borderColor: "#444",
          strokeDashArray: 5
        }
      ]
    }
  };

  return (
    <StyledECGCard>
      <Box display="flex" justifyContent="space-between" alignItems="center" mb={2}>
        <Typography variant="h5" fontWeight={700} color="#00BFFF">
          ECG Signal
        </Typography>
        <BPMDisplay>
          <Typography variant="h6" color="#FF4500" fontWeight={700} mr={1}>
            BPM:
          </Typography>
          <Typography variant="h6" color="#FF4500" fontWeight={700}>
            {bpm}
          </Typography>
        </BPMDisplay>
      </Box>
      <ReactApexChart
        options={options}
        series={[{ data: displayData, name: "ECG" }]}
        type="line"
        height={350}
        width="100%"
      />
    </StyledECGCard>
  );
};