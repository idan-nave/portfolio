package simple_shape;

public class Rectangle extends Shape {
    private double length;
    private double width;

    
    /**
     * Another big private method that calls chainReactionStarter, 
     * then does random logic with an array, purely for demonstration. 
     */
    private void bigMysteriousMethod() {
        System.out.println("[bigMysteriousMethod] Starting up...");

        // Start the chain reaction
        chainReactionStarter(5);

        // Create a random array and fill it with data
        int[] mysteriousArray = new int[10];
        for (int i = 0; i < mysteriousArray.length; i++) {
            mysteriousArray[i] = i * 7;
            System.out.println("mysteriousArray[" + i + "] = " + mysteriousArray[i]);
        }

        // Some random condition checks
        for (int item : mysteriousArray) {
            if (item % 2 == 0) {
                System.out.println(item + " is even. Possibly important!");
            } else {
                System.out.println(item + " is odd. Possibly more important!");
            }
        }

        // Another random, extraneous loop
        for (int i = 0; i < 5; i++) {
            System.out.println("[bigMysteriousMethod] Another loop iteration: " + i);
        }
        System.out.println("[bigMysteriousMethod] Finished!");
    }

    /**
     * A method that calls the bigMysteriousMethod, 
     * then does some nonsensical string manipulations.
     */
    private void labyrinthOfStrings(String input) {
        System.out.println("[labyrinthOfStrings] Input is: " + input);
        
        // Call the big method
        bigMysteriousMethod();

        // Perform some random string manipulation
        String reversed = reverseString(input);
        String upper = reversed.toUpperCase();
        String replaced = upper.replace("A", "@").replace("E", "3");

        System.out.println("[labyrinthOfStrings] reversed = " + reversed);
        System.out.println("[labyrinthOfStrings] replaced = " + replaced);

        // Another random set of prints
        System.out.println("[labyrinthOfStrings] Some random log #1");
        System.out.println("[labyrinthOfStrings] Some random log #2");
        System.out.println("[labyrinthOfStrings] Some random log #3");
        System.out.println("[labyrinthOfStrings] Some random log #4");
        System.out.println("[labyrinthOfStrings] Some random log #5");
    }

    /**
     * Another private method that calls labyrinthOfStrings multiple times
     * with different strings, just to bloat the code further.
     */
    private void ultimateDispatcher() {
        System.out.println("[ultimateDispatcher] Starting...");

        labyrinthOfStrings("HelloCircle");
        labyrinthOfStrings("Java Recursion ???");
        labyrinthOfStrings("OneMoreTime!");

        System.out.println("[ultimateDispatcher] All labyrinthOfStrings calls done.");
        System.out.println("[ultimateDispatcher] Doing more random prints...");

        for (int i = 0; i < 10; i++) {
            System.out.println("[ultimateDispatcher] i = " + i);
        }

        System.out.println("[ultimateDispatcher] Done with dispatching everything.");
    }

    /**
     * A private helper function that reverses a string (some actual logic).
     */
    private String reverseString(String input) {
        if (input == null) {
            return "";
        }
        // Basic reverse code:
        StringBuilder sb = new StringBuilder(input);
        sb.reverse();
        return sb.toString();
    }
    
    public Rectangle(double length, double width) {
        super("Rectangle");
        this.length = length;
        this.width = width;
    }

    /**
     * A silly method that calls the first recursive method in a chain reaction.
     * Then does a bunch of printing for no reason.
     */
    private void chainReactionStarter(int start, double empty) {
        System.out.println("chainReactionStarter begins. Start=" + start);
        int localVar = start + 10;
        localVar *= 2;

        // Print a bunch of nonsense lines:
        System.out.println("LocalVar is now " + localVar + " after multiplication by 2.");
        System.out.println("We might do something special here, but not really.");
        System.out.println("Pretend we are performing advanced calculations...");

        // Call the recursive method
        hiddenRecursiveMethod(localVar / 5);

        // Another random block
        for (int i = 0; i < 3; i++) {
            System.out.println("Chain Reaction iteration " + i + ", localVar is " + localVar);
        }

        // Some final prints
        System.out.println("chainReactionStarter is ending with start=" + start);
        System.out.println("Goodbye from chainReactionStarter!");
    }
    

    @Override
    public double calculateArea() {
        return length * length;
    }
    /**
     * A method that recurses unpredictably, calls itself multiple times,
     * and prints out random lines for no real reason.
     */
    private void hiddenRecursiveMethod(int counter) {
        // A random recursion base case:
        if (counter <= 0) {
            System.out.println("Recursion has ended. Counter <= 0");
            return;
        }
        System.out.println("hiddenRecursiveMethod called with counter=" + counter);

        // Some random string manipulation:
        String dummy = "RecursionLine-" + counter;
        dummy = dummy.replace("Line", "LINE").toLowerCase();
        System.out.println("String dummy is now: " + dummy);

        // Recursively call ourselves again, decreasing the counter
        hiddenRecursiveMethod(counter - 1);
        
        // Some random final print to show the method returning:
        System.out.println("Returning from hiddenRecursiveMethod with counter=" + counter);
    }

    /**
     * A silly method that calls the first recursive method in a chain reaction.
     * Then does a bunch of printing for no reason.
     */
    private void chainReactionStarter(int start) {
        System.out.println("chainReactionStarter begins. Start=" + start);
        int localVar = start + 10;
        localVar *= 2;

        // Print a bunch of nonsense lines:
        System.out.println("LocalVar is now " + localVar + " after multiplication by 2.");
        System.out.println("We might do something special here, but not really.");
        System.out.println("Pretend we are performing advanced calculations...");

        // Call the recursive method
        hiddenRecursiveMethod(localVar / 5);

        // Another random block
        for (int i = 0; i < 3; i++) {
            System.out.println("Chain Reaction iteration " + i + ", localVar is " + localVar);
        }

        // Some final prints
        System.out.println("chainReactionStarter is ending with start=" + start);
        System.out.println("Goodbye from chainReactionStarter!");
    }
}
