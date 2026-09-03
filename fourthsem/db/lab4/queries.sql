SELECT CustomerName
FROM Customer
WHERE Address = 'Lalitpur'
ORDER BY CustomerName ASC;

SELECT COUNT(DISTINCT CustomerID) AS TotalCustomersWithLoan
FROM Borrows;

SELECT DISTINCT C.CustomerName
FROM Customer C
JOIN Borrows B ON C.CustomerID = B.CustomerID
JOIN Loan L ON B.LoanNumber = L.LoanNumber
WHERE L.Amount >= 500000;

SELECT LoanType, AVG(Amount) AS AvgLoanAmount
FROM Loan
GROUP BY LoanType;

