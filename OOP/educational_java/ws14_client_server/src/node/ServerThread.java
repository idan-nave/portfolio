package src.node;

// Let's introduce threading to allow concurrent connections. The threading will be particularly important for handling multiple client connections in the server mode.
// ServerThread.java (Thread for each client connection)

import java.io.IOException;
import java.net.Socket;
import src.rules.*;

public class ServerThread extends Thread {
    private Socket clientSocket;
    private GenericConnectionHandler connectionHandler;

    public ServerThread(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    @Override
    public void run() {
        try {
            connectionHandler = new GenericConnectionHandler(clientSocket);
            connectionHandler.setCommunicationRules(new IntervalBasedCommunicationRules(5000, 0)); // Example rule

            String request = connectionHandler.listen();
            System.out.println("Received request: " + request);
            
            connectionHandler.transmit("HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello from server!");
        } catch (IOException | CommunicationException e) {
            e.printStackTrace();
            // Handle exceptions if necessary
        } finally {
            try {
                connectionHandler.close();
            } catch (IOException | CommunicationException e) {
                e.printStackTrace();
            }
        }
    }
}
