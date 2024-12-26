package company;

public class InvalidInputException extends Exception {

    // Constructor to accept a custom message
    public InvalidInputException(String message) {
        super(message);
    }

    // Input validation checks for employee data

    // Check if a salary value is valid (should be positive)
    public static void checkSalary(double salary) throws InvalidInputException {
        if (salary < 0) {
            throw new InvalidInputException("Salary cannot be negative: " + salary);
        }
    }

    // Check if vacation days are valid (should be non-negative and within
    // reasonable limits)
    public static void checkVacationDays(int vacationDays) throws InvalidInputException {
        if (vacationDays < 0) {
            throw new InvalidInputException("Vacation days cannot be negative: " + vacationDays);
        }
        if (vacationDays > 365) {
            throw new InvalidInputException("Vacation days cannot exceed 365 days: " + vacationDays);
        }
    }

    // Check if sickness days are valid (should be non-negative and within
    // reasonable limits)
    public static void checkSicknessDays(int sicknessDays) throws InvalidInputException {
        if (sicknessDays < 0) {
            throw new InvalidInputException("Sickness days cannot be negative: " + sicknessDays);
        }
        if (sicknessDays > 365) {
            throw new InvalidInputException("Sickness days cannot exceed 365 days: " + sicknessDays);
        }
    }

    // Check if an employee's hours worked are valid
    public static void checkWorkingHours(double hours) throws InvalidInputException {
        if (hours < 0 || hours > 24) {
            throw new InvalidInputException("Invalid number of hours worked in a day: " + hours);
        }
    }

    // Check if an employee's rating is valid (must be between 1 and 5)
    public static void checkEmployeeRating(int rating) throws InvalidInputException {
        if (rating < 1 || rating > 5) {
            throw new InvalidInputException("Rating must be between 1 and 5: " + rating);
        }
    }

    // Check if an employee's bonus is valid (should be non-negative)
    public static void checkEmployeeBonus(double bonus) throws InvalidInputException {
        if (bonus < 0) {
            throw new InvalidInputException("Bonus cannot be negative: " + bonus);
        }
    }

    // Check if the monthly salary is correct for an hourly employee (should be
    // non-negative)
    public static void checkHourlySalary(double hourlySalary) throws InvalidInputException {
        if (hourlySalary < 0) {
            throw new InvalidInputException("Hourly salary cannot be negative: " + hourlySalary);
        }
    }

    // Validate employee work type (is it hourly or global)
    public static void checkSalaryType(boolean isHourly) throws InvalidInputException {
        // This is just an informational check to ensure we have two options: hourly or
        // global
        if (isHourly != true && isHourly != false) {
            throw new InvalidInputException("Invalid salary type: " + isHourly);
        }
    }

    // Validate company name (should not be empty or null)
    public static void checkCompanyName(String companyName) throws InvalidInputException {
        if (companyName == null || companyName.trim().isEmpty()) {
            throw new InvalidInputException("Company name cannot be empty or null");
        }
    }

    // Validate company address (should not be empty or null)
    public static void checkCompanyAddress(String address) throws InvalidInputException {
        if (address == null || address.trim().isEmpty()) {
            throw new InvalidInputException("Company address cannot be empty or null");
        }
    }

    // Validate company phone number (should be numeric and of valid length)
    public static void checkCompanyPhoneNumber(String phoneNumber) throws InvalidInputException {
        if (phoneNumber == null || phoneNumber.trim().isEmpty()) {
            throw new InvalidInputException("Phone number cannot be empty or null");
        }
        if (!phoneNumber.matches("\\d+")) {
            throw new InvalidInputException("Phone number must be numeric: " + phoneNumber);
        }
        if (phoneNumber.length() < 10 || phoneNumber.length() > 15) {
            throw new InvalidInputException("Phone number length must be between 10 and 15 digits: " + phoneNumber);
        }
    }

    // Check if an ID is valid (should not be negative or too high)
    public static void checkPersonID(long id) throws InvalidInputException {
        if (id < 100000000 || id > 999999999) {
            throw new InvalidInputException("Invalid ID: " + id + ". ID must be between 100000000 and 999999999");
        }
    }

    // Check if an age is valid (should be between 18 and 100)
    public static void checkAge(int age) throws InvalidInputException {
        if (age < 18 || age > 100) {
            throw new InvalidInputException("Invalid age: " + age + ". Age must be between 18 and 100");
        }
    }

    // Check if the day of the month is valid
    public static void checkDayOfMonth(int day) throws InvalidInputException {
        if (day < 1 || day > 31) {
            throw new InvalidInputException("Invalid day of the month: " + day + ". Day must be between 1 and 31.");
        }
    }

    // Check if the month is valid
    public static void checkMonth(int month) throws InvalidInputException {
        if (month < 1 || month > 12) {
            throw new InvalidInputException("Invalid month: " + month + ". Month must be between 1 and 12.");
        }
    }

    // Check if hours logged for a day are correct
    public static void checkLoggedHours(double hours) throws InvalidInputException {
        if (hours < 0 || hours > 24) {
            throw new InvalidInputException(
                    "Invalid number of hours logged: " + hours + ". Hours should be between 0 and 24.");
        }
    }

    // Validate a salary for a global employee (the value should be reasonable, e.g.
    // greater than 0)
    public static void checkGlobalSalary(double globalSalary) throws InvalidInputException {
        if (globalSalary <= 0) {
            throw new InvalidInputException("Global salary must be greater than 0: " + globalSalary);
        }
    }

    // Check the validity of employee work hours (0 to 24 hours per day)
    public static void checkWorkHoursForEmployee(double hoursWorked) throws InvalidInputException {
        if (hoursWorked < 0 || hoursWorked > 24) {
            throw new InvalidInputException(
                    "Invalid number of work hours: " + hoursWorked + ". Hours must be between 0 and 24.");
        }
    }

    // Check if a bonus is reasonable (e.g. not negative)
    public static void checkBonusAmount(double bonusAmount) throws InvalidInputException {
        if (bonusAmount < 0) {
            throw new InvalidInputException("Bonus amount cannot be negative: " + bonusAmount);
        }
    }

    // Check if a spending amount is reasonable (e.g. not negative)
    public static void checkSpendingAmount(double spendingAmount) throws InvalidInputException {
        if (spendingAmount < 0) {
            throw new InvalidInputException("Spending amount cannot be negative: " + spendingAmount);
        }
    }

    // Validate the rating given to an employee (rating should be between 1 and 5)
    public static void checkRating(int rating) throws InvalidInputException {
        if (rating < 1 || rating > 5) {
            throw new InvalidInputException("Invalid rating. Rating must be between 1 and 5.");
        }
    }

    // Validate if a person's name is valid (non-empty and non-null)
    public static void checkPersonName(String name) throws InvalidInputException {
        if (name == null || name.trim().isEmpty()) {
            throw new InvalidInputException("Name cannot be null or empty.");
        }
    }

    // Validate if an employee's logged hours are valid
    public static void checkEmployeeLoggedHours(int day, double hours) throws InvalidInputException {
        if (day < 1 || day > 31) {
            throw new InvalidInputException("Invalid day of the month: " + day + ". Day should be between 1 and 31.");
        }
        if (hours < 0 || hours > 24) {
            throw new InvalidInputException("Invalid hours worked: " + hours + ". Should be between 0 and 24.");
        }
    }

}
