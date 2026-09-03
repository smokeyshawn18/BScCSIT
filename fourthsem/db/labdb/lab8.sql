GRANT CONNECT ON DATABASE postgres TO csit;
GRANT CREATE ON DATABASE postgres TO csit;

psql -U yourName -d postgres -W

CREATE TABLE Student (
    Student_ID SERIAL PRIMARY KEY,
    Name VARCHAR(50),
    Department VARCHAR(50),
    Age INT
);

INSERT INTO Student (Name, Department, Age) VALUES
('Ram', 'CSIT', 20),
('Sita', 'CSIT', 22),
('Hari', 'Math', 21);

SELECT * FROM Student WHERE Department = 'CSIT';

UPDATE Student
SET Age = 23
WHERE Student_ID = 2;

DELETE FROM Student
WHERE Student_ID = 3;
