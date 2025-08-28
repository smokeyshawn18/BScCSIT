-- Create view
CREATE VIEW emp_salaries AS
SELECT emp_id, first_name, last_name, salary
FROM employee;

-- Display results from the view
SELECT * FROM emp_salaries;


CREATE VIEW high_earners AS
SELECT emp_id, first_name, last_name, salary
FROM employee
WHERE salary > 10000;

-- Display results
SELECT * FROM high_earners;


CREATE VIEW emp_dept AS
SELECT e.first_name, e.last_name, d.department_name
FROM employee e
JOIN department d ON e.dept_id = d.dept_id;

-- Display results
SELECT * FROM emp_dept;


DROP VIEW emp_salaries;
