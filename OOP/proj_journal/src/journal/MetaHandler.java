package journal;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.util.UUID;

// Classs that holds common meta attributes shared by all objects
// of the Journal's pproject - user, journal, entry.
// also handles the file representation of these objects by
// using the FileHandler class.

public abstract class MetaHandler {

    // static initialization block
    {
        Path path = Paths.get(User.USERS_PATH);
        try {
            // If the directory does not exist, create it
            if (Files.notExists(path)) {
                Files.createDirectory(path);
                System.out.println("Directory created: " + User.USERS_PATH);
            }
        } catch (IOException e) {
            System.out.println("Error creating directory: " + e.getMessage());
        }
    }

    // MetaHandler fields
    private String uid;
    private String title;
    private String path;
    private LocalDateTime lastChanged;

    // Constructor
    public MetaHandler(String title, String parentPath) throws InvalidInputException {

        // Validate inputs
        InvalidInputException.validateString(title);
        InvalidInputException.validateString(parentPath);

        this.uid = UUID.randomUUID().toString();
        this.title = title;
        this.path = parentPath + "/" + title;

        // create file/dir
        if (this instanceof Entry)
            FileHandler.createFile(path);
        else
            FileHandler.createDirectory(path);
        setLastChanged();
    }

    // Getter and Setters
    protected String getUID() {
        return uid;
    }

    protected String getTitle() {
        return title;
    }

    protected void setTitle(String title) throws InvalidInputException {

        // Validate inputs
        InvalidInputException.validateString(title);

        this.title = title;
        this.path = FileHandler.getParentPath(this.getPath()) + "/" + title;
        setLastChanged(); // Update lastChanged on title change
    }

    protected String getPath() {
        return path;
    }

    protected LocalDateTime getLastChanged() {
        return lastChanged;
    }

    // Set the last modified date from the file's metadata
    private void setLastChanged() throws InvalidInputException {
        // Validate inputs
        InvalidInputException.validatePath(this.path);

        lastChanged = LocalDateTime.now();
    }

    // CRUD methods for the journal files
    protected void delete() throws InvalidInputException {
        // Validate inputs
        InvalidInputException.validatePath(this.path);

        if (this instanceof Entry)
            FileHandler.deleteFile(path);
        else
            FileHandler.deleteDirectoryRecursively(path);
    }

    protected void rename(String newTitle) throws InvalidInputException {
        // Validate inputs
        InvalidInputException.validatePath(this.path);
        InvalidInputException.validateString(newTitle);

        if (this instanceof Entry) //
            FileHandler.renameFile(this.path, newTitle);
        else
            FileHandler.renameDirectory(this.path, newTitle);

        this.setTitle(newTitle);
    }

}
