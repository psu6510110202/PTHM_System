import { Card, Typography, Stack } from "@mui/material";
import { styled } from "@mui/material/styles";
import { Gauge, gaugeClasses } from '@mui/x-charts/Gauge';

interface PatientCardProps {
  temperature: number; // Body temperature
  minTemp: number; // Minimum temperature threshold
  maxTemp: number; // Maximum temperature threshold
}

const StyledPatientCard = styled(Card)(({ theme }) => ({
  borderRadius: theme.shape.borderRadius * 2, // Rounded corners
  padding: theme.spacing(3),
  boxShadow: "0px 8px 20px rgba(0, 0, 0, 0.1)", // Deeper shadow for emphasis
  maxWidth: 375, // Card width
  width: "100%", // Full width
  display: "flex",
  flexDirection: "column",
  justifyContent: "space-between",
  background: "linear-gradient(135deg, #f3f6fa, #ffffff)", // Soft gradient background
  border: "1px solid #e0e0e0", // Light border for card definition
}));

export const BodyTempCard: React.FC<PatientCardProps> = ({
  temperature,
  minTemp,
  maxTemp,
}) => {
  // Conditional rendering of green or red gauge based on the temperature
  const isNormalTemp = temperature < 37.5;
  const status = isNormalTemp ? 'Normal Temperature' : 'High Temperature';

  return (
    <StyledPatientCard>
      <Stack spacing={0} alignItems="center">
        <Typography variant="h6" fontWeight={800} color="primary">
          🌡️ Body Temperature
        </Typography>

        {/* Gauge Component with conditional color based on temperature */}
        {isNormalTemp ? (
          <Gauge
            value={temperature}
            valueMin={minTemp}
            valueMax={maxTemp}
            width={220}
            height={220}
            startAngle={-90}
            endAngle={90}
            sx={(theme) => ({
              [`& .${gaugeClasses.valueArc}`]: {
                fill: '#52b202', // Green for normal temperature
              },
              [`& .${gaugeClasses.referenceArc}`]: {
                fill: theme.palette.text.disabled, // Customize the color for the reference arc (background)
              },
              [`& .${gaugeClasses.valueText}`]: {
                fontSize: 35,
                transform: 'translate(0px, 0px)',
              },
            })}
            text={({ value }) => `${value}°C`} // Correct placement of the text prop
          />
        ) : (
          <Gauge
            value={temperature}
            valueMin={minTemp}
            valueMax={maxTemp}
            width={220}
            height={220}
            startAngle={-90}
            endAngle={90}
            sx={(theme) => ({
              [`& .${gaugeClasses.valueArc}`]: {
                fill: '#f44336', // Red for high temperature
              },
              [`& .${gaugeClasses.referenceArc}`]: {
                fill: theme.palette.text.disabled, // Customize the color for the reference arc (background)
              },
              [`& .${gaugeClasses.valueText}`]: {
                fontSize: 35,
                transform: 'translate(0px, 0px)',
              },
            })}
            text={({ value }) => `${value}°C`} // Correct placement of the text prop
          />
        )}

        <Typography variant="body1" color="text.secondary">
          {status}
        </Typography>
      </Stack>
    </StyledPatientCard>
  );
};
