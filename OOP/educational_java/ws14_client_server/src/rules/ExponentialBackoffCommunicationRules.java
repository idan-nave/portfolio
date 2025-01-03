package src.rules;

public class ExponentialBackoffCommunicationRules implements CommunicationRules {
    private int retryCount;
    private final long initialDelayMs;
    private final long maxDelayMs;

    public ExponentialBackoffCommunicationRules(long initialDelayMs, long maxDelayMs) {
        this.retryCount = 0;
        this.initialDelayMs = initialDelayMs;
        this.maxDelayMs = maxDelayMs;
    }

    @Override
    public boolean shouldListen() {
        return true; // Always listen
    }

    @Override
    public boolean shouldTransmit(String data) {
        try {
            long delay = Math.min(initialDelayMs * (long)Math.pow(2, retryCount), maxDelayMs);
            Thread.sleep(delay);
            retryCount++;
            return true;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return false;
        }
    }

    @Override
    public boolean shouldRetryOnFailure() {
        return true; // Retry indefinitely with exponential backoff
    }
}
