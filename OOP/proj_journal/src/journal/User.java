package journal;

import java.util.ArrayList;
import java.util.List;

public class User {

    // Non-Premium restrictions
    private static final int MAX_JOURNALS = 1;
    private static final int MAX_ENTRIES = 3;

    private static long idCounter = 100000000; // Auto-incremented ID starting at 100000000
    private long id;
    protected boolean isPremium;
    private String userName;
    private List<Journal> journals;

    // Constructor to set specific fields (if needed)
    public User(String userName) throws InvalidInputException {
        // Validate user details
        InvalidInputException.checkName(userName);
        this.id = idCounter++; // Auto-increment ID
        this.isPremium = false;
        this.userName = userName;

        //adds a single default journal
        this.journals = new ArrayList<>(MAX_JOURNALS);
        this.journals.add(new Journal("Default Journal"));
    }

    // Getter and Setter methods
    public long getId() {
        return id;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) throws InvalidInputException {
        InvalidInputException.checkName(userName);
        this.userName = userName;
    }

    public void payPremium() {
        this.isPremium = true;
    }

    public void createNewJournal(String journalTitle) throws InvalidActionException, InvalidInputException {
        InvalidActionException.validateJournalCreation(this);
        this.journals.add(new Journal(journalTitle));
    }

    // toString method to return a string representation of the user
    @Override
    public String toString() {
        String isPremium = (this.isPremium) ? "Premium" : "Regular";
        return "ID: " + id + ", Name: " + userName + ", Status: " + isPremium;
    }

    // Main method to test the User class
    public static void main(String[] args) {
        try {

            // Create User objects with and without a company
            User notPremiumUser = new User("Alice");
            User premiumUser = new User("Guy");
            premiumUser.payPremium();

            // Print the details of each user
            System.out.println(notPremiumUser);
            System.out.println(premiumUser);

        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
