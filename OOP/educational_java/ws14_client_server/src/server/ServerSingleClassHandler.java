// Implementing Handlers as Methods in One Class (Alternative Approach)

// Pros:

//     Simplicity: Keeping everything in one class is simpler and may make sense if the logic is relatively straightforward and not expected to grow much. There's no need to manage multiple classes or files.
//     Fewer Files: With everything in one class, you don't have to worry about organizing multiple files, which is simpler in small projects.
//     Tightly Coupled Logic: The logic for connection handling, request fetching, response sending, and termination is in one place, which could make the flow more straightforward for smaller systems.

// Cons:

//     Reduced Maintainability: As the server logic grows, it becomes harder to maintain because all functionality is in one class. A change to one part of the code might affect the rest of the logic.
//     Harder to Test: With everything in one class, testing becomes more difficult because the code is not modular. For instance, testing the connection handling logic might require invoking the entire client handler logic, which is not ideal.
//     Violates SRP: A class doing many things (connection, request processing, response handling, termination) is a violation of the Single Responsibility Principle. It makes the class more complex and harder to reason about.
//     Less Flexibility: As your system evolves, it will be harder to modify or extend specific parts of the process (e.g., changing the way requests are processed without touching the connection handling part).

// Best Approach for Your Case

//     If your server is small and simple, and you don't expect it to grow significantly in terms of complexity, implementing them as methods within a single class can be an acceptable approach. It minimizes the overhead of managing multiple classes and keeps things concise.

//     If you expect the server to grow in complexity, handle more diverse or complex requests, or need to handle different client behaviors (such as upgrading the protocol, adding features like authentication, etc.), splitting the handler into different classes is a better long-term solution. This approach makes it easier to maintain, extend, and test each part of the code independently. It also ensures that you follow good design principles such as SRP and makes the code more modular and easier to understand.


package src.server;

import java.io.*;
import java.net.*;
import java.util.concurrent.*;

public class ServerSingleClassHandler {

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
    
    private Socket clientSocket;

    public ClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    @Override
    public void run() {
        try {
            handleConnection();
            String request = fetchRequest();
            sendResponse(request);
        } catch (IOException e) {
            System.err.println("Error handling client: " + e.getMessage());
        } finally {
            terminateConnection();
        }
    }

    private void handleConnection() throws IOException {
        // Handle connection setup
        System.out.println("Handling connection for: " + clientSocket.getInetAddress());
        clientSocket.setSoTimeout(5000); // Set client socket timeout
    }

    private String fetchRequest() throws IOException {
        // Fetch request from client
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()))) {
            StringBuilder request = new StringBuilder();
            String requestLine;
            while ((requestLine = reader.readLine()) != null && !requestLine.contains("END_OF_REQUEST")) {
                request.append(requestLine).append("\n");
            }
            return request.toString();
        }
    }

    private void sendResponse(String request) throws IOException {
        // Send response to client
        try (PrintWriter writer = new PrintWriter(clientSocket.getOutputStream(), true)) {
            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/plain");
            writer.println(""); // Blank line separating headers and body
            writer.println("Hello from the server!");
            writer.println("END_OF_RESPONSE");
        }
    }

    private void terminateConnection() {
        // Close the socket and clean up
        try {
            System.out.println("Terminating connection for: " + clientSocket.getInetAddress());
            clientSocket.close();
        } catch (IOException e) {
            System.err.println("Error closing client socket: " + e.getMessage());
        }
    }
}
