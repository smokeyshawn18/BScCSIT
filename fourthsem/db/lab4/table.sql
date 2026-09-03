-- Customer Table
CREATE TABLE Customer (
    CustomerID INT PRIMARY KEY,
    CustomerName VARCHAR(100),
    Address VARCHAR(100),
    Phone VARCHAR(20),
    Email VARCHAR(100)
);

-- Loan Table
CREATE TABLE Loan (
    LoanNumber INT PRIMARY KEY,
    LoanType VARCHAR(50),
    Amount DECIMAL(12,2)
);

-- Borrows Table (bridge table)
CREATE TABLE Borrows (
    CustomerID INT,
    LoanNumber INT,
    PRIMARY KEY (CustomerID, LoanNumber),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
    FOREIGN KEY (LoanNumber) REFERENCES Loan(LoanNumber)
);
