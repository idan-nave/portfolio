# Library Management System

## Overview

This Java-based Library Management System allows users to add books, borrow them, return them, and view the entire library's collection. The application supports the following core features:

- **Book Management**: Add books to the library.
- **Borrow/Return Books**: Users can borrow or return books by providing their name.
- **Random Book Generation**: Populate the library with random books for testing or for convenience.
- **Custom Exception Handling**: Includes exceptions like `BorrowingException` and `OverDueException` to handle various scenarios like borrowing a book that's already taken or returning a book after its due date.
- **Menu-Driven Interface**: Interactive console menu that drives the system’s functionality.

## Table of Contents

1. [Installation](#installation)
2. [Usage](#usage)
3. [Classes and Functionality](#classes-and-functionality)
4. [Exceptions](#exceptions)
5. [Contributing](#contributing)
6. [License](#license)

---

## Installation

To run this project, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   ```
   
2. **Compile the project**:
   Open a terminal and navigate to the project folder. Compile the project using:
   ```bash
   javac *.java
   ```
   
3. **Run the Application**:
   Start the application by running:
   ```bash
   java LibraryApp
   ```

4. **Required Libraries**:
   This project is a simple console-based application and does not require external libraries.

---

## Usage

Upon running the program, you will be presented with a console menu with the following options:

1. **Add Book**: Adds a new book to the library by entering the book's title and author.
2. **Borrow a Book**: Allows a user to borrow a book by providing the title and their name.
3. **Return a Book**: Allows a user to return a book they previously borrowed.
4. **Show All Books**: Lists all books in the library with their status (borrowed or available).
5. **Add Random Books**: Populates the library with a specified number of randomly generated books (useful for testing).
6. **Exit**: Exits the program.

Example output when running the application:

```
Library System
1. Add Book
2. Borrow a Book
3. Return a Book
4. Show All Books
5. Add Random Books
6. Exit
Choose an option: 1
Enter book title: The Catcher in the Rye
Enter author name: J.D. Salinger
Book "The Catcher in the Rye" by J.D. Salinger added to the library.
```

---

## Classes and Functionality

### `LibraryApp` (Main Class)

This is the entry point of the program. It contains the main menu and drives the user interactions with the library system. The following operations are handled by `LibraryApp`:

- Displaying the menu and accepting user input.
- Calling methods to add, borrow, and return books.
- Displaying the list of all books in the library.
- Handling exceptions thrown during the borrowing or returning process.

### `Library` Class

This class manages the collection of books and handles all the operations related to the books. It includes:

- **addBook(Book book)**: Adds a book to the library.
- **findBook(String title)**: Finds and returns a book by its title.
- **borrowBook(String title, String borrower)**: Allows a user to borrow a book if available.
- **returnBook(String title, String borrower)**: Allows a user to return a borrowed book.
- **listAllBooks()**: Displays a summary of all books in the library.

### `Book` Class (Implements `Borrowable`)

Represents a book in the library. It has the following fields and methods:

- **Fields**:
  - `title`: The title of the book.
  - `author`: The author of the book.
  - `borrowedBy`: The borrower’s name (if the book is currently borrowed).
  - `isBorrowed`: Whether the book is currently borrowed.

- **Methods**:
  - `borrowItem(String borrower)`: Borrows the book. If it's already borrowed, an exception is thrown.
  - `returnItem(String borrower)`: Returns the book. If the borrower is not the one who borrowed it, an exception is thrown.

### `Borrowable` Interface

An interface implemented by classes (like `Book`) that can be borrowed. It has the following methods:

- `boolean borrowItem(String borrower)`: Borrow the item.
- `boolean returnItem(String borrower)`: Return the item.

### `RandomBookPopulator` Class

This utility class generates random books by selecting a title and an author from predefined lists. It includes the following methods:

- `generateRandomBook()`: Generates and returns a random book.
- `populateLibraryWithRandomBooks(Library library, int numBooks)`: Populates the library with a specified number of random books.

---

## Exceptions

### `BorrowingException` (Custom Exception)

This is a custom checked exception that is thrown in the following scenarios:

- A user tries to borrow a book that is already borrowed.
- A user tries to return a book they did not borrow.

**Constructor**:
- `BorrowingException(String message)`: Accepts a custom error message.

### `OverDueException` (Custom Exception)

This exception is thrown when a book is returned past its due date. It can be used for adding due dates to borrowed books and checking if a book is overdue.

**Constructor**:
- `OverDueException(String message)`: Accepts a custom error message indicating the book is overdue.

### Usage in Code:
```java
try {
    library.borrowBook("1984", "John Doe");
} catch (BorrowingException e) {
    System.out.println(e.getMessage());
}

try {
    library.returnBook("1984", "John Doe");
} catch (BorrowingException | OverDueException e) {
    System.out.println(e.getMessage());
}
```

---

## Extras

In addition to the core features, you can implement the following enhancements:

- **Create a Magazine or DVD**: Create a `Magazine` or `DVD` class that also implements `Borrowable`. These can have unique borrowing rules like limited time periods.
- **Track Due Date**: Add a due date to borrowed books and throw an `OverDueException` if the book is returned late. This will require tracking the date when a book is borrowed.
- **Logging**: You can add logging to keep track of actions such as borrowing and returning books, which will provide more informative messages when operations succeed or fail.

---

## Contributing

If you would like to contribute to this project, feel free to fork the repository, create a branch, and submit a pull request. Please ensure your contributions adhere to the following guidelines:

- Keep the code clean and well-documented.
- Write unit tests for any new functionality.
- Ensure all exceptions are handled gracefully.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

---

**End of README**
