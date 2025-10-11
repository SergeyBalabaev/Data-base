import { FC } from "react";
import {
  Table,
  TableBody,
  TableCell,
  TableContainer,
  TableHead,
  TableRow,
  Paper,
} from "@mui/material";
import { getColorForMark } from './helper'; 

interface TableProps {
  disciplines: Array<string>;
  marks: Record<string, number>;
}

const SubjectTable: FC<TableProps> = ({ disciplines, marks }) => {
  return (
    <TableContainer component={Paper}>
      <Table>
        <TableHead>
          <TableRow>
            <TableCell>Дисциплина</TableCell>
            <TableCell align="right">Оценка</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {disciplines.map((discipline) => (
            <TableRow key={discipline}>
              <TableCell component="th" scope="row">
                {discipline}
              </TableCell>
              <TableCell
                align="center"
                sx={{
                  backgroundColor: getColorForMark(marks[discipline]),
                  fontWeight: "bold",
                }}
              >
                {marks[discipline]}
              </TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
  );
};

export default SubjectTable;
