package company;

public class Main {

    public static void main(String[] args) {
        try {
            // Create a company
            Company company = new Company("Tech Innovators", "Los Angeles");

            // Demonstrating Person class with and without companies
            Client personWithCompany = new Client("Alice", 30, company);
            Client personWithoutCompany = new Client("Bob", 40, null);
            printPersonDetails(personWithCompany, personWithoutCompany);

            // Demonstrating Client class and their spendings
            Client client1 = new Client("Charlie", 28, company);
            demonstrateClientSpendings(client1);

            // Demonstrating Employee class and paycheck calculation
            Employee employee1 = new Employee("David", 25, company, 50000, false);  // Salary employee
            Employee employee2 = new Employee("Eva", 30, company, 20, true);        // Hourly employee
            demonstrateEmployeeDetails(employee1, employee2);

            // Demonstrating Manager class, employee management, and performance ratings
            Manager manager = new Manager("Frank", 40, company, 80000, true);  // Manager with bonus
            manager.addEmployee(employee1);
            manager.addEmployee(employee2);
            manager.assignPerformanceRating(employee1, 1, 4);  // Rating for month 1
            manager.assignPerformanceRating(employee2, 2, 5);  // Rating for month 2
            demonstrateManagerDetails(manager);

        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    // Helper function to print Person details
    private static void printPersonDetails(Person personWithCompany, Person personWithoutCompany) {
        System.out.println("Person with company: " + personWithCompany);
        System.out.println("Person without company: " + personWithoutCompany);
    }

    // Helper function to demonstrate Client spendings
    private static void demonstrateClientSpendings(Client client) throws InvalidInputException {
        client.spendMoney(150.50);
        client.spendMoney(200.75);
        client.spendMoney(75.00);
        client.printSpendings();
    }

    // Helper function to demonstrate Employee details and paycheck
    private static void demonstrateEmployeeDetails(Employee employee1, Employee employee2)  throws InvalidInputException {
        // Logging hours and taking vacation days
        employee1.logWorkingHours(5, 8);  // Employee 1 works 8 hours on day 5
        employee2.logWorkingHours(10, 8); // Employee 2 works 8 hours on day 10
        employee1.takeVacationDays(2);    // Employee 1 takes 2 vacation days
        employee2.takeVacationDays(1);    // Employee 2 takes 1 vacation day

        // Set monthly bonus and rating
        employee1.setMonthlyBonus(5, 1000);   // Set bonus for May for Employee 1
        employee2.setMonthlyBonus(6, 500);    // Set bonus for June for Employee 2
        employee1.setMonthlyRating(5, 4);     // Set rating for May for Employee 1
        employee2.setMonthlyRating(6, 5);     // Set rating for June for Employee 2

        // Display employee details and calculate paychecks
        System.out.println(employee1);
        System.out.println("Employee 1 Paycheck: " + employee1.calculatePaycheck());
        System.out.println(employee2);
        System.out.println("Employee 2 Paycheck: " + employee2.calculatePaycheck());
    }

    // Helper function to demonstrate Manager details and employee management
    private static void demonstrateManagerDetails(Manager manager) {
        // Display Manager details
        System.out.println(manager);
        System.out.println("Employees under management:");
        for (Employee emp : manager.getEmployeesUnderManagement()) {
            System.out.println(emp);
        }
    }
}
