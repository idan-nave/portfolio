package company;

import java.util.Random;

public abstract class Person {
    private static long idCounter = 100000000; // Auto-incremented ID starting at 100000000
    private long id;
    private String name;
    private int age;
    private Company company;

    // Default constructor that generates a random person
    public Person() throws InvalidInputException {
        this.id = idCounter++; // Auto-increment ID
        this.name = generateRandomName();
        this.age = generateRandomAge();
        this.company = null; // Default company is null
    }

    // Constructor to set specific fields (if needed)
    public Person(String name, int age, Company company) throws InvalidInputException {
        // Validate person details
        InvalidInputException.checkPersonName(name);
        InvalidInputException.checkAge(age);

        this.id = idCounter++; // Auto-increment ID
        this.name = name;
        this.age = age;
        this.company = company; // May be null
    }

    // Getter and Setter methods
    public long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) throws InvalidInputException {
        if (name == null || name.isEmpty()) {
            throw new InvalidInputException("Name cannot be null or empty.");
        }
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) throws InvalidInputException {
        if (age < 18 || age > 120) {
            throw new InvalidInputException("Age must be between 18 and 120.");
        }
        this.age = age;
    }

    public Company getCompany() {
        return company;
    }

    public void setCompany(Company company) {
        this.company = company;
    }

    // Randomly generate a name (could be expanded for more realistic names)
    private String generateRandomName() {
        String[] names = { "John", "Alice", "Bob", "Sophia", "David", "Eva" };
        Random rand = new Random();
        return names[rand.nextInt(names.length)];
    }

    // Randomly generate an age between 18 and 60
    private int generateRandomAge() {
        Random rand = new Random();
        return rand.nextInt(43) + 18; // Random age between 18 and 60
    }

    // toString method to return a string representation of the person
    @Override
    public String toString() {
        String companyName = (company != null) ? company.getName() : "N/A";
        return "ID: " + id + ", Name: " + name + ", Age: " + age + ", Company: " + companyName;
    }

    // Main method to test the Person class
    public static void main(String[] args) {
        try {
            // Create a company
            Company company1 = new Company("Tech Corp", "Tel-Aviv");

            // Create Person objects with and without a company
            Client personWithCompany = new Client("Alice", 30, company1);
            Client personWithoutCompany = new Client("Bob", 40, null);

            // Print the details of each person
            System.out.println(personWithCompany);
            System.out.println(personWithoutCompany);
        } catch (InvalidInputException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
