SELECT DISTINCT first_name
FROM employee                                                                                              
WHERE dept_id IN (10, 20);

SELECT first_name
FROM employee
WHERE dept_id IN (10, 20);

SELECT first_name
FROM employee
WHERE dept_id = 30
  AND salary > 8000;

SELECT first_name
FROM employee
WHERE dept_id = 30
  AND salary <= 8000;

SELECT DISTINCT job_id
FROM employee
WHERE dept_id IN (10, 20)
ORDER BY job_id;
