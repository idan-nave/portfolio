package company;

import java.util.ArrayList;
import java.util.List;

public class Manager extends Employee {
    private List<Employee> employeesUnderManagement; // List of employees this manager is responsible for

    // Constructor to initialize Manager with basic Employee details
    public Manager(String name, int age, Company company, double salary, boolean isFullTime) throws InvalidInputException {
        super(name, age, company, salary, isFullTime);  // Call Employee constructor
        this.employeesUnderManagement = new ArrayList<>();
        
        // Managers have better benefits (e.g., more sick days, vacation days, and higher bonuses)
        this.sicknessDays = 20;  // Example base sick leave for managers
        this.vacationDays = 25;  // Example base vacation days for managers
		super.isManager = true;
        super.managersBonus = 1500.0;  // Example monthly bonus for managers
    }

    // Method to add an employee to the manager's list of employees
    public void addEmployee(Employee employee) throws InvalidInputException {
        if (employee == null) {
            throw new InvalidInputException("Employee cannot be null.");
        }
        employeesUnderManagement.add(employee);
    }

    // Method to remove an employee from the manager's list of employees
    public void removeEmployee(Employee employee) {
        employeesUnderManagement.remove(employee);
    }

    // Method to assign a performance rating to an employee
    public void assignPerformanceRating(Employee employee, int month, int rating) throws InvalidInputException {
        if (employee == null) {
            throw new InvalidInputException("Employee cannot be null.");
        }
        InvalidInputException.checkMonth(month); // Validate month range
        InvalidInputException.checkRating(rating); // Validate rating (1 to 5)

        // Assuming Employee has a performanceRating field (which we'll need to add)
        employee.setMonthlyRating(month, rating);
    }

    // Getter for employees under management
    public List<Employee> getEmployeesUnderManagement() {
        return employeesUnderManagement;
    }

    // Override toString to include the list of employees under management
    @Override
    public String toString() {
        return super.toString() + ", Managed Employees: " + employeesUnderManagement.size();
    }

    // Main method to test the Manager class
    public static void main(String[] args) {
        try {
            // Create a company
            Company company = new Company("Tech Innovators", "Los Angeles");

            // Create a manager
            Manager manager = new Manager("Alice", 35, company, 80000, true);

            // Create employees
            Employee employee1 = new Employee("Bob", 28, company, 50000, true);
            Employee employee2 = new Employee("Charlie", 30, company, 55000, false);

            // Add employees to manager
            manager.addEmployee(employee1);
            manager.addEmployee(employee2);

            // Assign performance ratings
            manager.assignPerformanceRating(employee1, 1, 4);
            manager.assignPerformanceRating(employee2, 2, 3);

            // Display manager and their employees' details
            System.out.println(manager);
            System.out.println("Employees under management:");
            for (Employee emp : manager.getEmployeesUnderManagement()) {
                System.out.println(emp);
            }

        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}

