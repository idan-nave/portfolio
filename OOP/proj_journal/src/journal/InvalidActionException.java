package journal;

public class InvalidActionException extends Exception {

    // Constructor to accept a custom message
    public InvalidActionException(String message) {
        super(message);
    }

    // ###### Action validation checks for employee data ######

    // ######Non-Premium actions ######

    public static void validateJournalCreationApproval(User user) throws InvalidActionException {
        if (!user.isPremium && user.getJournalCount() >= User.MAX_JOURNALS) {
            throw new InvalidActionException(
                    "User" + user.getUserName() + "is not allowed to have more than " + User.MAX_JOURNALS + " journals");
        }
    }

    public static void validateEntryCreationApproval(User user) throws InvalidActionException {
        if (!user.isPremium && user.journals.get(0).getEntryCount() >= User.MAX_ENTRIES) {
            throw new InvalidActionException(
                    "User" + user.getUserName() + "is not allowed to have more than " + User.MAX_ENTRIES + " entries");
        }
    }
    // ###### Null Operations ######

    public static void validateJournalDeletion(User user) throws InvalidActionException {

    }

    public static void validateEntryDeletion(Journal journal) throws InvalidActionException {

    }

}
