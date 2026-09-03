SELECT MAX(salary) AS second_highest_salary
FROM employee
WHERE salary < (SELECT MAX(salary) FROM employee);

SELECT j.job_id, j.job_title, COUNT(e.emp_id) AS total_employees
FROM employee e
JOIN job j ON e.job_id = j.job_id
GROUP BY j.job_id, j.job_title
HAVING COUNT(e.emp_id) > 3;

SELECT e.ename, e.salary, j.job_title
FROM employee e
JOIN job j ON e.job_id = j.job_id
ORDER BY e.salary DESC
LIMIT 3;

SELECT ename, emp_id, job_id, dept_id
FROM employee
WHERE manager_id IS NULL;

SELECT d.department_name, AVG(e.salary) AS avg_salary
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
GROUP BY d.department_name
ORDER BY avg_salary DESC
LIMIT 1;
