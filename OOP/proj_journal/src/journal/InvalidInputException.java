package journal;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

/**
 * Custom exception to handle invalid input scenarios.
 */
public class InvalidInputException extends Exception {

    // Constructor that accepts a custom message
    public InvalidInputException(String message) {
        super(message);
    }

    // ###### User Validation Methods ######

    /**
     * Validates that a user does not already exist in the system.
     * 
     * @param userName The username to validate.
     * @throws InvalidInputException if the user already exists.
     */

    public static void validateUsernameNotExists(String userName) throws InvalidInputException {
        Path path = Paths.get(User.USERS_PATH + userName);

        if (Files.exists(path)) {
            throw new InvalidInputException(
                    "Username: " + userName + " already exists");
        }
    }

    /**
     * Validates that a user exist in the system.
     * 
     * @param userName The username to validate.
     * @throws InvalidInputException if the user already exists.
     */
    public static void validateUsernameExists(String userName) throws InvalidInputException {
        Path path = Paths.get(User.USERS_PATH + userName);

        if (!Files.exists(path)) {
            throw new InvalidInputException(
                    "Username: " + userName + " does not exist");
        }
    }

    /**
     * Validates that the user exists in the system.
     * 
     * @param user The user to validate.
     * @throws InvalidInputException if the user does not exist.
     */
    public static void validateUserExists(User user) throws InvalidInputException {
        Path path = Paths.get(User.USERS_PATH + user.getUserName());

        if (!Files.exists(path)) {
            throw new InvalidInputException(
                    "User Object: " + user.getUserName() + " does not exist");
        }
    }

    // ###### Subscription and Journal Validation ######

    /**
     * Validates that a jounnal exists in the system.
     * 
     * @param user The user to validate.
     * @throws InvalidInputException if the user does not exist.
     */
    public static void validateJournalExists(Journal journal) throws InvalidInputException {
        Path path = Paths.get("/users/" + journal.owner.getUserName() + "/" + journal.getTitle());

        if (!Files.exists(path)) {
            throw new InvalidInputException(
                    "Journal: " + journal.getTitle() + " does not exist");
        }
    }

    /**
     * Validates the user's subscription and journal entry limits.
     * 
     * @param user The user to validate.
     * @throws InvalidInputException if the user exceeds their limits.
     */
    public static void validateSubscription(User user) throws InvalidInputException {
        if (!user.isSubscribed()) {
            if (user.getJournalsCount() >= User.MAX_JOURNALS) {
                throw new InvalidInputException(
                        "User: " + user.getUserName() + " is not allowed to have more than "
                                + User.MAX_JOURNALS + " journals");
            }

            if (user.getTotalEntriesCount() >= User.MAX_ENTRIES) {
                throw new InvalidInputException(
                        "User: " + user.getUserName() + " is not allowed to have more than "
                                + User.MAX_ENTRIES + " entries");
            }
        }
    }

    // ###### Path and File Validation ######

    /**
     * Validates that a given file path exists.
     * 
     * @param path The path to validate.
     * @throws InvalidInputException if the path does not exist.
     */
    public static void validatePath(String path) throws InvalidInputException {
        Path filePath = Path.of(path);
        if (!Files.exists(filePath)) {
            throw new InvalidInputException("Path does not exist: " + path);
        }
    }

    // ###### Null and Object Existence Validation ######

    /**
     * Validates that an object is not null.
     * 
     * @param obj The object to validate.
     * @throws InvalidInputException if the object is null.
     */
    public static <T> void validateExists(T obj) throws InvalidInputException {
        if (obj == null) {
            throw new InvalidInputException("Passed object is null");
        }
    }

    /**
     * Validates that a string is neither null nor empty.
     * 
     * @param str The string to validate.
     * @throws InvalidInputException if the string is null or empty.
     */
    public static void validateString(String str) throws InvalidInputException {
        if (str == null || str.trim().isEmpty()) {
            throw new InvalidInputException("String cannot be empty or null");
        }
    }

    /**
     * Validates that an index is a positive integer (greater than or equal to 0).
     * 
     * @param index The index to validate.
     * @throws InvalidInputException if the index is negative.
     */
    public static void validatePositiveIndex(int index) throws InvalidInputException {
        if (index < 0) {
            throw new InvalidInputException("Index cannot be negative");
        }
    }

    /**
     * Validates that the given index is within the valid range of items in the
     * list.
     * 
     * @param items The list of items.
     * @param index The index to validate.
     * @throws InvalidInputException if the index is out of bounds of the list.
     */
    public static void validateItemIndexExist(List<Object> items, int index) throws InvalidInputException {
        if (index < 0 || index >= items.size()) {
            throw new InvalidInputException(
                    "Index " + index + " is out of bounds. The list has " + items.size() + " items.");
        }
    }

}
