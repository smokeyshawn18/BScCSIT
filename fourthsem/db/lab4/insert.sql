-- Insert Customers
INSERT INTO Customer (CustomerID, CustomerName, Address, Phone, Email) VALUES
(1, 'Aarav Shrestha', 'Lalitpur', '9800000001', 'aarav@example.com'),
(2, 'Sita Sharma', 'Kathmandu', '9800000002', 'sita@example.com'),
(3, 'Bikash Koirala', 'Lalitpur', '9800000003', 'bikash@example.com'),
(4, 'Rita Gurung', 'Pokhara', '9800000004', 'rita@example.com'),
(5, 'Kiran Lama', 'Bhaktapur', '9800000005', 'kiran@example.com');

-- Insert Loans
INSERT INTO Loan (LoanNumber, LoanType, Amount) VALUES
(101, 'Home Loan', 800000),
(102, 'Car Loan', 300000),
(103, 'Education Loan', 500000),
(104, 'Personal Loan', 200000),
(105, 'Home Loan', 1000000);

-- Insert Borrows (relationships)
INSERT INTO Borrows (CustomerID, LoanNumber) VALUES
(1, 101),   -- Aarav took Home Loan (800000)
(2, 102),   -- Sita took Car Loan (300000)
(3, 103),   -- Bikash took Education Loan (500000)
(4, 104),   -- Rita took Personal Loan (200000)
(1, 105);   -- Aarav also took another Home Loan (1000000)
