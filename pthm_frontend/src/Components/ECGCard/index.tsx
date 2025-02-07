import ReactApexChart from "react-apexcharts";
import { Card, Typography } from "@mui/material";
import { styled } from "@mui/material/styles";

const StyledECGCard = styled(Card)(({ theme }) => ({
  borderRadius: theme.shape.borderRadius * 2,
  padding: theme.spacing(4),
  boxShadow: "0px 8px 20px rgba(0, 0, 0, 0.1)",
  width: "100%", // Full width inside the container
  maxWidth: "90vw", // Responsive max width
  minWidth: 300, // Prevents it from shrinking too much
  maxHeight: 425, // Maintain good visibility
  background: "white",
}));


type ECGCardProps = {
  ecgData: number[];
};

export const ECGCard: React.FC<ECGCardProps> = ({ ecgData }) => {
  const options = {
    chart: {
      id: "ecg-chart",
      animations: { enabled: true, easing: "linear", dynamicAnimation: { speed: 500 } },
      toolbar: { show: false },
      zoom: { enabled: false },
    },
    stroke: { curve: "smooth" as "smooth", width: 2 }, // Make line smoother and thinner
    markers: { size: 0 }, // Remove pointers
    tooltip: { enabled: false }, // Disable tooltip
    xaxis: { labels: { show: false } }, // No need for x-axis labels
    yaxis: {
      labels: { show: true, formatter: (val: number) => val.toFixed(1) }, // Limit decimal places
    },
    grid: { show: false }, // Optional: remove grid lines
  };

  return (
    <StyledECGCard>
      <Typography variant="h5" fontWeight={700} color="primary" gutterBottom>
        ECG Signal
      </Typography>
      <ReactApexChart
        options={options}
        series={[{ data: ecgData.map((value, index) => ({ x: index, y: value })), name: "ECG" }]}
        type="line"
        height={350} // Increase chart height for better visibility
      />
    </StyledECGCard>
  );
};
