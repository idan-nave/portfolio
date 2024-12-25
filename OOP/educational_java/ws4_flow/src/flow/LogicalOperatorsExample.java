package flow;

public class LogicalOperatorsExample {
    public static void main(String[] args) {
        int age = 18;
        boolean isCitizen = true;
        
        if (age >= 18 && isCitizen) {
            System.out.println("Eligible to vote.");
        } else {
            System.out.println("Not eligible to vote.");
        }
    }
}
