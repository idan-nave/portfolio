package journal;

public class InvalidActionException extends Exception {

    // Constructor to accept a custom message
    public InvalidActionException(String message) {
        super(message);
    }

    // ###### Action validation checks for employee data ######

    // ######Non-Premium actions ######

    public static void validateJournalCreation(User user) throws InvalidActionException {
        if (!user.isPremium) {
            throw new InvalidActionException(
                    "User" + user.getUserName() + "is not allowed to have more than one journal");
        }
    }

    // ###### Null Operations ######

    public static void validateJournalDeletion(User user) throws InvalidActionException {

    }

    public static void validateEntryDeletion(Journal journal) throws InvalidActionException {

    }

}
