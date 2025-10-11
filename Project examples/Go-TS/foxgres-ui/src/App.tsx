import { Routes, Route } from "react-router-dom";
import { Login, Home, ErrorPage } from "./pages";

function App() {
  return (
    <Routes>
      {/* Login Page */}
      <Route path="/" element={<Login />} />

      {/* Main Pages */}
      <Route path="home" element={<Home />} />

      {/* Error route */}
      <Route path="*" element={<ErrorPage />} />
    </Routes>
  );
}

export default App;
