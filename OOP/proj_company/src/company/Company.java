package company;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.Random;

public class Company {
    // Fields
    private String uid; // Unique identifier for each company
    private String name;
    private String location;
    private List<Employee> employees;

    // Constructor with company name and location
    public Company(String name, String location) throws InvalidInputException {
        this.uid = UUID.randomUUID().toString(); // Generate a unique uid for the company
        setName(name);  // Validate company name
        setLocation(location);  // Validate location
        this.employees = new ArrayList<>();
    }

    // Empty constructor that generates a random company with random employees
    public Company() throws InvalidInputException {
        this.uid = UUID.randomUUID().toString(); // Generate a unique uid for the company
        generateRandomCompany();
    }

    // Method to generate a random company with random employees
    private void generateRandomCompany() throws InvalidInputException {
        Random random = new Random();
        String[] companyNames = { "Tech Solutions", "Innovative Systems", "Future Enterprises", "Global Solutions",
                "Pioneering Technologies" };
        String[] locations = { "New York", "San Francisco", "Chicago", "London", "Berlin" };

        // Set random company name and location
        setName(companyNames[random.nextInt(companyNames.length)]);
        setLocation(locations[random.nextInt(locations.length)]);

        // Create random employees for the company
        int employeeCount = random.nextInt(5) + 1; // Random number of employees (1 to 5)
        this.employees = new ArrayList<>();
        for (int i = 0; i < employeeCount; i++) {
            employees.add(new Employee()); // Add random employees
        }
    }

    // Method to add employees
    public void addEmployee(Employee employee) throws InvalidInputException {
        if (employee == null) {
            throw new InvalidInputException("Employee cannot be null.");
        }
        employees.add(employee);
    }

    public void removeEmployee(Employee employee) {
        employees.remove(employee);
    }

    // Setter methods for name and location with validation
    public void setName(String name) throws InvalidInputException {
        if (name == null || name.isEmpty()) {
            throw new InvalidInputException("Company name cannot be null or empty.");
        }
        this.name = name;
    }

    public void setLocation(String location) throws InvalidInputException {
        if (location == null || location.isEmpty()) {
            throw new InvalidInputException("Location cannot be null or empty.");
        }
        this.location = location;
    }

    // Getter methods for company details
    public String getId() {
        return uid;
    }

    public String getName() {
        return name;
    }

    public String getLocation() {
        return location;
    }

    public List<Employee> getEmployees() {
        return employees;
    }

    // Method to display company details
    public void displayCompanyDetails() {
        System.out.println("Company uid: " + uid);
        System.out.println("Company Name: " + name);
        System.out.println("Location: " + location);
        System.out.println("Employees:");
        for (Employee employee : employees) {
            System.out.println(employee);
        }
    }

    // Main method to test the Company class
    public static void main(String[] args) {
        try {
            // Create a random company using the empty constructor
            Company randomCompany = new Company();

            // Display the random company's details
            randomCompany.displayCompanyDetails();

            // Create a custom company with name and location
            Company customCompany = new Company("Tech Innovators", "Los Angeles");

            // Add employees to the custom company
            Employee employee1 = new Employee("Alice", 30, randomCompany, 50000, false);
            Employee employee2 = new Employee("Bob", 25, randomCompany, 2000, true);

            customCompany.addEmployee(employee1);
            customCompany.addEmployee(employee2);

            // Display custom company details
            customCompany.displayCompanyDetails();
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
