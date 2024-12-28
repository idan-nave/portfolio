package library;

import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * The main application that drives the interaction with the library system.
 */
public class LibraryApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Library library = new Library();

        while (true) {
            // Menu options
            System.out.println("\nLibrary System");
            System.out.println("1. Add Book");
            System.out.println("2. Borrow a Book");
            System.out.println("3. Return a Book");
            System.out.println("4. Show All Books");
            System.out.println("5. Add Random Books");
            System.out.println("6. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume the newline left by nextInt()

            try {
                switch (choice) {
                    case 1:
                        // Add Book
                        System.out.print("Enter book title: ");
                        String title = scanner.nextLine();
                        System.out.print("Enter author name: ");
                        String author = scanner.nextLine();
                        Book newBook = new Book(title, author);
                        library.addBook(newBook);
                        System.out.println("Book \"" + title + "\" by " + author + " added to the library.");
                        break;

                    case 2:
                        // Borrow a Book
                        System.out.print("Enter book title to borrow: ");
                        String borrowTitle = scanner.nextLine();
                        System.out.print("Enter your name: ");
                        String borrower = scanner.nextLine();
                        library.borrowBook(borrowTitle, borrower);
                        break;

                    case 3:
                        // Return a Book
                        System.out.print("Enter book title to return: ");
                        String returnTitle = scanner.nextLine();
                        System.out.print("Enter your name: ");
                        String returner = scanner.nextLine();
                        library.returnBook(returnTitle, returner);
                        break;

                    case 4:
                        // Show All Books
                        library.listAllBooks();
                        break;

                    case 5:
                        // Add Random Books
                        System.out.print("Enter the number of random books to add: ");
                        int numRandomBooks = scanner.nextInt();
                        RandomBookPopulator.populateLibraryWithRandomBooks(library, numRandomBooks);
                        break;

                    case 6:
                        // Exit
                        System.out.println("Exiting Library System.");
                        scanner.close();
                        return;

                    default:
                        System.out.println("Invalid option. Please try again.");
                }

            } catch (InputMismatchException e) {
                System.out.println("Invalid Input. Please enter a valid option.");
                scanner.nextLine(); // Consume invalid input
            }
        }
    }
}
