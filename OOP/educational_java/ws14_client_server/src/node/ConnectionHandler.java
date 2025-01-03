package src.node;

import java.io.IOException;

import src.rules.CommunicationRules;

public interface ConnectionHandler extends AutoCloseable {
    String END_OF_TRAFFIC = "END_OF_TRAFFIC"; // Marker to signal end of communication

    // Method to listen for traffic (can be either request or response depending on the role)
    String listen() throws IOException, CommunicationException;

    // Method to transmit data to the other party (either request or response)
    void transmit(String data);

    // Method for the user to define how the communication will occur (using strategies)
    void setCommunicationRules(CommunicationRules rules);

    // Close method for auto closing resources
    @Override
    void close() throws IOException, CommunicationException;
}
