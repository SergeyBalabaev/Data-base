import { FC } from "react";
import { Alert, Snackbar, styled } from "@mui/material";

interface AlertProps {
  open: boolean;
  severity: "success" | "error";
  alertMessage?: string;
  onClose: () => void;
}

const StyledMsg = styled("p")`
  font-size: 14px;
  font-weight: bold;
`;

const AlertNotification: FC<AlertProps> = ({
  open,
  severity,
  alertMessage,
  onClose,
}) => {
  return (
    <Snackbar
      open={open}
      autoHideDuration={10000}
      onClose={onClose}
      anchorOrigin={{ vertical: "bottom", horizontal: "right" }}
    >
      <Alert onClose={onClose} severity={severity}>
        <StyledMsg>{alertMessage}</StyledMsg>
      </Alert>
    </Snackbar>
  );
};

export default AlertNotification;
