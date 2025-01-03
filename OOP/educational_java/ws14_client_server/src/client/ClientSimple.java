package src.client;

import java.io.*;
import java.net.*;

public class ClientSimple {

    // Define final constants for the server connection and HTTP request
    // For external server:
    // private static final String SERVER_HOST = "example.com"; // Server hostname (can be an IP address)
    // private static final int SERVER_PORT = 80; // Server port (HTTP port)
    // private static final String HOST_HEADER = "Host: example.com"; // HTTP Host header

    // For localhost server:
    private static final String SERVER_HOST = "localhost";       // "localhost" ; "example.com"; // Server hostname (can be an IP address)
    private static final int SERVER_PORT = 8080;                 //  8080 ; 80;                  // Server port (HTTP port)
    private static final String HOST_HEADER = "Host: localhost"; // "localhost" ; "example.com"; // HTTP Host header

    private static final String HTTP_REQUEST = "GET / HTTP/1.1"; // HTTP GET request line
    private static final String END_OF_REQUEST = "END_OF_REQUEST";
    private static final String END_OF_RESPONSE = "END_OF_RESPONSE";
    public static void main(String[] args) {
        try (Socket socket = new Socket(SERVER_HOST, SERVER_PORT);
             OutputStream output = socket.getOutputStream();
             PrintWriter writer = new PrintWriter(output, true);
             InputStream input = socket.getInputStream();
             BufferedReader reader = new BufferedReader(
                new InputStreamReader(input))) {

            // 1. Validate connection over Socket
            if (socket.isConnected()) {
                System.out.println("Socket connected successfully!");
            } else {
                System.out.println("Socket connection failed.");
            }
                
            // 2. Send an HTTP GET request to the server
            writer.println(HTTP_REQUEST);  // Sending the HTTP GET request
            writer.println(HOST_HEADER);  // Adding the Host header
            writer.println(END_OF_REQUEST); // indicate the end of the request

            // 3. Read the response from the server
            String responseLine;
            do {
                responseLine = reader.readLine();
                if (responseLine != null) {
                    System.out.println("Server Response: " + responseLine);  // Displaying the server's response
                }
            } while (responseLine != null && !responseLine.contains(END_OF_RESPONSE));

        } catch (IOException e) {
            System.err.println("Error while communicating with the server: " + e.getMessage());
        }
    }
}
