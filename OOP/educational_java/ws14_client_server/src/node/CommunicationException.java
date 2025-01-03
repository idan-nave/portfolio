package src.node;

public class CommunicationException extends Exception {
    public static final int TIMEOUT_ERROR = 1;
    public static final int CONNECTION_ERROR = 2;
    public static final int COMMUNICATION_ERROR = 3;

    private final int errorCode;

    public CommunicationException(String message, int errorCode) {
        super(message);
        this.errorCode = errorCode;
    }

    public int getErrorCode() {
        return errorCode;
    }
}
