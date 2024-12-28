# Journal Project README

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Technologies Used](#technologies-used)
4. [Getting Started](#getting-started)
5. [Class Descriptions](#class-descriptions)
6. [Usage Instructions](#usage-instructions)
7. [File Operations](#file-operations)
8. [Error Handling](#error-handling)
9. [Future Enhancements](#future-enhancements)

---

## Project Overview

The Journal Project is a Java-based system that allows users to create and manage personal journals. The system includes the ability to:

- **Create Users**: Each user has a unique ID and can own multiple journals.
- **Create and Manage Journals**: Users can add, rename, or remove journals.
- **Create Entries within Journals**: Journals can contain multiple entries, and entries can have associated data items (e.g., text, photos).
- **Manage Entry Items**: Entries can contain items (like text) which users can add, update, or remove.
- **File Handling**: Data is stored in files, and users can read, write, replace, or delete data items in these files.

This system allows for hierarchical management where users own journals, and journals contain entries. Each entry can have multiple items that are stored and managed as text data.

---

## Features

- **User Management**: 
    - Users can be created with a unique username.
    - Users can subscribe for additional functionality.
    - Users can own multiple journals.

- **Journal Management**: 
    - Journals can be created and linked to a user.
    - Users can add, remove, and rename journals.

- **Entry Management**: 
    - Entries can be created within journals.
    - Entries can be renamed and removed.
    - Entries can hold multiple items (text, etc.), and these items can be added, updated, or removed.

- **File Operations**:
    - File-based persistence is used for storing journal entries and data items.
    - Basic file operations such as reading, writing, replacing, and deleting lines from files are implemented.

---

## Technologies Used

- **Java**: The project is built entirely in Java, utilizing standard Java libraries for file handling, exception handling, and string manipulation.
- **Java IO (File Handling)**: The project uses Java’s `java.nio.file` and `java.io` packages for reading and writing to files.
- **Java 8+**: Utilized for `LocalDateTime` handling and other Java 8 features.

---

## Getting Started

To run the Journal Project on your local machine, follow these steps:

1. **Clone the Repository**:
   - If you have Git installed, clone the repository using:
     ```
     git clone <repository-url>
     ```
   
2. **Setup Java Development Environment**:
   - Make sure you have Java 8 or higher installed on your system. You can check your Java version by running:
     ```
     java -version
     ```
   
3. **Compile and Run**:
   - Open a terminal/command prompt in the root folder of the project.
   - Compile the project using the following command:
     ```
     javac -d . *.java
     ```
   - Run the project with:
     ```
     java journal.Main
     ```

4. **Interacting with the Program**:
   - Once the program starts, you can test it by adding users, creating journals, adding entries, and manipulating the data within the journals.

---

## Class Descriptions

### `MetaHandler`

- **Purpose**: This is the base class for all entities (User, Journal, Entry). It holds common properties like `title`, `path`, and `lastChanged`. It also provides methods to update and retrieve these values.

### `StreamHandler`

- **Purpose**: Handles all file operations such as writing data to files, reading data, and manipulating lines within files (adding, replacing, or deleting).
- **Main Methods**:
    - `writeToFile`: Writes data to a file.
    - `readFromFile`: Reads and prints the contents of a file.
    - `replaceLineInFile`: Replaces a specific line in a file.
    - `deleteLineInFile`: Deletes a specific line in a file.
    - `countFilesInDirectory`: Counts the number of files in a directory.

### `InvalidInputException`

- **Purpose**: Custom exception for handling invalid inputs, such as empty strings or invalid actions (e.g., trying to add a journal to a user who is not subscribed).
- **Key Validation Methods**:
    - `validateString`: Validates non-empty strings.
    - `validateExists`: Checks if an entity (user, journal, entry) exists.
    - `validateSubscription`: Validates if the user is subscribed.
    - `validatePositiveIndex`: Ensures that indices used in lists are positive.

### `User`

- **Purpose**: Represents a user in the system. A user can own multiple journals and has a subscription status that affects their permissions.
- **Key Methods**:
    - `addJournal`: Adds a journal to the user.
    - `removeJournal`: Removes a journal from the user.
    - `subscribe`: Marks the user as subscribed.
    - `viewJournal`: Views the details of a journal.

### `Journal`

- **Purpose**: Represents a journal owned by a user. A journal can contain multiple entries.
- **Key Methods**:
    - `addEntry`: Adds a new entry to the journal.
    - `removeEntry`: Removes an entry from the journal.
    - `renameEntry`: Renames an existing entry.
    - `viewEntry`: Views the details of an entry.

### `Entry`

- **Purpose**: Represents an individual entry within a journal. Entries can contain multiple data items (e.g., text or photos).
- **Key Methods**:
    - `addItem`: Adds an item (text) to the entry.
    - `setItem`: Replaces an item in the entry.
    - `removeItem`: Removes an item from the entry.
    - `viewItem`: Views the contents of an item in the entry.

---

## Usage Instructions

### 1. Create a User
```java
User user1 = new User("john_doe");
```

### 2. Create a Journal
```java
Journal journal1 = new Journal("Tech Journal", user1);
```

### 3. Add an Entry to a Journal
```java
Entry entry1 = new Entry("Tech Trends 2024", journal1);
journal1.addEntry(entry1);
```

### 4. Add Items to an Entry
```java
entry1.addItem("Cloud Computing");
entry1.addItem("AI Developments");
```

### 5. View All Data
```java
StreamHandler.readFromFile(entry1.getPath());
```

### 6. Update an Item in an Entry
```java
StreamHandler.replaceLineInFile(entry1.getPath(), 0, "Updated Content for Cloud Computing");
```

### 7. Delete an Item from an Entry
```java
StreamHandler.deleteLineInFile(entry1.getPath(), 1);
```

---

## File Operations

### `writeToFile`
Writes data to a specified file. Each line in the data array is written to a new line in the file.

### `readFromFile`
Reads the entire content of the file and prints it to the console.

### `replaceLineInFile`
Replaces a specific line in the file with new content. The line number is specified by its index.

### `deleteLineInFile`
Deletes a specific line from the file based on its index.

### `countFilesInDirectory`
Counts the number of files in a directory and returns the count.

---

## Error Handling

The project uses custom exceptions (`InvalidInputException`) to handle errors related to invalid inputs. Common error scenarios include:

- Trying to create a journal or entry with an invalid title.
- Adding a journal or entry to a user who has not subscribed (if applicable).
- Accessing a non-existent file or data.

All these errors are handled gracefully, and appropriate messages are displayed to the user.

---

## Future Enhancements

1. **Database Support**: Replace file storage with a more robust database (e.g., SQLite, MySQL) to handle large amounts of data.
2. **User Interface**: Develop a graphical user interface (GUI) using JavaFX or Swing.
3. **Search Functionality**: Add the ability to search for journals, entries, or items by keywords.
4. **Password Protection**: Add user authentication with password protection to enhance security.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
