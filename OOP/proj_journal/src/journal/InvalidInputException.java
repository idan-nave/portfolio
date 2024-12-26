package journal;

public class InvalidInputException extends Exception {

    // Constructor to accept a custom message
    public InvalidInputException(String message) {
        super(message);
    }

    // Input validation checks for employee data

    // Validate title name (should not be empty or null)
    public static void checkName(String mame) throws InvalidInputException {
        if (mame == null || mame.trim().isEmpty()) {
            throw new InvalidInputException("Name cannot be empty or null");
        }
    }

    public static void validateUserExists(User user) throws InvalidInputException {
        if (user == null) {
            throw new InvalidInputException("null user passed");
        }
    }


    // Validate 31 Months
    public static void checkDayOfMonth(int day) throws InvalidInputException {
        if (day < 1 || day > 31) {
            throw new InvalidInputException("Invalid day of the month: " + day + ". Day must be between 1 and 31.");
        }
    }

    // Validate 12 Months
    public static void checkMonth(int month) throws InvalidInputException {
        if (month < 1 || month > 12) {
            throw new InvalidInputException("Invalid month: " + month + ". Month must be between 1 and 12.");
        }
    }

    // Validate 24 Hours
    public static void checkLoggedHours(double hours) throws InvalidInputException {
        if (hours < 0 || hours > 24) {
            throw new InvalidInputException(
                    "Invalid number of hours logged: " + hours + ". Hours should be between 0 and 24.");
        }
    }

}
