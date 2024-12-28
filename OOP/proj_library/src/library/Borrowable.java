package library;

/**
 * This interface defines the basic operations for items that can be borrowed from the library.
 */
public interface Borrowable {
    boolean borrowItem(String borrower) throws BorrowingException;
    boolean returnItem(String borrower) throws BorrowingException;
}
