package src.node;

public class ExceptionHandler {

    public static void handleException(Exception e) {
        if (e instanceof CommunicationException) {
            CommunicationException commEx = (CommunicationException) e;
            switch (commEx.getErrorCode()) {
                case CommunicationException.TIMEOUT_ERROR:
                    System.err.println("Timeout occurred: " + e.getMessage());
                    break;
                case CommunicationException.CONNECTION_ERROR:
                    System.err.println("Connection error: " + e.getMessage());
                    break;
                case CommunicationException.COMMUNICATION_ERROR:
                    System.err.println("Communication error: " + e.getMessage());
                    break;
                default:
                    System.err.println("Unknown error: " + e.getMessage());
                    break;
            }
        } else {
            System.err.println("Generic error: " + e.getMessage());
        }
    }
}
