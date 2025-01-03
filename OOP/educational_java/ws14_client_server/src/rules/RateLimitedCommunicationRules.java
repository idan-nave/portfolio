package src.rules;

public class RateLimitedCommunicationRules implements CommunicationRules {
    private final int maxRequestsPerSecond;
    private int requestCount;
    private long lastRequestTime;

    public RateLimitedCommunicationRules(int maxRequestsPerSecond) {
        this.maxRequestsPerSecond = maxRequestsPerSecond;
        this.requestCount = 0;
        this.lastRequestTime = System.currentTimeMillis();
    }

    @Override
    public boolean shouldListen() {
        return true; // Always listen
    }

    @Override
    public boolean shouldTransmit(String data) {
        long currentTime = System.currentTimeMillis();
        long elapsedTime = currentTime - lastRequestTime;

        if (elapsedTime >= 1000) {
            requestCount = 0; // Reset count every second
            lastRequestTime = currentTime;
        }

        if (requestCount < maxRequestsPerSecond) {
            requestCount++;
            return true;
        }

        return false; // Block transmission if rate limit is reached
    }

    @Override
    public boolean shouldRetryOnFailure() {
        return true; // Retry if rate limit is exceeded
    }
}
