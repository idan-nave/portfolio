package src.node;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import src.rules.*;

public class GeneralPurposeNode {
    private boolean isServer;
    private String serverAddress;
    private int serverPort;

    // Constructor for server-side operation
    public GeneralPurposeNode(boolean isServer, int serverPort) {
        this.isServer = isServer;
        this.serverPort = serverPort;
    }

    // Constructor for client-side operation
    public GeneralPurposeNode(boolean isServer, String serverAddress, int serverPort) {
        this.isServer = isServer;
        this.serverAddress = serverAddress;
        this.serverPort = serverPort;
    }

    public void start() {
        if (isServer) {
            startServer();
        } else {
            startClient();
        }
    }

    private void startServer() {
        try (ServerSocket serverSocket = new ServerSocket(serverPort)) {
            System.out.println("Server listening on port " + serverPort);
            while (true) {
                try {
                    Socket clientSocket = serverSocket.accept();
                    System.out.println("New client connected: " + clientSocket.getInetAddress());
                    ServerThread serverThread = new ServerThread(clientSocket);
                    serverThread.start(); // Start a new thread to handle the connection
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void startClient() {
        try (GenericConnectionHandler connectionHandler = new GenericConnectionHandler(serverAddress, serverPort)) {
            connectionHandler.setCommunicationRules(new RateLimitedCommunicationRules(5)); // Apply rate-limiting rule
            connectionHandler.transmit("GET / HTTP/1.1\nHost: " + serverAddress);
            String response = connectionHandler.listen();
            System.out.println("Received response: " + response);
        } catch (IOException | CommunicationException e) {
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        // Example: Server node
        GeneralPurposeNode serverNode = new GeneralPurposeNode(true, 8080);
        serverNode.start();

        // Example: Client node
        // GeneralPurposeNode clientNode = new GeneralPurposeNode(false, "localhost", 8080);
        // clientNode.start();
    }
}
