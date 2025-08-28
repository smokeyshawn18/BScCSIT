SELECT e.ename
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
WHERE d.department_name = 'IT'
ORDER BY e.ename ASC;


SELECT d.department_name, COUNT(e.emp_id) AS employee_count
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
WHERE e.salary > 5000
GROUP BY d.department_name;


SELECT d.department_name, AVG(e.salary) AS average_salary
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
GROUP BY d.department_name;

SELECT e.ename,
       d.department_name,
       e.salary
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
WHERE e.salary = (
    SELECT MAX(e2.salary)
    FROM employee e2
    WHERE e2.dept_id = e.dept_id
);


SELECT e.ename,
       d.department_name
FROM employee e
LEFT JOIN department d ON e.dept_id = d.dept_id;


