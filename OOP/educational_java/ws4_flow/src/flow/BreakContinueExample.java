package flow;

public class BreakContinueExample {
    public static void main(String[] args) {
        for (int i = 1; i <= 10; i++) {
            if (i == 5) {
                break;  // Stop the loop when i is 5
            }
            if (i == 7) {
                continue;  // Skip this iteration when i is 7
            }
            System.out.println(i);
        }
    }
}
