// Splitting Handlers into Different Classes

// Pros:

//     Separation of Concerns: Each class has a single responsibility (i.e., connection handling, fetching requests, transmiting, and terminating), which adheres to the Single Responsibility Principle (SRP). This improves maintainability and makes the code easier to modify in the future.
//     Modularity: You can modify or extend each handler independently. For example, you could easily change the way requests are processed without affecting the response or connection handling logic.
//     Testability: Testing individual components becomes easier because each handler is isolated and does one thing. You can unit test them independently.
//     Scalability: If the server grows in complexity, you can expand or replace individual handler classes without impacting the rest of the system. This is particularly helpful if you expect the server to handle more sophisticated requests or require additional functionality in the future.

// Cons:

//     Increased Complexity: Splitting the logic into multiple classes increases the number of files and classes in the project, which can be cumbersome for small projects.
//     Overhead: There's some additional complexity in managing multiple classes, which may feel over-engineered if the logic is simple.

package src.server;

import java.io.*;
import java.net.*;
import java.util.concurrent.*;

public class ServerMultiClassHandler {

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

    public static final String END_OF_REQUEST = "END_OF_REQUEST";
    public static final String END_OF_RESPONSE = "END_OF_RESPONSE";

    private Socket clientSocket;

    public ClientHandler(Socket socket) {
        this.clientSocket = socket;
    }

    @Override
    public void run() {
        // Use try-with-resources to manage each handler that needs to close resources
        try (
            ConnectionHandler connectionHandler = new ConnectionHandler(clientSocket);
            FetchHandler fetchHandler = new FetchHandler(clientSocket);
            ResponseHandler responseHandler = new ResponseHandler(clientSocket);
            TerminationHandler terminationHandler = new TerminationHandler(clientSocket)
        ) {
            // 1. Connection Handling
            connectionHandler.handleConnection();

            // 2. Fetch the client's request
            String request = fetchHandler.fetchRequest();

            // 3. transmit to the client
            responseHandler.sendResponse(request);

        } catch (IOException e) {
            System.err.println("Error handling client: " + e.getMessage());
        }
    }
}

// Handle accepting client connections and set up socket parameters
class ConnectionHandler implements AutoCloseable {

    private Socket clientSocket;

    public ConnectionHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    public void handleConnection() throws IOException {
        System.out.println("Handling connection for: " + clientSocket.getInetAddress());
        clientSocket.setSoTimeout(5000); // Timeout for the client connection
    }

    @Override
    public void close() throws IOException {
        // No explicit resource to close here, but could be done if needed
    }
}

// Handle reading the client's request
class FetchHandler implements AutoCloseable {

    private static final String CLIENT_MESSAGE_PREFIX = "Client: "; // Prefix for printing client messages

    private Socket clientSocket;

    public FetchHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    public String fetchRequest() throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()))) {
            String requestLine;
            StringBuilder request = new StringBuilder();
            while ((requestLine = reader.readLine()) != null && !requestLine.contains(ClientHandler.END_OF_REQUEST)) {
                request.append(requestLine).append("\n");
                System.out.println(CLIENT_MESSAGE_PREFIX + requestLine); // Displaying the Client's request
            }
            return request.toString();
        }
    }

    @Override
    public void close() throws IOException {
        // No explicit resource to close here, but could be done if needed
    }
}

// Handle sending the HTTP response
class ResponseHandler implements AutoCloseable {

    private static final String EMPTY_LINE = ""; // Represents an empty line in HTTP requests

    private Socket clientSocket;

    public ResponseHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    public void sendResponse(String request) throws IOException {
        try (PrintWriter writer = new PrintWriter(clientSocket.getOutputStream(), true)) {
            // Send an HTTP response
            writer.println(ServerMultiClassHandler.HTTP_OK_RESPONSE); // HTTP status from Server class
            writer.println(ServerMultiClassHandler.CONTENT_TYPE); // Content-Type header
            writer.println(EMPTY_LINE); // Blank line separating headers and body
            writer.println(ServerMultiClassHandler.SERVER_MESSAGE); // Message sent to the client
            writer.println(ClientHandler.END_OF_RESPONSE); // End of response marker
        }
    }

    @Override
    public void close() throws IOException {
        // No explicit resource to close here, but could be done if needed
    }
}

// Handle terminating the client connection
class TerminationHandler implements AutoCloseable {

    private Socket clientSocket;

    public TerminationHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    public void terminateConnection() {
        try {
            System.out.println("Terminating connection for: " + clientSocket.getInetAddress());
            clientSocket.close(); // Ensure the client socket is closed
        } catch (IOException e) {
            System.err.println("Error closing client socket: " + e.getMessage());
        }
    }

    @Override
    public void close() throws IOException {
        // Close the socket in case it wasn't closed in the terminateConnection method
        if (clientSocket != null && !clientSocket.isClosed()) {
            clientSocket.close();
        }
    }
}
