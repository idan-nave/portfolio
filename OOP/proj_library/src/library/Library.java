package library;

import java.util.ArrayList;
import java.util.List;

/**
 * Manages the collection of books in the library. It allows operations such as adding, borrowing, returning,
 * and listing books.
 */
public class Library {
    private List<Book> books;

    public Library() {
        this.books = new ArrayList<>();
    }

    /**
     * Add a new book to the library.
     * @param book the book to add
     */
    public void addBook(Book book) {
        books.add(book);
    }

    /**
     * Find a book by its title.
     * @param title the title of the book to search for
     * @return the book object or null if not found
     */
    public Book findBook(String title) {
        for (Book book : books) {
            if (book.getTitle().equalsIgnoreCase(title)) {
                return book;
            }
        }
        return null;
    }

    /**
     * Borrow a book from the library.
     * @param title the title of the book to borrow
     * @param borrower the name of the person borrowing the book
     */
    public void borrowBook(String title, String borrower) {
        Book book = findBook(title);
        //if found
        if (book != null) {
            try {
                if (book.borrowItem(borrower)) {
                    System.out.println("Book \"" + title + "\" successfully borrowed by " + borrower);
                }
            } catch (BorrowingException e) {
                System.out.println(e.getMessage());
            }
        } else {
            System.out.println("Book \"" + title + "\" not found in the library.");
        }
    }

    /**
     * Return a borrowed book to the library.
     * @param title the title of the book to return
     * @param borrower the name of the person returning the book
     */
    public void returnBook(String title, String borrower) {
        Book book = findBook(title);
        //if found
        if (book != null) {
            try {
                if (book.returnItem(borrower)) {
                    System.out.println("Book \"" + title + "\" successfully returned by " + borrower);
                }
            } catch (BorrowingException e) {
                System.out.println(e.getMessage());
            }
        } else {
            System.out.println("Book \"" + title + "\" not found in the library.");
        }
    }

    /**
     * List all books in the library with their borrow status.
     */
    public void listAllBooks() {
        if (books.isEmpty()) {
            System.out.println("No books available in the library.");
        } else {
            for (Book book : books) {
                System.out.println(book);
            }
        }
    }
}
