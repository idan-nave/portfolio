package journal;

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class ConsoleApp {
    
    private static Scanner scanner = new Scanner(System.in);
    
    private static List<User> users = new ArrayList<>();
    private static User currentUser;
    private static Journal currentJournal;
    private static Entry currentEntry;
    
    public static void main(String[] args) {
        while (true) {
            showMainMenu();
        }
    }
    
    private static void showMainMenu() {
        System.out.println("\n--- Main Menu ---");
        System.out.println("1. Manage Users");
        System.out.println("2. Exit");
        System.out.print("Choose an option: ");
        
        int choice = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        switch (choice) {
            case 1:
                showUserMenu();
                break;
            case 2:
                System.out.println("Exiting the application...");
                System.exit(0);
                break;
            default:
                System.out.println("Invalid option. Please try again.");
        }
    }
    
    private static void showUserMenu() {
        System.out.println("\n--- User Management ---");
        System.out.println("1. Create User");
        System.out.println("2. View Users");
        System.out.println("3. Back to Main Menu");
        System.out.print("Choose an option: ");
        
        int choice = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        switch (choice) {
            case 1:
                createUser();
                break;
            case 2:
                viewUsers();
                break;
            case 3:
                return;
            default:
                System.out.println("Invalid option. Please try again.");
        }
    }
    
    private static void createUser() {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        try {
            User user = new User(username);
            users.add(user);
            System.out.println("User created successfully!");
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    
    private static void viewUsers() {
        if (users.isEmpty()) {
            System.out.println("No users available.");
            return;
        }
        
        System.out.println("\n--- List of Users ---");
        for (int i = 0; i < users.size(); i++) {
            System.out.println((i + 1) + ". " + users.get(i).getUserName());
        }
        System.out.print("Choose a user to manage or 0 to go back: ");
        
        int choice = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        if (choice == 0) {
            return;
        } else if (choice > 0 && choice <= users.size()) {
            currentUser = users.get(choice - 1);
            showJournalMenu();
        } else {
            System.out.println("Invalid option. Please try again.");
        }
    }
    
    private static void showJournalMenu() {
        while (true) {
            System.out.println("\n--- Journal Management (User: " + currentUser.getUserName() + ") ---");
            System.out.println("1. Add Journal");
            System.out.println("2. View Journals");
            System.out.println("3. Subscribe User");
            System.out.println("4. Back to User Management");
            System.out.print("Choose an option: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline
            
            switch (choice) {
                case 1:
                    addJournal();
                    break;
                case 2:
                    viewJournals();
                    break;
                case 3:
                    subscribeUser();
                    break;
                case 4:
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }
    
    private static void addJournal() {
        System.out.print("Enter journal title: ");
        String title = scanner.nextLine();
        
        try {
            Journal journal = new Journal(title, currentUser);
            currentUser.addJournal(journal);
            System.out.println("Journal added successfully!");
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    
    private static void viewJournals() {
        if (currentUser.getJournals().isEmpty()) {
            System.out.println("No journals available.");
            return;
        }
        
        System.out.println("\n--- List of Journals ---");
        for (int i = 0; i < currentUser.getJournals().size(); i++) {
            System.out.println((i + 1) + ". " + currentUser.getJournals().get(i).getTitle());
        }
        System.out.print("Choose a journal to manage or 0 to go back: ");
        
        int choice = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        if (choice == 0) {
            return;
        } else if (choice > 0 && choice <= currentUser.getJournals().size()) {
            currentJournal = currentUser.getJournals().get(choice - 1);
            showEntryMenu();
        } else {
            System.out.println("Invalid option. Please try again.");
        }
    }
    
    private static void subscribeUser() {
        currentUser.subscribe();
        System.out.println("User subscribed successfully!");
    }
    
    private static void showEntryMenu() {
        while (true) {
            System.out.println("\n--- Entry Management (Journal: " + currentJournal.getTitle() + ") ---");
            System.out.println("1. Add Entry");
            System.out.println("2. View Entries");
            System.out.println("3. Back to Journal Management");
            System.out.print("Choose an option: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline
            
            switch (choice) {
                case 1:
                    addEntry();
                    break;
                case 2:
                    viewEntries();
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }
    
    private static void addEntry() {
        System.out.print("Enter entry title: ");
        String title = scanner.nextLine();
        
        try {
            Entry entry = new Entry(title, currentJournal);
            currentJournal.addEntry(entry);
            System.out.println("Entry added successfully!");
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    
    private static void viewEntries() {
        if (currentJournal.getEntries().isEmpty()) {
            System.out.println("No entries available.");
            return;
        }
        
        System.out.println("\n--- List of Entries ---");
        for (int i = 0; i < currentJournal.getEntries().size(); i++) {
            System.out.println((i + 1) + ". " + currentJournal.getEntries().get(i).getTitle());
        }
        System.out.print("Choose an entry to manage or 0 to go back: ");
        
        int choice = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        if (choice == 0) {
            return;
        } else if (choice > 0 && choice <= currentJournal.getEntries().size()) {
            currentEntry = currentJournal.getEntries().get(choice - 1);
            manageEntry();
        } else {
            System.out.println("Invalid option. Please try again.");
        }
    }
    
    private static void manageEntry() {
        while (true) {
            System.out.println("\n--- Entry Management (Entry: " + currentEntry.getTitle() + ") ---");
            System.out.println("1. Add Item");
            System.out.println("2. View Item");
            System.out.println("3. Remove Item");
            System.out.println("4. Back to Journal Management");
            System.out.print("Choose an option: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline
            
            switch (choice) {
                case 1:
                    addItemToEntry();
                    break;
                case 2:
                    viewItemInEntry();
                    break;
                case 3:
                    removeItemFromEntry();
                    break;
                case 4:
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }
    
    private static void addItemToEntry() {
        System.out.print("Enter item to add: ");
        String item = scanner.nextLine();
        
        try {
            currentEntry.addItem(item);
            System.out.println("Item added successfully!");
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    
    private static void viewItemInEntry() {
        System.out.print("Enter index of item to view: ");
        int index = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        try {
            currentEntry.viewItem(index);
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    
    private static void removeItemFromEntry() {
        System.out.print("Enter index of item to remove: ");
        int index = scanner.nextInt();
        scanner.nextLine();  // Consume newline
        
        try {
            currentEntry.removeItem(index);
            System.out.println("Item removed successfully!");
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
