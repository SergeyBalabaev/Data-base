import { API_BASE_URL } from "./constants";

export interface LoginProps {
  login: string;
  password: string;
}

export const fetchLogin = async ({ login, password }: LoginProps) => {
  const response = await fetch(`${API_BASE_URL}/auth`, {
    method: "GET",
    headers: {
      "Content-type": "application/json",
      login: login,
      password: password,
    },
  });

  if (response.ok) {
    const data = await response.json();
    return data;
  } else {
    return undefined; // TODO: think of it
  }
};

export const fetchGrades = async (studentId: string) => {
  try {
    const response = await fetch(
      `${API_BASE_URL}/marks?student_id=${studentId}`,
    );
    if (!response.ok) {
      throw new Error("Проблема с получением данных: " + response.statusText);
    }
    const data = await response.json();
    return data;
  } catch (error) {
    console.error("Ошибка при выполнении запроса:", error);
    throw error;
  }
};
