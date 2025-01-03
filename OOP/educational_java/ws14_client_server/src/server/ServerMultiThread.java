package src.server;

import java.io.*;
import java.net.*;
import java.util.concurrent.*;

public class ServerMultiThread {

    // Define final constants for server configuration and responses
    public static final int SERVER_PORT = 8080; // Server listening port
    public static final String HTTP_OK_RESPONSE = "HTTP/1.1 200 OK"; // HTTP status line
    public static final String CONTENT_TYPE = "Content-Type: text/plain"; // HTTP Content-Type header
    public static final String SERVER_MESSAGE = "Hello from the server!"; // Message sent to clients
    private static final int CLIENT_TIMEOUT = 5000; // Timeout in milliseconds for client connections
    private static final int THREADS_COUNT = 10;

    public static void main(String[] args) {
        // Using a thread pool to manage client connections more efficiently
        ExecutorService clientThreadPool = Executors.newFixedThreadPool(THREADS_COUNT);

        try (ServerSocket serverSocket = new ServerSocket(SERVER_PORT)) {
            System.out.println("Server listening on port " + SERVER_PORT + "...");

            // 2. Loop to continuously accept client connections
            while (true) {
                try {
                    // Accept the client connection with a timeout
                    Socket clientSocket = serverSocket.accept();
                    clientSocket.setSoTimeout(CLIENT_TIMEOUT); // Set a timeout for client connection

                    System.out.println("New client connected: " + clientSocket.getInetAddress());

                    // 3. Handle client in a new thread (to allow multiple clients)
                    clientThreadPool.submit(new ClientHandler(clientSocket));

                } catch (IOException e) {
                    System.out.println("Error while accepting client connection: " + e.getMessage());
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            System.out.println("Error setting up the server socket: " + e.getMessage());
            e.printStackTrace();
        } finally {
            clientThreadPool.shutdown(); // Ensure thread pool is shut down gracefully
        }
    }
}

// A separate thread to handle multi-client connection
class ClientHandler implements Runnable {

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
            writer.println(ServerMultiThread.HTTP_OK_RESPONSE); // Send HTTP status from Server class
            writer.println(ServerMultiThread.CONTENT_TYPE); // Send content type header from Server class
            writer.println(EMPTY_LINE); // Blank line separating headers and body
            writer.println(ServerMultiThread.SERVER_MESSAGE); // Send the server message to the client
            writer.println(END_OF_RESPONSE); // Indicate the end of the response

        } catch (IOException e) {
            System.err.println("Error handling client: " + e.getMessage());
        } finally {
            try {
                clientSocket.close(); // Ensure the client socket is closed
            } catch (IOException e) {
                System.err.println("Error closing client socket: " + e.getMessage());
            }
        }
    }
}
