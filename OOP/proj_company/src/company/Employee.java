package company;

import java.util.ArrayList;
import java.util.List;

public class Employee extends Person {
    // Salary type constant for global employees (isHourly = false means global
    // salary)
    private boolean isHourly; // true for hourly, false for global
    protected boolean isManager;
    private double baseSalary;
    protected double managersBonus; // constant monthly bonus for managers
    protected int vacationDays;
    protected int sicknessDays;
    private List<Double> loggedHours; // Logged hours for each day in the month (indexed by day)

    // Monthly bonus and rating arrays (12 months)
    private double[] monthlyBonuses = new double[12]; // Monthly bonuses for each month
    private int[] monthlyRatings = new int[12]; // Monthly ratings (1 to 5)

    private static final int MAX_DAYS_IN_MONTH = 31; // Max days in a month
    private static final int MIN_MONTHLY_HOURS = 160; // Minimum hours for global salary employee

    // Default constructor that generates a random employee
    public Employee() throws InvalidInputException {
        super(); // Call the Person's default constructor
        this.isHourly = Math.random() > 0.5; // Randomly assign hourly or global salary
        this.isManager = false;
        this.baseSalary = generateRandomBaseSalary();
        this.managersBonus = 0.0;
        this.vacationDays = 20; // Default vacation days
        this.sicknessDays = 10; // Default sickness days
        this.loggedHours = new ArrayList<>(MAX_DAYS_IN_MONTH);

        // Initialize logged hours for each day of the month as 0
        for (int i = 0; i < MAX_DAYS_IN_MONTH; i++) {
            loggedHours.add(0.0);
        }

        // Initialize monthly bonuses and ratings with default values (0 bonus and 3
        // rating)
        for (int i = 0; i < 12; i++) {
            monthlyBonuses[i] = 0.0;
            monthlyRatings[i] = 3; // Default rating of 3 (neutral rating)
        }
    }

    // Constructor for a specific Employee with name, age, company, and salary
    public Employee(String name, int age, Company company, double baseSalary, boolean isHourly)
            throws InvalidInputException {
        super(name, age, company);

        // Validate inputs
        InvalidInputException.checkSalary(baseSalary); // Validate base salary
        InvalidInputException.checkSalaryType(isHourly); // Check if hourly is true or false
        InvalidInputException.checkVacationDays(20); // Initialize vacation days (e.g., 20 days)
        InvalidInputException.checkSicknessDays(10); // Initialize sickness days (e.g., 10 days)

        this.baseSalary = baseSalary;
        this.isHourly = isHourly;
        this.isManager = false;
        this.managersBonus = 0.0;
        this.vacationDays = 20; // Default vacation days
        this.sicknessDays = 10; // Default sickness days
        this.loggedHours = new ArrayList<>(MAX_DAYS_IN_MONTH);

        // Initialize logged hours for each day of the month as 0
        for (int i = 0; i < MAX_DAYS_IN_MONTH; i++) {
            loggedHours.add(0.0);
        }

        // Initialize monthly bonuses and ratings with default values (0 bonus and 3
        // rating)
        for (int i = 0; i < 12; i++) {
            monthlyBonuses[i] = 0.0;
            monthlyRatings[i] = 3; // Default rating of 3 (neutral rating)
        }
    }

    // Method to generate a random base salary between 30,000 and 80,000
    private double generateRandomBaseSalary() {
        return Math.random() * 50000 + 30000;
    }

    // Methods to take vacation or sickness days
    public boolean takeVacationDays(int days) throws InvalidInputException {
        InvalidInputException.checkVacationDays(vacationDays - days); // Ensure valid vacation day deduction
        if (vacationDays >= days) {
            vacationDays -= days;
            return true;
        }
        return false; // Not enough vacation days
    }

    public boolean takeSicknessDays(int days) throws InvalidInputException {
        InvalidInputException.checkSicknessDays(sicknessDays - days); // Ensure valid sickness day deduction
        if (sicknessDays >= days) {
            sicknessDays -= days;
            return true;
        }
        return false; // Not enough sickness days
    }

    // Method to log working hours for a specific day
    public void logWorkingHours(int day, double hours) throws InvalidInputException {
        InvalidInputException.checkDayOfMonth(day); // Ensure valid day
        InvalidInputException.checkLoggedHours(hours); // Ensure valid hours worked
        loggedHours.set(day - 1, hours); // Set the hours for the given day (all employees)
    }

    // Method to get the hours worked on a specific day
    public double getHoursWorkedOnDay(int day) throws InvalidInputException {
        InvalidInputException.checkDayOfMonth(day); // Ensure valid day
        return loggedHours.get(day - 1);
    }

    // Method to calculate the employee's paycheck
    public double calculatePaycheck() {
        double paycheck = 0;
        if (isHourly) {
            paycheck = calculateHourlyPaycheck();
        } else {
            paycheck = calculateGlobalPaycheck();
        }
        return paycheck;
    }

    // Calculate paycheck for hourly employees
    private double calculateHourlyPaycheck() {
        double totalWorkedHours = getTotalLoggedHours();
        return totalWorkedHours * baseSalary + managersBonus; // hourly pay = hours worked * hourly rate + managersBonus (if any)
    }

    // Calculate paycheck for global salary employees
    private double calculateGlobalPaycheck() {
        double totalLoggedHours = getTotalLoggedHours();
        if (totalLoggedHours < MIN_MONTHLY_HOURS) {
            return totalLoggedHours * (baseSalary / MIN_MONTHLY_HOURS); // Calculate pay based on worked hours if less
                                                                        // than minimum and no bonus :-(
        }
        return baseSalary + managersBonus; // Pay the full salary if the minimum hours are met
    }

    // Helper method to get the total logged hours
    private double getTotalLoggedHours() {
        double total = 0;
        for (double hours : loggedHours) {
            total += hours;
        }
        return total;
    }

    // Getter and Setter for Monthly Bonuses and Ratings (accessible by Manager)
    public double getMonthlyBonus(int month) throws InvalidInputException {
        InvalidInputException.checkMonth(month); // Validate month range
        return monthlyBonuses[month - 1];
    }

    public void setMonthlyBonus(int month, double bonus) throws InvalidInputException {
        InvalidInputException.checkMonth(month); // Validate month range
        InvalidInputException.checkBonusAmount(bonus); // Validate bonus value
        this.monthlyBonuses[month - 1] = bonus;
    }

    public int getMonthlyRating(int month) throws InvalidInputException {
        InvalidInputException.checkMonth(month); // Validate month range
        return monthlyRatings[month - 1];
    }

    public void setMonthlyRating(int month, int rating) throws InvalidInputException {
        InvalidInputException.checkMonth(month); // Validate month range
        InvalidInputException.checkRating(rating); // Validate rating (1 to 5)
        this.monthlyRatings[month - 1] = rating;
    }

    // Method to print employee details (overridden to include salary type and days
    // off)
    @Override
    public String toString() {
        return super.toString() +
                ", Salary Type: " + (isHourly ? "Hourly" : "Global") +
                ", Base Salary: " + baseSalary +
                ", Vacation Days: " + vacationDays +
                ", Sickness Days: " + sicknessDays +
                ", Total Logged Hours: " + getTotalLoggedHours();
    }

    // Main method for testing the Employee class
    public static void main(String[] args) {
        try {
            // Create a company instance
            Company company1 = new Company("Tech Corp", "Tel-Aviv");

            // Create a global salary employee
            Employee employee1 = new Employee("Alice", 30, company1, 50000, false);
            employee1.logWorkingHours(5, 8); // Log some hours worked on day 5
            employee1.takeVacationDays(5); // Take some vacation days
            employee1.setMonthlyBonus(5, 1000); // Set a bonus for May
            employee1.setMonthlyRating(5, 4); // Set a rating for May

            // Create an hourly salary employee
            Employee employee2 = new Employee("Bob", 25, company1, 20, true);
            employee2.logWorkingHours(10, 8); // Log some hours worked on day 10
            employee2.setMonthlyBonus(10, 500); // Set a bonus for October
            employee2.setMonthlyRating(10, 5); // Set a rating for October

            // Print employee details and calculate paychecks
            System.out.println(employee1);
            System.out.println("Employee 1 Paycheck: " + employee1.calculatePaycheck());

            System.out.println(employee2);
            System.out.println("Employee 2 Paycheck: " + employee2.calculatePaycheck());

            // Test accessing and modifying bonuses and ratings
            System.out.println("Employee 1 Bonus for May: " + employee1.getMonthlyBonus(5));
            System.out.println("Employee 1 Rating for May: " + employee1.getMonthlyRating(5));

            System.out.println("Employee 2 Bonus for October: " + employee2.getMonthlyBonus(10));
            System.out.println("Employee 2 Rating for October: " + employee2.getMonthlyRating(10));
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
