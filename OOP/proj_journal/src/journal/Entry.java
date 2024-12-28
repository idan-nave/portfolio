package journal;

import java.util.List;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class Entry extends MetaHandler {

    // Entry fields
    protected Journal container;
    private List<Object> items; // List to hold various data types (text, photo, checkbox...)

    // Constructor - a journal must be coupled with a journal
    public Entry(String title, Journal container) throws InvalidInputException {
        super(title, container.getPath()); // Pass the parent path to the MetaHandler constructor

        // Input Validation
        InvalidInputException.validateString(title);
        // InvalidInputException.validateJournalExists(container);

        this.container = container;
        this.items = new ArrayList<>();
        // entry remains empty
    }

    // Getters
    protected Journal getContainer() {
        return this.container;
    }

    public List<Object> getItems() {
        return items;
    }

    public int getItemsCount() {
        return items.size();
    }

    // Entry Actuators

    protected void addItem(String item) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validateString(item);

        items.add(item);
        StreamHandler.writeToFile(getPath(), new String[] { item });
    }

    protected void setItem(int index, String alter) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validatePositiveIndex(index);
        InvalidInputException.validateItemIndexExist(items, index);
        InvalidInputException.validateString(alter);

        items.set(index, alter);
        StreamHandler.replaceLineInFile(getPath(), index, alter);
    }

    protected void removeItem(int index) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validatePositiveIndex(index);
        InvalidInputException.validateItemIndexExist(items, index);

        items.remove(index);
        StreamHandler.deleteLineInFile(getPath(), index);
    }

    protected void viewItem(int index) throws InvalidInputException {

        // Input Validation
        InvalidInputException.validatePositiveIndex(index);
        InvalidInputException.validateItemIndexExist(items, index);

        System.out.println(StreamHandler.readLineInFile(getPath(), index));
    }

    protected void view() {
        StreamHandler.readFromFile(getPath());
    }

    // Overriding the toString method to show useful user info
    @Override
    public String toString() {

        // Get last changed time
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String lastChanged = getLastChanged().format(formatter);
        // Get entry count
        int itemsCount = getItemsCount();

        return "Entry [uid=" + getUID()
                + ", title=" + getTitle()
                + ", lastChanged=" + lastChanged
                + "], Has " + itemsCount + " items";
    }
}