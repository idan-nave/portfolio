package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketException;

public class Handler implements Runnable {
    private final static String END_OF_RESPONSE = "END_OF_RESPONSE";
	private final static String PONG = "PONG";


    private Socket socket = null;
    private PrintWriter writer = null;
    private BufferedReader reader = null;

    public Handler(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            System.out.println("Starting conversation with client on port " + socket.getPort());
            InputStream input = socket.getInputStream();
            OutputStream out = socket.getOutputStream();

            writer = new PrintWriter(out, true);
            reader = new BufferedReader(new InputStreamReader(input));

            String request;

            while ((request = reader.readLine()) != null) {
                switch (request) {
                    case "GET animals":
                        System.out.println("GET animals");
                        readAnimals();
                        break;
                    case "GET users":
                        System.out.println("GET users");
                        readUsers();
                        break;
                    case "POST user":
                        System.out.println("POST user");
                        addUser();
                        break;
                    case "PING":
                        System.out.println(PONG);
                        writer.println(PONG);
                        break;
                    default:
                        System.out.println("Received unknown command: " + request);
                        writer.println("UNKNOWN_COMMAND");
                        break;
                }
            }
        } catch (SocketException e) {
            System.err.println("Client on port " + socket.getPort() + " has disconnected.");
        } catch (IOException e) {
            System.err.println("Error in Handler: " + e.getMessage());
        } finally {
            closeConnections();
        }
    }

    private void addUser() throws IOException {
        writer.println("Enter new username:");
        String username = reader.readLine();
        writer.println("Enter new password:");
        String password = reader.readLine();

        if (username == null || password == null || username.isEmpty() || password.isEmpty()) {
            writer.println("400 Bad Request: Username and password cannot be empty.");
            writer.println(END_OF_RESPONSE);
            return;
        }

        // Acknowledge the addition of the user
        writer.println("User " + username + " added successfully.");
        writer.println(END_OF_RESPONSE);
        System.out.println("Added user: " + username);
    }

    private void readAnimals() {
        writer.println("List of Animals:");
        writer.println("Dog");
        writer.println("Cat");
        writer.println("Elephant");
        writer.println(END_OF_RESPONSE);
    }

    private void readUsers() {
        writer.println("List of Users:");
        writer.println("Alice");
        writer.println("Bob");
        writer.println("Charlie");
        writer.println(END_OF_RESPONSE);
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
