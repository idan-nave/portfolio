package src.server;

import java.io.*;
import java.net.*;

public class ServerSimple {

    // Define final constants for the server configuration and response
    private static final int SERVER_PORT = 8080;  // Port number the server listens on
    
    private static final String HTTP_OK_RESPONSE = "HTTP/1.1 200 OK";  // HTTP response status
    private static final String END_OF_REQUEST = "END_OF_REQUEST";
    private static final String END_OF_RESPONSE = "END_OF_RESPONSE";

    public static void main(String[] args) {
        try (
            // 1. Create a ServerSocket to listen on port SERVER_PORT
            ServerSocket serverSocket = new ServerSocket(SERVER_PORT)
        ) {
            System.out.println("Server listening on port " + SERVER_PORT + "...");

            // 2. Loop to continuously accept client connections
            while (true) {
                // 3. Accept client connections and handle them in a new method
                try (
                    // Accept client connection
                    Socket clientSocket = serverSocket.accept();
                    // Set up input and output streams to communicate with the client
                    InputStream input = clientSocket.getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                    OutputStream output = clientSocket.getOutputStream();
                    PrintWriter writer = new PrintWriter(output, true)
                ) {
                    //  serverSocket.accept() was done, so connection established:
                    System.out.println("New client connected: " + clientSocket.getInetAddress());

                    // Read client messages (in a simple way, just echo back the data)
                    String requestLine;
                    do {
                        requestLine = reader.readLine();
                        if (requestLine != null) {
                            System.out.println("Clients Request: " + requestLine);  // Displaying the Clients's request
                        }
                    } while (requestLine != null && !requestLine.contains(END_OF_REQUEST));

                    // Send HTTP response to the client
                    writer.println(HTTP_OK_RESPONSE); // Send HTTP status to the client
                    writer.println("Content-Type: text/plain"); // Send content-type header
                    writer.println(); // Blank line separating headers and body
                    writer.println("Hello from the server!"); // Body content
                    writer.println(END_OF_RESPONSE); // indicate the end of the response

                } catch (IOException e) {
                    System.err.println("Error handling client: " + e.getMessage());
                }
            }

        } catch (IOException e) {
            System.err.println("Server error: " + e.getMessage());
        }
    }
}
