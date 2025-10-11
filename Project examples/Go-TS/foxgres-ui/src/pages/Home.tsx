import { FC, ChangeEvent, useEffect, useState } from "react";
import { TextField, styled } from "@mui/material";
import SubjectTable from "../components/subjectTable/SubjectTable";
import { fetchGrades } from "../utils/utils";

interface Marks {
  [discipline: string]: number;
}

interface PersonProps {
  surname: string;
  name: string;
  patronymic?: string;
  group?: string;
}

const StyledHome = styled("div")`
  border-radius: 15px;
  padding: 20px;
  box-shadow: 0px 0px 50px 1px rgba(0, 0, 0, 0.1);
`;

export const Home: FC = () => {
  const [userId, setUserId] = useState("");
  const [studentInfo, setStudentInfo] = useState<PersonProps | null>(null);
  const [marks, setMarks] = useState<Marks>({});
  const [searchTerm, setSearchTerm] = useState("");

  useEffect(() => {
    const storedUserId = localStorage.getItem("userId");
    if (storedUserId) {
      setUserId(storedUserId);
    }
  }, []);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const data = await fetchGrades(userId);
        setStudentInfo(data.student);
        setMarks(data.marks);
      } catch (error) {
        console.log(error);
      }
    };

    fetchData();
  }, [userId]);

  const handleSearch = (event: ChangeEvent<HTMLInputElement>) => {
    setSearchTerm(event.target.value);
  };

  const filteredDisciplines = Object.keys(marks).filter((discipline) =>
    discipline.toLowerCase().includes(searchTerm.toLowerCase()),
  );
  return (
    <StyledHome>
      {userId && (
        <div>
          <h1 style={{ color: '#444343' }}>{`${studentInfo?.surname} ${studentInfo?.name} ${studentInfo?.patronymic}`}</h1>
        </div>
      )}
      <TextField
        label="Поиск дисциплины"
        variant="outlined"
        fullWidth
        margin="normal"
        value={searchTerm}
        onChange={handleSearch}
      />
      <SubjectTable disciplines={filteredDisciplines} marks={marks} />
    </StyledHome>
  );
};
