package journal;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class User {

    // Non-Premium restrictions
    public static final int MAX_JOURNALS = 1;
    public static final int MAX_ENTRIES = 3;

    private static long idCounter = 100000000; // Auto-incremented ID starting at 100000000
    private long id;
    protected boolean isPremium;
    private String userName;
    protected String basePath; // path for user files
    protected List<Journal> journals;

    public User()
    {
        //void consructor for enabling inheritance
    }

    // Constructor to set specific fields (if needed)
    public User(String userName) throws InvalidActionException, InvalidInputException {
        // Validate user details
        InvalidInputException.checkName(userName);
        this.id = idCounter++; // Auto-increment ID
        this.isPremium = false;
        this.userName = userName;
        this.basePath = "./journals/" + userName + "/";
        FilesDirsManager.createDirectory(basePath); // adds a user folder
        createJournal("Default Journal"); // adds a single default journal
    }

    // Getter and Setter methods
    public long getId() {
        return id;
    }

    public String getUserName() {
        return userName;
    }

    public int getJournalCount() {
        return this.journals.size();
    }

    public void setUserName(String userName) throws InvalidInputException {
        InvalidInputException.checkName(userName);
        this.userName = userName;
    }

    public void payPremium() {
        this.isPremium = true;
    }

    // Method to create a new journal - take premium status into account
    protected void createJournal(String title) throws InvalidActionException, InvalidInputException {
        InvalidInputException.checkName(title);
        InvalidActionException.validateJournalCreationApproval(this);
        this.journals = new ArrayList<Journal>(); //adds journal to user list
        this.journals.add(new Journal(title)); //construct journal type
        FilesDirsManager.createDirectory(basePath + title); // if not exists already
    }

    // Method to delete a journal (including all contents)
    protected void deleteJournal(String title) throws InvalidInputException {
        InvalidInputException.checkName(title);
        Iterator<Journal> found = findJournalByTitle(title);
        if (found == null)
            return;
        found.remove();
        FilesDirsManager.deleteDirectoryRecursively(basePath + title);
    }

    // Method to rename a journal (if not existing already)
    protected void renameJournal(String title, String newTitle) throws InvalidInputException {
        InvalidInputException.checkName(title);
        InvalidInputException.checkName(newTitle);
        Iterator<Journal> found = findJournalByTitle(title);
        if (found == null)
            return;
        Journal journal = found.next();
        journal.setTitle(newTitle);
        FilesDirsManager.renameDirectory(basePath + title, basePath + newTitle);
    }

    // toString method to return a string representation of the user
    @Override
    public String toString() {
        String isPremium = (this.isPremium) ? "Premium" : "Regular";
        return "ID: " + id + ", Name: " + userName + ", Status: " + isPremium + ", has" + getJournalCount() + " journals";
    }

    // Method to find a journal by title and return an Iterator
    protected Iterator<Journal> findJournalByTitle(String title) throws InvalidInputException {
        InvalidInputException.checkName(title);

        // Iterate over journals list and find the one with the matching title
        Iterator<Journal> iterator = journals.iterator();
        while (iterator.hasNext()) {
            Journal journal = iterator.next();
            if (journal.getTitle().equals(title)) {
                return iterator; // Return the iterator pointing to the matching journal
            }
        }
        System.out.println("no results for findJournalByTitle(" + title + ")");
        return null; // Return null if no journal with the title is found
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

        } catch (InvalidInputException | InvalidActionException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
