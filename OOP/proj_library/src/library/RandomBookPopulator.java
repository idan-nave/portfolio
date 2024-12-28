package library;

import java.util.List;
import java.util.Random;

public class RandomBookPopulator {

    // Predefined lists of titles and authors
    private static final List<String> titles = List.of(
        "The Catcher in the Rye", "To Kill a Mockingbird", "1984", "The Great Gatsby", 
        "Moby Dick", "War and Peace", "Pride and Prejudice", "The Odyssey", "Ulysses", 
        "The Lord of the Rings"
    );
    
    private static final List<String> authors = List.of(
        "J.D. Salinger", "Harper Lee", "George Orwell", "F. Scott Fitzgerald", 
        "Herman Melville", "Leo Tolstoy", "Jane Austen", "Homer", "James Joyce", 
        "J.R.R. Tolkien"
    );

    // Random number generator
    private static final Random random = new Random();

    /**
     * Generates a random book using a random title and author from predefined lists.
     * @return a new Book object with a random title and author
     */
    public static Book generateRandomBook() {
        // Select random title and author
        String randomTitle = titles.get(random.nextInt(titles.size()));
        String randomAuthor = authors.get(random.nextInt(authors.size()));

        // Create and return a new Book object
        return new Book(randomTitle, randomAuthor);
    }

    /**
     * Populates the library with a specified number of random books.
     * @param library the library to populate
     * @param numBooks the number of books to add to the library
     */
    public static void populateLibraryWithRandomBooks(Library library, int numBooks) {
        for (int i = 0; i < numBooks; i++) {
            Book randomBook = generateRandomBook();
            library.addBook(randomBook);
            System.out.println("Random Book \"" + randomBook.getTitle() + "\" by " + randomBook.getAuthor() + " added to the library.");
        }
    }
}
