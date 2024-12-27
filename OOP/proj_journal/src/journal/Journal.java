package journal;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.UUID;

public class Journal extends User {
    public static final String ENTRY_FILE_EXT = ".txt";

    private String uid; // Unique identifier for each journal
    private String title;
    private String path; // path for journal entry files
    private List<Entry> entries;

    public Journal(String title) throws InvalidInputException, InvalidActionException {
        super();
        InvalidInputException.checkName(title);
        this.uid = UUID.randomUUID().toString(); // Generate a unique uid for the company
        this.title = title;
        this.path = super.basePath + title + "/";
        FilesDirsManager.createDirectory(path); // adds a journal folder
        createEntry("Default Entry"); // adds a single default entry
    }

    // Getter and Setter methods
    public String getUID() {
        return uid;
    }

    public String getTitle() {
        return title;
    }

    public int getEntryCount() {
        return this.entries.size();
    }

    protected void setTitle(String title) throws InvalidInputException {
        InvalidInputException.checkName(title);
        this.title = title;
    }

    // Method to create a new entry - take premium status into account
    protected void createEntry(String title) throws InvalidActionException, InvalidInputException {
        InvalidInputException.checkName(title);
        InvalidActionException.validateEntryCreationApproval(this);
        this.entries = new ArrayList<Entry>(); // adds entry to user list
        this.entries.add(new Entry(title)); // construct entry type
        FilesDirsManager.createFile(path + title + ENTRY_FILE_EXT); // if not exists already
    }

    // Method to delete an entry
    protected void deleteEntry(String title) throws InvalidInputException {
        InvalidInputException.checkName(title);
        Iterator<Entry> found = findEntryByTitle(title);
        if (found == null)
            return;
        found.remove();
        FilesDirsManager.deleteFile(path + title + ENTRY_FILE_EXT);
    }

    // Method to rename an entry (if not existing already)
    protected void renameEntry(String title, String newTitle) throws InvalidInputException {
        InvalidInputException.checkName(title);
        InvalidInputException.checkName(newTitle);
        Iterator<Entry> found = findEntryByTitle(title);
        if (found == null)
            return;
        Entry entry = found.next();
        entry.setTitle(newTitle);
        FilesDirsManager.renameFile(path + title + ENTRY_FILE_EXT, path + newTitle + ENTRY_FILE_EXT);
    }

    // toString method to return a string representation of the journal
    @Override
    public String toString() {
        return "UUID: " + uid + ", Journal: " + title + ", has" + getEntryCount() + " entries";
    }

    // Method to find a entry by title and return an Iterator
    protected Iterator<Entry> findEntryByTitle(String entryTitle) throws InvalidInputException {
        InvalidInputException.checkName(entryTitle);

        // Iterate over entry list and find the one with the matching title
        Iterator<Entry> iterator = entries.iterator();
        while (iterator.hasNext()) {
            Entry entry = iterator.next();
            if (entry.getTitle().equals(entryTitle)) {
                return iterator; // Return the iterator pointing to the matching journal
            }
        }
        System.out.println("no results for findEntryByTitle(" + entryTitle + ")");
        return null; // Return null if no journal with the title is found
    }
    
    // //Method to serialize & export a journal
    // public void export(String title) throws InvalidActionException,
    // InvalidInputException {
    // InvalidActionException.validateJournalCreation(this);
    // this.journals.add(new Journal(title));
    // }

}
