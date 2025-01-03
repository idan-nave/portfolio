package src.rules;

public class IntervalBasedCommunicationRules implements CommunicationRules {
    private final long intervalMs; // Interval in milliseconds
    private final long maxDurationMs; // Maximum duration for the communication (0 = unlimited)
    private long startTime;

    public IntervalBasedCommunicationRules(long intervalMs, long maxDurationMs) {
        this.intervalMs = intervalMs;
        this.maxDurationMs = maxDurationMs;
        this.startTime = System.currentTimeMillis();
    }

    @Override
    public boolean shouldListen() {
        long elapsedTime = System.currentTimeMillis() - startTime;
        return elapsedTime < maxDurationMs || maxDurationMs == 0;
    }

    @Override
    public boolean shouldTransmit(String data) {
        long elapsedTime = System.currentTimeMillis() - startTime;
        if (elapsedTime >= intervalMs) {
            startTime = System.currentTimeMillis();
            return true;
        }
        return false;
    }

    @Override
    public boolean shouldRetryOnFailure() {
        return false; // No retry mechanism in this rule
    }
}
