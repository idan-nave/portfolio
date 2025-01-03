package library;

import java.util.Scanner;

public class LibraryApp {

    public static void main(String[] args) {
        Library library = new Library();
        Scanner scanner = new Scanner(System.in);

        // Populate the system with sample data (if any)
        RandomBookPopulator.populateLibraryWithRandomBooks(library, 6);

        // Start the console app
        runConsoleApp(library, scanner);
    }

    private static void runConsoleApp(Library library, Scanner scanner) {
        while (true) {
            displayMenu();
            int choice = getUserChoice(scanner);
            handleMenuOption(choice, library, scanner);
        }
    }

    private static void displayMenu() {
        System.out.println("\nLibrary System");
        System.out.printf("%-30s%-30s%-30s%n", "1. Add Book", "2. Borrow a Book", "3. Return a Book");
        System.out.printf("%-30s%-30s%-30s%n", "4. Show All Books", "5. Add Random Books", "6. Exit");
        System.out.print("\nChoose an option: ");
    }

    private static int getUserChoice(Scanner scanner) {
        try {
            return scanner.nextInt();
        } catch (Exception e) {
            System.out.println("Invalid input. Please try again.");
            scanner.nextLine(); // Clear buffer
            return -1; // Return an invalid option
        }
    }

    private static void handleMenuOption(int choice, Library library, Scanner scanner) {
        scanner.nextLine(); // Consume the newline character from previous input

        switch (choice) {
            case 1 -> addBook(library, scanner);
            case 2 -> borrowBook(library, scanner);
            case 3 -> returnBook(library, scanner);
            case 4 -> library.listAllBooks();
            case 5 -> addRandomBooks(library, scanner);
            case 6 -> exitApp(scanner);
            default -> System.out.println("Invalid option. Please try again.");
        }
    }

    private static void addBook(Library library, Scanner scanner) {
        System.out.print("Enter book title: ");
        String title = scanner.nextLine();
        System.out.print("Enter author name: ");
        String author = scanner.nextLine();
        try {
            Book newBook = new Book(title, author);
            library.addBook(newBook);
            System.out.println("Book \"" + title + "\" by " + author + " added to the library.");
        } catch (IllegalArgumentException e) {
            System.out.println("Error adding book: " + e.getMessage());
        }
    }

    private static void borrowBook(Library library, Scanner scanner) {
        System.out.print("Enter book title to borrow: ");
        String borrowTitle = scanner.nextLine();
        System.out.print("Enter your name: ");
        String borrower = scanner.nextLine();
        try {
            library.borrowBook(borrowTitle, borrower);
        } catch (IllegalArgumentException e) {
            System.out.println("Error borrowing book: " + e.getMessage());
        }
    }

    private static void returnBook(Library library, Scanner scanner) {
        System.out.print("Enter book title to return: ");
        String returnTitle = scanner.nextLine();
        System.out.print("Enter your name: ");
        String returner = scanner.nextLine();
        try {
            library.returnBook(returnTitle, returner);
        } catch (IllegalArgumentException e) {
            System.out.println("Error returning book: " + e.getMessage());
        }
    }

    private static void addRandomBooks(Library library, Scanner scanner) {
        System.out.print("Enter the number of random books to add: ");
        int numRandomBooks = scanner.nextInt();
        try {
            RandomBookPopulator.populateLibraryWithRandomBooks(library, numRandomBooks);
            System.out.println(numRandomBooks + " random books added to the library.");
        } catch (IllegalArgumentException e) {
            System.out.println("Error adding random books: " + e.getMessage());
        }
    }

    private static void exitApp(Scanner scanner) {
        System.out.println("Exiting Library System.");
        scanner.close();
        System.exit(0); // Exit the program
    }
}
