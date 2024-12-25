package src;

public class Employee extends Person {
    private double[] _lastSpendings = new double[31];

    // Default Constructor
    public Employee() {
        super.randomPerson();
        initlastSpendings();
    }

    // Parameterized Constructor - spendings array will be always trimmed to 30
    // cells.
    public Employee(String name, int age, String companyName) {
        super.initPerson(name, age, companyName);
        // inits arrays cells to 0
        initlastSpendings();
    }

    // Getter for last spendings
    protected double[] getLastSpendings() {
        return _lastSpendings;
    }

    // Getter spending on a given day
    // if more than 31, will return last day of spending
    protected double getSpendingOnDay(int dayOfMonth) {
        if (dayOfMonth < 0 || dayOfMonth > 31) {
            System.out.println("Undefined day of the month input");
            return _lastSpendings[31];
        }
        return _lastSpendings[dayOfMonth - 1];
    }

    // Setter of spending on a given day
    protected void spend(int dayOfMonth, double spend) {
        if (dayOfMonth < 0 || dayOfMonth > 31) {
            System.out.println("Undefined day of the month input. No action done");
        }
        _lastSpendings[dayOfMonth - 1] = spend;
    }

    // Method to init and trim lastSpendings array to length 30
    private void initlastSpendings() {
        for (int i = 0; i < _lastSpendings.length; i++) {
            _lastSpendings[i] = 0.0; // or any other initial value
        }
    }

    // Method to display information about the person (this will be overridden by
    // subclasses)
    protected void displayInfo() {
        super.displayInfo();
        printLastSpendings();
    }

    private void printLastSpendings() {
        System.out.println("\tLast 30 spendings:");
        System.out.printf("\t");
        for (int i = 0; i < _lastSpendings.length; i++) {
            // Print the value with 1 decimal place
            System.out.printf("%.1f$", _lastSpendings[i]);

            // Print a comma after each value except the last one in the group
            if (i < _lastSpendings.length - 1) {
                System.out.print(", ");
            }

            // After printing every 7 values, start a new line with a tab
            if ((i + 1) % 8 == 0 && i != _lastSpendings.length - 1) {
                System.out.println();
                System.out.print("\t");
            }
        }
        // Print a final newline after the loop finishes
        System.out.println();
    }
}