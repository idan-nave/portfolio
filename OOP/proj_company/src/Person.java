package src;

//for this project use - a person cannot be of its own, it must be inherited by other classes in order to be instantiated.
abstract class Person {
    // Static & Encapsulation: a static quality of the class shared by all objects,
    // will be setted with constructor / method
    private static int ID_COUNTER = 100000000;

    // Encapsulation: Private variables with _ prefix
    protected String _name;
    protected int _age;
    protected int _id;
    private String _companyName;

    // not a constructor - but acts like it
    public void randomPerson() {
        _name = "Someone";
        _age = 0;
        _companyName = "Some Company";
        _id = genID();
    }

    // not a constructor - but acts like it
    public void initPerson(String name, int age, String companyName) {
        _name = name;
        _age = age;
        _companyName = companyName;
        _id = genID();
    }

    // Getter for _name (Encapsulation)
    protected String getName() {
        return _name;
    }

    // Getter for _age (Encapsulation)
    protected int getAge() {
        return _age;
    }

    // Getter for _companyName
    public String getCompanyName() {
        return _companyName;
    }

    // Setter for _name
    protected void setCompanyName(String companyName) {
        _companyName = companyName;
    }

    // Method to display information about the person
    // (but not abstract, in order to allow use of this method as standalone and not
    // overwrite it)
    protected void displayInfo() {
        System.out.println("Personal Data: " + _name + ", Age: " + _age + ", ID: " + _id + ", Company: " + _companyName);
    }

    // Method to increment the id of the new person,
    // belongs to Person class, and no to any of Person instances, and only Once!
    private static int genID() {
        return ++ID_COUNTER;
    }
}
