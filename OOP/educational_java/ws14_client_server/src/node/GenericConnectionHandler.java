package src.node;

import java.io.IOException;
import java.io.*;
import java.net.*;
import src.rules.*;

public class GenericConnectionHandler implements ConnectionHandler {
    private static final int CLIENT_TIMEOUT = 5000;
    private Socket socket;
    private BufferedReader reader;
    private PrintWriter writer;
    private CommunicationRules communicationRules;
    @SuppressWarnings("unused")
    private boolean isClient;

    public GenericConnectionHandler(Socket socket) throws IOException {
        this.socket = socket;
        this.socket.setSoTimeout(CLIENT_TIMEOUT);
        this.reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.writer = new PrintWriter(socket.getOutputStream(), true);
        this.isClient = false; // Server mode by default
    }

    public GenericConnectionHandler(String serverAddress, int serverPort) throws IOException {
        this.isClient = true;
        this.socket = new Socket(serverAddress, serverPort);
        this.socket.setSoTimeout(CLIENT_TIMEOUT);
        this.reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.writer = new PrintWriter(socket.getOutputStream(), true);
    }

    @Override
    public String listen() throws IOException, CommunicationException {
        try {
            if (communicationRules.shouldListen()) {
                StringBuilder response = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null && !line.contains(END_OF_TRAFFIC)) {
                    response.append(line).append("\n");
                }
                return response.toString();
            }
        } catch (IOException e) {
            throw new CommunicationException("Failed to listen due to I/O error.", CommunicationException.COMMUNICATION_ERROR);
        }
        return null; // No data if the rule says not to listen
    }

    @Override
    public void transmit(String data) {
        // try {
            if (communicationRules.shouldTransmit(data)) {
                writer.println(data);
                writer.println(END_OF_TRAFFIC); // End of transmission marker
            }
        // } catch (CommunicationException e) {
        //     throw new CommunicationException("Failed to transmit data.", CommunicationException.COMMUNICATION_ERROR);
        // }
    }

    @Override
    public void close() throws IOException, CommunicationException {
        try {
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
            if (reader != null) {
                reader.close();
            }
            if (writer != null) {
                writer.close();
            }
        } catch (IOException e) {
            throw new CommunicationException("Failed to close connection.", CommunicationException.CONNECTION_ERROR);
        }
    }

    @Override
    public void setCommunicationRules(CommunicationRules rules) {
        this.communicationRules = rules;
    }
}
