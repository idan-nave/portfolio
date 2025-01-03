package src.node;

public class TestNode {
    public static void main(String[] args) {
        try {
            // Server node example
            GeneralPurposeNode serverNode = new GeneralPurposeNode(true, 8080);
            serverNode.start();

            // Client node example (You can comment out the server start if you just want to test the client)
            // GeneralPurposeNode clientNode = new GeneralPurposeNode(false, "localhost", 8080);
            // clientNode.start();

        } catch (Exception e) {
            ExceptionHandler.handleException(e);
        }
    }
}
