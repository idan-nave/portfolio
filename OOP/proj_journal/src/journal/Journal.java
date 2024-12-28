package journal;

import java.util.List;
import java.util.ArrayList;

public class Journal extends MetaHandler {

    // Journal fields
    protected User owner;
    private List<Entry> entries;

    // Constructor - a journal must be coupled with a user
    public Journal(String title, User owner) throws InvalidInputException {
        super(title, owner.getPath()); // Pass the parent path to the MetaHandler constructor

        // Input Validation
        InvalidInputException.validateString(title);
        InvalidInputException.validateUserExists(owner);

        this.entries = new ArrayList<>();
        // If subscribed, the user can create multiple entries, otherwise only
        // MAX_ENTRIES
        addEntry(new Entry("Default Entry", this));
    }

    // Getters
    protected User getOwner() {
        return this.owner;
    }

    public List<Entry> getEntries() {
        return entries;
    }

    public int getEntriesCount() {
        return entries.size();
    }

    // Journal Actuators

    protected void addEntry(Entry entry) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateExists(entry);
        InvalidInputException.validateSubscription(owner);

        entries.add(entry);
        entry.container = this;
    }

    protected void renameEntry(Entry entry, String newTitle) throws InvalidInputException {
        
        // Input Validation
        InvalidInputException.validateExists(entry);
        InvalidInputException.validateString(newTitle);

        // if found- will rename first occurance
        entry.rename(newTitle);
    }

    protected void removeEntry(Entry entry) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateExists(entry);

        // if found- will remove first occurance
        entries.remove(entry);
        entry.delete();
    }

    protected void viewEntry(Entry entry) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateExists(entry);

        System.out.println(entry.toString());
    }

    // Overriding the toString method to show useful user info
    @Override
    public String toString() {
        StringBuilder entryTitles = new StringBuilder();
        for (Entry entry : entries) {
            entryTitles.append(entry.getTitle()).append(" ");
        }
        

        // Get last changed time
        String lastChanged = getLastChanged().toString(); 
        // Get entry count
        int entryCount = getEntriesCount();
        
        return "Journal [uid=" + getUID() 
                + ", title=" + getTitle() 
                + ", lastChanged=" + lastChanged 
                + ", Has " + entryCount + " entries: " 
                + "[" + entryTitles + "]]";
    }
}