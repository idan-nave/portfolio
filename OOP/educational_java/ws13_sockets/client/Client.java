// javac -d bin client/Client.java
// java -cp bin client.Client 

package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    private final static String ADDRESS = "127.0.0.1";
    private final static int PORT = 3001;
    private final static String PING = "PING";
    private final static String END_OF_RESPONSE = "END_OF_RESPONSE";
    
    private Socket socket = null;
    private PrintWriter writer = null;
    private BufferedReader reader = null;
    
    public static void main(String[] args) {
        Client client = new Client();
        client.start();
    }
    
    public void start() {
        try {
            socket = new Socket(ADDRESS, PORT);
            System.out.println("Connected to the server at " + ADDRESS + ":" + PORT);
            
            InputStream input = socket.getInputStream();
            OutputStream out = socket.getOutputStream();
            
            writer = new PrintWriter(out, true); // Auto-flush enabled
            reader = new BufferedReader(new InputStreamReader(input));
            
            System.out.println("Starting connection test...");
            testCon();
            handleMenu();
        } catch (IOException e) {
            System.err.println("Error connecting to the server: " + e.getMessage());
            e.printStackTrace();
        } finally {
            closeConnections();
        }
    }

    private void testCon() throws IOException {
        // Send PING to the server
        writer.println(PING);
        String response = reader.readLine();

        if ("PONG".equalsIgnoreCase(response)) {
            System.out.println("Connection test successful.");
        } else if (response != null) {
            System.out.println("Unexpected response from server: " + response);
        } else {
            System.out.println("No response from server.");
        }
    }
    
    private void handleMenu() {
        // Use try-with-resources to ensure Scanner is closed automatically
        try (Scanner scan = new Scanner(System.in)) {
            int answer;
            boolean running = true;

            while (running) {
                System.out.println("\nChoose what to do?\n"
                        + "\t1: Return the users\n"
                        + "\t2: Return the animals\n"
                        + "\t3: Add a user\n"
                        + "\t4: Add an animal\n"
                        + "\t0: Exit");
                System.out.print("Enter your choice: ");

                if (scan.hasNextInt()) {
                    answer = scan.nextInt();
                    scan.nextLine(); // Consume the newline character

                    switch (answer) {
                        case 1:
                            getUsers();
                            break;
                        case 2:
                            getAnimals();
                            break;
                        case 3:
                            addUser(scan);
                            break;
                        case 4:
                            addAnimal(scan);
                            break;
                        case 0:
                            System.out.println("Exiting the application. Goodbye!");
                            running = false;
                            break;
                        default:
                            System.out.println("Not an option! Please choose a valid number.");
                    }
                } else {
                    System.out.println("Invalid input! Please enter a number.");
                    scan.nextLine(); // Clear the invalid input
                }
            }
        } catch (IOException e) {
            System.err.println("Error during menu handling: " + e.getMessage());
        }
    }
    
    private void getUsers() throws IOException {
        // Send command to server
        writer.println("GET users");
        
        // Wait for server response until END_OF_RESPONSE
        System.out.println("Retrieving users...");
        String str;
        while ((str = reader.readLine()) != null) {
            if (str.equalsIgnoreCase(END_OF_RESPONSE)) {
                break;
            }
            System.out.println(str);
        }
    }
    
    private void getAnimals() throws IOException {
        // Send command to server
        writer.println("GET animals");
        
        // Wait for server response until END_OF_RESPONSE
        System.out.println("Retrieving animals...");
        String str;
        while ((str = reader.readLine()) != null) {
            if (str.equalsIgnoreCase(END_OF_RESPONSE)) {
                break;
            }
            System.out.println(str);
        }
    }
    
    private void addUser(Scanner scan) throws IOException {
        // Send command to server
        writer.println("POST user");
        
        // Read server's prompt for username
        String promptUsername = reader.readLine();
        if (promptUsername != null) {
        	if(promptUsername.equalsIgnoreCase("UNKNOWN_COMMAND")) {
        		System.out.println("Server respond: "+promptUsername);
        		handleMenu();	
        	}
            System.out.println(promptUsername);
        }
        
        // Get username from user
        String username = scan.nextLine();
        writer.println(username);
        
        // Read server's prompt for password
        String promptPassword = reader.readLine();
        if (promptPassword != null) {
            System.out.println(promptPassword);
        }
        
        // Get password from user
        String password = scan.nextLine();
        writer.println(password);
        
        // Wait for server response until END_OF_RESPONSE
        System.out.println("Adding user...");
        String str;
        while ((str = reader.readLine()) != null) {
            if (str.equalsIgnoreCase(END_OF_RESPONSE)) {
                break;
            }
            System.out.println(str);
        }
    }
    
    private void addAnimal(Scanner scan) throws IOException {
        // Send command to server
        writer.println("POST animal");
        
        // Read server's prompt for animal name
        String promptName = reader.readLine();
        if (promptName != null) {
        	if(promptName.equalsIgnoreCase("UNKNOWN_COMMAND")) {
        		System.out.println("Server respond: "+promptName);
        		handleMenu();
        	}
        	System.out.println(promptName);
        }
        
        // Get animal name from user
        String animalName = scan.nextLine();
        writer.println(animalName);
        
        // Read server's prompt for animal species
        String promptSpecies = reader.readLine();
        if (promptSpecies != null) {
            System.out.println(promptSpecies);
        }
        
        // Get animal species from user
        String species = scan.nextLine();
        writer.println(species);
        
        // Wait for server response until END_OF_RESPONSE
        System.out.println("Adding animal...");
        String str;
        while ((str = reader.readLine()) != null) {
            if (str.equalsIgnoreCase(END_OF_RESPONSE)) {
                break;
            }
            System.out.println(str);
        }
    }
    
    private void closeConnections() {
        try {
            if (writer != null) {
                writer.close();
            }
            if (reader != null) {
                reader.close();
            }
            if (socket != null && !socket.isClosed()) {
                socket.close();
                System.out.println("Disconnected from the server.");
            }
        } catch (IOException e) {
            System.err.println("Error closing connections: " + e.getMessage());
        }
    }
}
