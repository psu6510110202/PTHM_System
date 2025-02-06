import { Card, CardContent, Typography, Box } from "@mui/material";
import { styled } from "@mui/material/styles";

interface InfoCardProps {
  icon: React.ReactNode;
  count: number;
  label: string;
  bgcolor?: string;
}

const StyledCard = styled(Card)<{ bgcolor?: string }>(({ theme, bgcolor }) => ({
  display: "flex",
  alignItems: "center",
  justifyContent: "space-between",
  padding: theme.spacing(3),
  borderRadius: theme.shape.borderRadius * 3,
  backgroundColor: bgcolor || theme.palette.background.paper,
  color: bgcolor ? "#fff" : "#333",
  boxShadow: "0px 6px 15px rgba(0, 0, 0, 0.1)",
  width: 350,
  height: 200,
}));

const IconWrapper = styled(Box)<{ bgcolor?: string }>(({ bgcolor }) => ({
  width: 140,
  height: 140,
  display: "flex",
  alignItems: "center",
  justifyContent: "center",
  borderRadius: "50%",
  backgroundColor: bgcolor || "#E0F7FA",
}));

const CardContentWrapper = styled(CardContent)({
  textAlign: "right",
  flexGrow: 1, // Ensures content fills available space
  padding: 0,
  display: "flex",
  flexDirection: "column",
  alignItems: "flex-end",
});

export const DashboardMetricCard: React.FC<InfoCardProps> = ({ icon, count, label, bgcolor }) => {
  return (
    <StyledCard bgcolor={bgcolor}>
        <IconWrapper bgcolor={bgcolor ? "#ffffff40" : undefined}>{icon}</IconWrapper>
        <CardContentWrapper>
            <Typography 
            variant="h5" 
            fontWeight="bold" 
            sx={{ 
                fontSize: "4.0rem", // Bigger for emphasis 
                color: bgcolor ? "#FFF" : "#333", // White if bg is set, dark otherwise
                letterSpacing: 1, // Adds slight spacing for readability
                textShadow: bgcolor ? "2px 2px 5px rgba(0, 0, 0, 0.3)" : "none" // Subtle shadow on colored backgrounds
            }}
            >
            {count}
            </Typography>
            <Typography 
            variant="subtitle1" 
            sx={{ 
                fontSize: "1rem", 
                textTransform: "uppercase", // Makes label stand out
                fontWeight: "500", 
                opacity: 0.8, // Slightly faded for elegance
                letterSpacing: 0.5, 
                fontStyle: "italic" // Adds a stylish touch
            }}
            >
            {label}
            </Typography>
        </CardContentWrapper>
    </StyledCard>

  );
};
