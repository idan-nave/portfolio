package journal;

public class EntryTester {
    public static void main(String[] args) {
        try {
            // 1. Create a new user
            System.out.println("Creating a new user...");
            User user = new User("alice_smith");

            // Display initial state of the user
            System.out.println(user);  // Using toString() method to show user details

            // 2. Subscribe the user
            System.out.println("\nSubscribing the user...");
            user.subscribe();
            System.out.println(user);  // Show user info after subscription

            // 3. Create a new journal for the user
            System.out.println("\nCreating a new journal...");
            Journal journal = new Journal("Travel Journal", user);
            System.out.println(journal);  // Show journal details after creation

            // 4. Add entries to the journal
            System.out.println("\nAdding entries to the journal...");
            Entry entry1 = new Entry("Day 1: Arrival", journal);
            journal.addEntry(entry1); // Add first entry to journal
            System.out.println(journal);  // Show journal details after adding entry

            // 5. Add items to the entry
            System.out.println("\nAdding items to the entry...");
            entry1.addItem("Photo: Arrival at the airport");
            entry1.addItem("Text: It was a long flight.");
            System.out.println(entry1);  // Show entry details after adding items

            // 6. Modify an item in the entry
            System.out.println("\nModifying an item in the entry...");
            entry1.setItem(1, "Text: It was an exhausting but exciting flight.");
            System.out.println(entry1);  // Show entry details after modifying an item

            // 7. Remove an item from the entry
            System.out.println("\nRemoving an item from the entry...");
            entry1.removeItem(0);
            System.out.println(entry1);  // Show entry details after removing an item

            // 8. View an item from the entry
            System.out.println("\nViewing an item from the entry...");
            entry1.viewItem(0);  // Should print the updated item

            // 9. View all items in the entry
            System.out.println("\nViewing all items in the entry...");
            entry1.view();  // Should print all the remaining items in the entry

            // 10. Try modifying or removing an item that doesn't exist
            System.out.println("\nTrying to remove an invalid item (out of bounds)...");
            try {
                entry1.removeItem(10);  // Should throw an exception because index is invalid
            } catch (InvalidInputException e) {
                System.out.println("Error: " + e.getMessage());
            }

            // 11. Try to set an invalid index in an entry
            System.out.println("\nTrying to set an invalid index...");
            try {
                entry1.setItem(-1, "Text: Invalid index test");  // Should throw an exception because the index is negative
            } catch (InvalidInputException e) {
                System.out.println("Error: " + e.getMessage());
            }

        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
