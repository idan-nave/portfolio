package src.server;

import java.io.*;
import java.net.*;

public class ServerSingleThread {

    // Define final constants for server configuration and responses
    public static final int SERVER_PORT = 8080; // Server listening port
    public static final String HTTP_OK_RESPONSE = "HTTP/1.1 200 OK"; // HTTP status line
    public static final String CONTENT_TYPE = "Content-Type: text/plain"; // HTTP Content-Type header
    public static final String SERVER_MESSAGE = "Hello from the server!"; // Message sent to clients

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(SERVER_PORT)) {
            System.out.println("Server listening on port " + SERVER_PORT + "...");

            // 2. Loop to continuously accept client connections
            while (true) {
                // Accept the client connection
                try (Socket clientSocket = serverSocket.accept();) {

                    System.out.println("New client connected: " + clientSocket.getInetAddress());

                    // 3. Handle client in a new thread (to allow multiple clients)
                    new ClientHandler(clientSocket).start();
                } catch (IOException e) {
                    System.out.println("Error while accepting client connection: " + e.getMessage());
                    e.printStackTrace();
                }
            }

        } catch (IOException e) {
            System.out.println("Error setting up the server socket: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

// A separate thread to handle multi client connection
class ClientHandler extends Thread {

    private static final String CLIENT_MESSAGE_PREFIX = "Client: "; // Prefix for printing client messages
    private static final String EMPTY_LINE = ""; // Represents an empty line in HTTP requests
    public static final String END_OF_REQUEST = "END_OF_REQUEST";
    public static final String END_OF_RESPONSE = "END_OF_RESPONSE";

    private Socket clientSocket;

    public ClientHandler(Socket socket) {
        this.clientSocket = socket;
    }

    @Override
    public void run() {
        try (
                InputStream input = clientSocket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                OutputStream output = clientSocket.getOutputStream();
                PrintWriter writer = new PrintWriter(output, true)) {
            // 4. Read the client's request line by line (e.g., HTTP request)
            String requestLine;
            do {
                requestLine = reader.readLine();
                if (requestLine != null) {
                    System.out.println(CLIENT_MESSAGE_PREFIX + requestLine); // Displaying the Clients's request
                }
            } while (requestLine != null && !requestLine.contains(END_OF_REQUEST));

            // 5. Send an HTTP response to the client
            writer.println(ServerSingleThread.HTTP_OK_RESPONSE); // Send HTTP status from Server class
            writer.println(ServerSingleThread.CONTENT_TYPE); // Send content type header from Server class
            writer.println(EMPTY_LINE); // Blank line separating headers and body
            writer.println(ServerSingleThread.SERVER_MESSAGE); // Send the server message to the client
            writer.println(END_OF_RESPONSE); // indicate the end of the response

        } catch (IOException e) {
            System.err.println("Error handling client: " + e.getMessage());
        }
    }
}
