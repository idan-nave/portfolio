package library;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.UUID;

/**
 * Represents a book in the library system. Each book has a title, author, and borrow status.
 */
public class Book implements Borrowable {

    private final String ID; // Unique ID for each book
    private final long MAX_BORROWING_DURATION = 14L;

    private String title;
    private String author;
    private String borrowedBy;
    private boolean isBorrowed;
    private Date dueDate;

    // Constructor for creating a book
    public Book(String title, String author) {
        this.ID = UUID.randomUUID().toString();
        this.title = title;
        this.author = author;
        this.isBorrowed = false;
        this.borrowedBy = null;
        this.dueDate = null;
    }

    @Override
    public boolean borrowItem(String borrower) throws BorrowingException {
        if (isBorrowed) {
            throw new BorrowingException(BorrowingException.alreadyBorrowed(title, borrowedBy));
        }
        isBorrowed = true;
        borrowedBy = borrower;
        setDueDate();
        return true;
    }

    @Override
    public boolean returnItem(String borrower) throws BorrowingException {
        if (!isBorrowed || !borrowedBy.equals(borrower)) {
            throw new BorrowingException(BorrowingException.notBorrowedByUser(title, borrower));
        }
        
        if (isOverDue()) {
            throw new BorrowingException(BorrowingException.overdueMessage(title, borrower, formatDate(dueDate)));
        }

        isBorrowed = false;
        borrowedBy = null;
        dueDate = null;
        return true;
    }

    /**
     * Set the due date for the book to MAX_BORROWING_DURATION (ms equivelent) days from the current date.
     */
    private void setDueDate() {
        long currentTime = System.currentTimeMillis();
        long dueTime = currentTime + (MAX_BORROWING_DURATION * 24 * 60 * 60 * 1000);
        dueDate = new Date(dueTime);
    }

    /**
     * Check if the book is overdue.
     * @return true if overdue, false otherwise
     */
    private boolean isOverDue() {
        return dueDate != null && new Date().after(dueDate);
    }

    /**
     * Format the date into a human-readable string.
     * @param date the date to format
     * @return formatted date string
     */
    private String formatDate(Date date) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        return sdf.format(date);
    }

    public String getTitle() {
        return title;
    }

    public String getAuthor() {
        return author;
    }

    public boolean isBorrowed() {
        return isBorrowed;
    }

    public String getBorrowedBy() {
        return borrowedBy;
    }

    public String getId() {
        return ID;
    }

    @Override
    public String toString() {
        return "Title: " + title + ", Author: " + author + ", Borrowed: " + (isBorrowed ? "Yes (by " + borrowedBy + ")" : "No");
    }
}
