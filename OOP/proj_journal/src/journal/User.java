package journal;

import java.util.List;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class User extends MetaHandler {

    public static final String USERS_PATH = "users/";

    // Non-subscribed user restrictions
    public static final int MAX_JOURNALS = 1;
    public static final int MAX_ENTRIES = 3;

    // User fields
    private static int idCounter = 1; // Auto-incremented ID for users
    private int id;
    private boolean isSubscribed;
    private List<Journal> journals; // list of journals owned by user

    // Constructor
    public User(String username) throws InvalidInputException {
        super(username, "./users"); // Pass the parent path to the MetaHandler constructor

        // Input Validation
        InvalidInputException.validateString(username);
        InvalidInputException.validateUsernameExists(username);

        this.id = idCounter++;
        this.isSubscribed = false;
        this.journals = new ArrayList<>();
        // If subscribed, the user can create multiple journals, otherwise only
        // MAX_JOURNALS
        addJournal(new Journal("Default Journal", this));
    }

    // Getters
    protected int getId() {
        return id;
    }

    protected String getUserName() {
        return super.getTitle();
    }

    protected boolean isSubscribed() {
        return isSubscribed;
    }

    protected List<Journal> getJournals() {
        return journals;
    }

    protected int getJournalsCount() {
        return journals.size();
    }

    protected int getTotalEntriesCount() {
        int entriesCount = 0;
        for (Journal journal : journals) {
            entriesCount += journal.getEntriesCount();
        }
        return entriesCount;
    }

    // Setters
    protected void setSubscribed(boolean isSubscribed) {
        this.isSubscribed = isSubscribed;
    }

    // User Actuators
    public void subscribe() {
        this.isSubscribed = true;
    }

    protected void addJournal(Journal journal) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateExists(journal);
        InvalidInputException.validateSubscription(this);

        journals.add(journal);
        journal.owner = this;
    }

    protected void renameJournal(Journal journal, String newTitle) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateExists(journal);
        InvalidInputException.validateString(newTitle);

        // if found- will rename first occurance
        journal.rename(newTitle);
    }

    protected void removeJournal(Journal journal) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateExists(journal);

        // if found- will remove first occurance
        journals.remove(journal);
        journal.delete();
    }

    protected void viewJournal(Journal journal) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateExists(journal);

        System.out.println(journal.toString());
    }

    // Overriding the toString method to show useful user info
    @Override
    public String toString() {
        StringBuilder journalTitles = new StringBuilder();
        for (Journal journal : journals) {
            journalTitles.append(journal.getTitle()).append("; ");
        }

        // Get subscription status
        String subscriptionStatus = isSubscribed ? "subscribed" : "unsubscribed";

        // Get last changed time
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String lastChanged = getLastChanged().format(formatter);
        // Get journal count
        int journalCount = getJournalsCount();

        return "User [id=" + id
                + ", username=" + getTitle()
                + ", subscription=" + subscriptionStatus
                + ", lastChanged=" + lastChanged
                + ", Has " + journalCount + " journals: "
                + "[" + journalTitles + "]]";
    }
}
