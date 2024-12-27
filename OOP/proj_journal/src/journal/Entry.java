package journal;

import java.sql.Date;
import java.util.UUID;

public class Entry extends Journal{

    private static final int MAX_CONTENT_CHARS = 8000;

    private String uid; // Unique identifier for each journal
    private Date lastUpdate;
    private String entryTitle;
    private StringBuffer content;

    public Entry(String entryTitle) throws InvalidInputException {
        InvalidInputException.checkName(entryTitle);
        this.entryTitle = entryTitle;
        this.content = new StringBuffer();;
        this.uid = UUID.randomUUID().toString(); // Generate a unique uid for the company
    }
}
