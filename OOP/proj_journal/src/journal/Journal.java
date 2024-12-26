package journal;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Journal {

    private String uid; // Unique identifier for each journal
    private String journalTitle;
    private List<Entry> entries;

    public Journal(String journalTitle) throws InvalidInputException {
        InvalidInputException.checkName(journalTitle);
        this.journalTitle = journalTitle;
        this.uid = UUID.randomUUID().toString(); // Generate a unique uid for the company
        this.entries = new ArrayList<>();
    }
}
