package company;

public class Client extends Person {
    private static final int MAX_SPENDINGS = 30; // Max spendings to track
    private double[] spendings; // Array to track last 30 spendings
    private int currentIndex; // To keep track of the next position in the array

    // Default constructor that generates a random client with random spendings
    public Client() throws InvalidInputException {
        super(); // Call the Person's default constructor
        spendings = new double[MAX_SPENDINGS];
        currentIndex = 0;
    }

    // Constructor to set specific fields (name, age, company) with random spendings
    public Client(String name, int age, Company company) throws InvalidInputException {
        super(name, age, company); // Call the Person's constructor

        spendings = new double[MAX_SPENDINGS];
        currentIndex = 0;
    }

    // Method to spend money, replaces the oldest spending if the array is full
    public void spendMoney(double amount) throws InvalidInputException {
        // Validate the spending amount (should not be negative)
        InvalidInputException.checkSpendingAmount(amount);

        if (currentIndex < MAX_SPENDINGS) {
            spendings[currentIndex++] = amount; // Add to the next available index
        } else {
            // If array is full, shift all elements to the left and add the new spending
            System.arraycopy(spendings, 1, spendings, 0, MAX_SPENDINGS - 1);
            spendings[MAX_SPENDINGS - 1] = amount;
        }
        System.out.println("Spent: " + amount);
    }

    // Method to print all the spendings
    public void printSpendings() {
        System.out.println("Last " + currentIndex + " Spendings:");
        for (int i = 0; i < currentIndex; i++) {
            System.out.println("Spending " + (i + 1) + ": " + spendings[i]);
        }
    }

    // Override toString to include spending information
    @Override
    public String toString() {
        return super.toString() + ", Spendings: " + currentIndex;
    }

    // Main method to test the Client class
    public static void main(String[] args) {
        try {
            // Create a company
            Company company1 = new Company("Tech Corp", "Tel-Aviv");

            // Create a Client object
            Client client = new Client("Alice", 30, company1);

            // Spend some money
            client.spendMoney(100.50);
            client.spendMoney(200.75);
            client.spendMoney(50.00);
            client.spendMoney(120.30);

            // Print client details and spendings
            System.out.println(client);
            client.printSpendings();

        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
