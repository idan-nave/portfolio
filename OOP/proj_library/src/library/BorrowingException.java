package library;

/**
 * Custom exception for handling errors related to borrowing and returning items from the library.
 */
public class BorrowingException extends Exception {
    
    public BorrowingException(String message) {
        super(message);
    }

    // Exception messages
    public static String alreadyBorrowed(String title, String borrower) {
        return "The book \"" + title + "\" is already borrowed by " + borrower + ".";
    }

    public static String notBorrowedByUser(String title, String borrower) {
        return "The book \"" + title + "\" was not borrowed by " + borrower + ".";
    }

    public static String overdueMessage(String title, String borrower, String dueDate) {
        return "The book \"" + title + "\" borrowed by " + borrower + " is overdue since " + dueDate + ".";
    }
}
