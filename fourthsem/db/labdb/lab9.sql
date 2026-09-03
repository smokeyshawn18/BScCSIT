SELECT e.*
FROM employee e
JOIN job j ON e.job_id = j.job_id
WHERE j.job_title = 'SH_CLERK';

SELECT e.first_name, e.last_name
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
WHERE d.location = (
    SELECT location
    FROM department
    WHERE dept_id = 90
);

SELECT d.department_name
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
GROUP BY d.department_name
HAVING COUNT(e.emp_id) = 2;

SELECT *
FROM employee
WHERE hire_date > (
    SELECT hire_date
    FROM employee
    WHERE first_name = 'Neena' AND last_name = 'Kochhar'
);


SELECT *
FROM employee
WHERE manager_id = (
    SELECT manager_id
    FROM employee
    WHERE first_name = 'Michael' AND last_name = 'Hartstein'
);
