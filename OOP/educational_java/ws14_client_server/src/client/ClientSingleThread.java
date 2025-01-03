package src.client;

import java.io.*;
import java.net.*;

public class ClientSingleThread {
    
    // Define final constants for the server connection
    private static final String SERVER_HOST = "localhost";  // Server hostname (could be an IP address)
    private static final int SERVER_PORT = 8080;  // Server port
    private static final String HTTP_REQUEST = "GET / HTTP/1.1";  // HTTP request line
    private static final String HOST_HEADER = "Host: localhost";  // HTTP Host header

    public static final String END_OF_REQUEST = "END_OF_REQUEST";
    public static final String END_OF_RESPONSE = "END_OF_RESPONSE";
    public static void main(String[] args) {
        // Test the connection before proceeding with communication
        if (testConnection()) {
            System.out.println("Connection successful! Proceeding with communication...");

            // Proceed with sending the request and reading the response
            try (
                // 1. Create a socket and connect to the server at the given IP address and port
                Socket socket = new Socket(SERVER_HOST, SERVER_PORT); // Using constants for connection details
                OutputStream output = socket.getOutputStream();
                PrintWriter writer = new PrintWriter(output, true);
                InputStream input = socket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input))
            ) {
                System.out.println("Connected to the server!");

                // 2. Send an HTTP GET request to the server
                writer.println(HTTP_REQUEST);  // Sending the HTTP GET request
                writer.println(HOST_HEADER);  // Adding the Host header
                writer.println(); // Blank line to indicate the end of the request headers

                // 3. Read the server's response
                String responseLine;
                do {
                    responseLine = reader.readLine();
                    if (responseLine != null) {
                        System.out.println("Server Response: " + responseLine);  // Displaying the server's response
                    }
                } while (responseLine != null && !responseLine.contains(END_OF_RESPONSE));
                } catch (IOException e) {
                e.printStackTrace();  // Handling any IOExceptions
            }
        } else {
            System.out.println("Failed to connect to the server. Please check the server status and try again.");
        }
    }

    /**
     * This method tests the connection to the server by attempting to open a socket connection.
     * @return true if the connection is successful, false otherwise.
     */
    private static boolean testConnection() {
        try (
            // Try connecting to the server using the specified host and port
            Socket socket = new Socket(SERVER_HOST, SERVER_PORT)
        ) {
            // If the connection is successful, the socket will be automatically closed
            return true;  // Connection is successful
        } catch (IOException e) {
            // If an exception occurs, the connection failed
            System.out.println("Connection failed: " + e.getMessage());
            return false;  // Connection failed
        }
    }
}
