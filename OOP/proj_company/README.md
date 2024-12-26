# Company Management System - README

## Overview

The Company Management System is a comprehensive software solution designed to manage companies, employees, clients, and performance metrics. The project includes classes to represent different types of persons (including employees, managers, and clients) and their interactions within a company. It allows for tracking employee details, calculating paychecks, managing employee benefits (e.g., vacation, bonuses), and tracking client spendings.

This project uses Object-Oriented Programming (OOP) principles and provides functionality to manage and interact with these entities.

### Key Features:
1. **Company**: Represents a company with a unique ID, name, location, and a list of employees.
2. **Person**: Base class for entities like employees, managers, and clients.
3. **Employee**: Represents an employee, including details such as salary, working hours, vacation days, and monthly ratings and bonuses.
4. **Manager**: Extends the Employee class, with additional responsibilities of managing employees, assigning performance ratings, and handling bonuses.
5. **Client**: Represents a client, with functionality for tracking spending history and calculating total expenditures.

### Technologies Used:
- Java (JDK 11 or higher recommended)
- Object-Oriented Programming (OOP)

---

## Table of Contents

1. [Project Structure](#project-structure)
2. [Installation & Setup](#installation-setup)
3. [Usage Instructions](#usage-instructions)
4. [Main Classes Overview](#main-classes-overview)
5. [Compilation & Execution](#compilation-execution)
6. [Error Handling](#error-handling)
7. [License](#license)

---

## Project Structure

The project is organized into the following directories:

```
CompanyManagementSystem/
├── src/
│   └── company/
│       ├── Company.java
│       ├── Employee.java
│       ├── InvalidInputException.java
│       ├── Client.java
│       ├── Manager.java
│       ├── Person.java
│       └── Main.java
├── bin/           # Compiled class files (generated after compilation)
└── README.md      # Project documentation
```

### Key Files:

- **Company.java**: Contains the `Company` class that holds the company's information and employees.
- **Employee.java**: Contains the `Employee` class with methods to log working hours, calculate paychecks, and manage vacation days.
- **Manager.java**: Extends the `Employee` class and adds functionality for employee management and performance ratings.
- **Client.java**: Represents a client, allowing them to spend money and track their spending history.
- **Person.java**: A base class for both `Employee` and `Client` classes.
- **InvalidInputException.java**: Custom exception class for input validation errors.
- **Main.java**: The main class that demonstrates the functionality of the entire system, including creating companies, employees, clients, and managers.

---

## Installation & Setup

To set up and run the project, follow these steps:

1. **Clone the repository (if applicable)**:
   ```bash
   git clone https://your-repository-link
   ```

2. **Navigate to the project directory**:
   ```bash
   cd CompanyManagementSystem
   ```

3. **Ensure you have Java installed**:
   Check your Java version:
   ```bash
   java -version
   ```

   If Java is not installed, download and install the latest JDK from [Oracle](https://www.oracle.com/java/technologies/javase-jdk11-downloads.html).

---

## Usage Instructions

To run the program, you need to compile and execute the Java classes. Here's how to do it:

### Compilation

1. **Compile the source code** using the `javac` command:
   ```bash
   javac -d bin src/company/*.java
   ```

   This will compile all the Java files in the `src/company/` directory and place the compiled `.class` files in the `bin/` directory.

### Execution

2. **Run the program**:
   After compiling, run the main class with the `java` command:
   ```bash
   java -cp bin company.Main
   ```

   This will execute the `Main` class, which contains the demonstration of all the features, such as managing employees, tracking spendings for clients, and assigning performance ratings to employees.

---

## Main Classes Overview

### 1. **Company Class**

This class represents a company. It contains:
- A unique company ID (generated with `UUID`).
- The company name and location.
- A list of employees working for the company.
  
**Key Methods**:
- `addEmployee(Employee employee)`: Adds an employee to the company.
- `removeEmployee(Employee employee)`: Removes an employee from the company.
- `displayCompanyDetails()`: Displays the company's details and its employees.

### 2. **Person Class**

This is a base class that holds common attributes for all people in the system (both employees and clients):
- `id`, `name`, `age`, `company`.

### 3. **Employee Class**

Represents an employee with specific attributes like salary, vacation days, bonuses, and ratings. Includes methods to:
- Log working hours.
- Track vacation days.
- Set monthly ratings and bonuses.
- Calculate paychecks based on salary or hourly rates.

### 4. **Manager Class**

Extends the `Employee` class and adds additional functionality for:
- Managing a team of employees.
- Assigning performance ratings to employees.
- Handling a monthly bonus for the manager.

### 5. **Client Class**

Represents a client who can:
- Spend money, which is tracked in a spending history.
- Print the total spending and detailed history.

### 6. **InvalidInputException Class**

A custom exception class to handle validation errors in input, ensuring that no invalid data is passed.

---

## Compilation & Execution

### Step-by-Step Instructions:

1. **Navigate to the project directory**:
   ```bash
   cd CompanyManagementSystem
   ```

2. **Compile all Java files**:
   ```bash
   javac -d bin src/company/*.java
   ```

3. **Run the program**:
   ```bash
   java -cp bin company.Main
   ```

---

## Error Handling

The project uses custom error handling with the `InvalidInputException` class. This exception is thrown when an invalid input is encountered, such as:
- Invalid age, salary, or other numeric values.
- Invalid company information or client data.

When an exception is thrown, an appropriate error message will be displayed.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

### Conclusion

The **Company Management System** offers a robust solution for managing employees, clients, and company operations. With features such as employee salary calculations, vacation tracking, performance ratings, and client spending management, the system provides a complete toolset for running and managing a business. This README should help you get started with compiling and running the project, as well as understanding the core functionality.
