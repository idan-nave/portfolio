package src.rules;

public interface CommunicationRules {
    // Rule for listening. The user defines how often or under what conditions to listen.
    boolean shouldListen();

    // Rule for transmitting. The user defines how often or under what conditions to transmit data.
    boolean shouldTransmit(String data);

    // Optional: Rule for retrying in case of failure
    boolean shouldRetryOnFailure();
}
