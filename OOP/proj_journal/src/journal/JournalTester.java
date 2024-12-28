package journal;

public class JournalTester {
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
            Journal journal1 = new Journal("Travel Journal", user);
            System.out.println(journal1);  // Show journal details after creation

            // 4. Add entries to the journal
            System.out.println("\nAdding entries to the journal...");
            Entry entry1 = new Entry("Day 1: Arrival", journal1);
            Entry entry2 = new Entry("Day 2: Exploring", journal1);
            journal1.addEntry(entry1);
            journal1.addEntry(entry2);
            System.out.println(journal1);  // Show journal details after adding entries

            // 5. Rename an entry
            System.out.println("\nRenaming an entry...");
            journal1.renameEntry(entry1, "Day 1: Arrival in Paris");
            System.out.println(journal1);  // Show journal details after renaming entry

            // 6. Remove an entry
            System.out.println("\nRemoving an entry...");
            journal1.removeEntry(entry2);
            System.out.println(journal1);  // Show journal details after removing entry

            // 7. View an entry
            System.out.println("\nViewing an entry...");
            journal1.viewEntry(entry1);  // Should print the details of "Day 1: Arrival in Paris"

            // 8. Check the total number of entries in the journal
            System.out.println("\nTotal entries in the journal: " + journal1.getEntriesCount());

            // 9. Try to add more entries when the user is not subscribed (if the subscription logic is enforced)
            System.out.println("\nCreating another user who is not subscribed...");
            User nonSubscribedUser = new User("bob_jones");
            System.out.println(nonSubscribedUser);  // Show user details
            Journal journal2 = new Journal("Work Journal", nonSubscribedUser);  // Should succeed
            System.out.println(journal2);  // Show journal details for non-subscribed user

            // 10. Add an entry for non-subscribed user (test subscription limits if any)
            Entry entry3 = new Entry("First Work Entry", journal2);
            journal2.addEntry(entry3);  // This should work
            System.out.println(journal2);  // Show journal details for non-subscribed user

            // 11. Try adding a second entry (if limited by subscription)
            System.out.println("\nTrying to add a second entry to the non-subscribed user's journal...");
            try {
                Entry entry4 = new Entry("Second Work Entry", journal2);
                journal2.addEntry(entry4);  // Should fail if subscription limit is enforced
            } catch (InvalidInputException e) {
                System.out.println("Error: " + e.getMessage());
            }

        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
