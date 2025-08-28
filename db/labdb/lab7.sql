SELECT ename, hire_date
FROM employee
WHERE hire_date > '2005-12-31'
ORDER BY hire_date ASC;

SELECT j.job_title, COUNT(e.emp_id) AS total_employees
FROM employee e
JOIN job j ON e.job_id = j.job_id
GROUP BY j.job_title
ORDER BY total_employees DESC;

SELECT e.ename, d.department_name, d.location
FROM employee e
JOIN department d ON e.dept_id = d.dept_id
WHERE d.location ILIKE '%London%';

SELECT e.ename, j.job_title, d.department_name
FROM employee e
JOIN job j ON e.job_id = j.job_id
JOIN department d ON e.dept_id = d.dept_id
WHERE e.ename = 'Steven King';

SELECT j.job_title,
       AVG(e.salary) AS avg_salary,
       MIN(e.salary) AS min_salary,
       MAX(e.salary) AS max_salary
FROM employee e
JOIN job j ON e.job_id = j.job_id
GROUP BY j.job_title
ORDER BY avg_salary DESC;
