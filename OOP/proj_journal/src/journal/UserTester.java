package journal;

public class UserTester {
    public static void main(String[] args) {
        try {
            // 1. Create a new User
            System.out.println("Creating a new user...");
            User user = new User("john_doe");

            // Display initial state of the user
            System.out.println(user); // Using toString() method to show user details

            // 2. Subscribe the user
            System.out.println("\nSubscribing the user...");
            user.subscribe();
            System.out.println(user); // Show user info after subscription

            // 3. Add a new journal
            System.out.println("\nAdding a new journal...");
            Journal journal1 = new Journal("My First Journal", user);
            user.addJournal(journal1);
            System.out.println(user); // Display user details after adding journal

            // 4. Add another journal (only allowed if subscribed)
            System.out.println("\nAdding another journal...");
            Journal journal2 = new Journal("My Second Journal", user);
            user.addJournal(journal2);
            System.out.println(user); // Display user details after adding second journal

            // 5. Rename a journal
            System.out.println("\nRenaming a journal...");
            user.renameJournal(journal1, "My Renamed Journal");
            System.out.println(user); // Display user details after renaming journal

            // 6. Remove a journal
            System.out.println("\nRemoving a journal...");
            user.removeJournal(journal2);
            System.out.println(user); // Display user details after removing journal

            // 7. Checking the total number of journals and entries
            System.out.println("\nTotal journals: " + user.getJournalsCount());
            System.out.println("Total entries: " + user.getTotalEntriesCount());

            // 8. Try adding a journal when not subscribed
            System.out.println("\nTrying to add a journal when unsubscribed...");
            User nonSubscribedUser = new User("non_subscribed_user");
            nonSubscribedUser.addJournal(new Journal("Non-subscribed Journal", nonSubscribedUser));
            System.out.println(nonSubscribedUser); // Display user info with journal

            // 9. View a journal
            System.out.println("\nViewing a journal...");
            user.viewJournal(journal1);

            // 10. Try to add a third journal when non-subscribed (should throw an
            // exception)
            System.out.println("\nTrying to add a third journal to a non-subscribed user...");
            try {
                nonSubscribedUser.addJournal(new Journal("Another Journal", nonSubscribedUser));
            } catch (InvalidInputException e) {
                System.out.println("Error: " + e.getMessage());
            }

        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
