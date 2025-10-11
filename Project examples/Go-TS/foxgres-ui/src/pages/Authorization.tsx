import { FC, useState } from "react";
import { useNavigate } from "react-router-dom";
import {
  Card,
  CardContent,
  Button,
  TextField,
  Box,
  Typography,
  Container,
} from "@mui/material";
import { styled } from "@mui/material/styles";

import { fetchLogin, LoginProps } from "../utils/utils";
import AlertNotification from "../components/alertNotification/AlertNotification";

const LoginCard = styled(Card)({
  width: 500,
  margin: "auto",
  marginTop: "10%",
  padding: "20px",
  background: "#FFF",
});

const LoginButton = styled(Button)({
  marginTop: "20px",
  fontSize: "16px",
  fontWeight: "bold",
});

const StyledTextField = styled(TextField)({
  marginBottom: "10px",
});

export const Login: FC = () => {
  const navigate = useNavigate();

  const [login, setLogin] = useState("");
  const [password, setPassword] = useState("");
  const [isErrorAuth, setIsErrorAuth] = useState(false);
  const [errorMsg, setErrorMsg] = useState("");

  const handleLogin = async ({ login, password }: LoginProps) => {
    try {
      const data = await fetchLogin({ login, password });
      if (data) {
        onSuccess();
      } else {
        onError("Ошибка авторизации");
      }
    } catch (error) {
      onError("Unknown Error!", error);
    }
  };

  const onSuccess = () => {
    localStorage.setItem("userId", login);
    navigate("/home");
  };

  const onError = (error: string, details?: any) => {
    setIsErrorAuth(true);
    setErrorMsg(error + " " + details.toString());
  };

  const handleClose = () => {
    setIsErrorAuth(false);
  };

  return (
    <Container component="main" maxWidth="md">
      <LoginCard>
        <CardContent>
          <Box
            sx={{
              display: "flex",
              flexDirection: "column",
              alignItems: "center",
            }}
          >
            <Typography component="h1" variant="h5">
              Вход в систему
            </Typography>
            <StyledTextField
              variant="outlined"
              margin="normal"
              required
              fullWidth
              id="email"
              label="Логин"
              name="email"
              autoComplete="email"
              autoFocus
              onBlur={(e) => {
                setLogin(e.target.value);
              }}
            />
            <StyledTextField
              variant="outlined"
              margin="normal"
              required
              fullWidth
              name="password"
              label="Пароль"
              type="password"
              id="password"
              autoComplete="current-password"
              onBlur={(e) => {
                setPassword(e.target.value);
              }}
            />
            <LoginButton
              type="submit"
              fullWidth
              variant="contained"
              color="primary"
              onClick={() => handleLogin({ login, password })}
            >
              Войти
            </LoginButton>
          </Box>
        </CardContent>
      </LoginCard>
      {isErrorAuth && (
        <AlertNotification
          open={isErrorAuth}
          severity="error"
          alertMessage={errorMsg}
          onClose={handleClose}
        />
      )}
    </Container>
  );
};
