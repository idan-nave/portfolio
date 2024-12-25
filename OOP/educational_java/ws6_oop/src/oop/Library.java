package oop;

public class Library {
    public String publicField = "Public Access";
    protected String protectedField = "Protected Access";
    String defaultField = "Default Access";
    private String privateField = "Private Access";

    public void printFields() {
        System.out.println(publicField);
        System.out.println(protectedField);
        System.out.println(defaultField);
        System.out.println(privateField);
    }

    public static void main(String[] args) {
        Library library = new Library();
        library.printFields();
    }
}
