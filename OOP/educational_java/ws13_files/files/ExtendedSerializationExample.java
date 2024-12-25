package files;

import java.io.*;

class PersonExtended implements Serializable {
    private String name;
    private int age;
    private String email;

    public PersonExtended(String name, int age, String email) {
        this.name = name;
        this.age = age;
        this.email = email;
    }

    public String getName() { return name; }
    public int getAge() { return age; }
    public String getEmail() { return email; }
}

public class ExtendedSerializationExample {
    public static void main(String[] args) {
        // Serialize the object
        PersonExtended person = new PersonExtended("Alice", 25, "alice@example.com");
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("personExtended.ser"))) {
            out.writeObject(person);
        } catch (IOException e) {
            System.out.println("Error serializing object: " + e.getMessage());
        }

        // Deserialize the object
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream("personExtended.ser"))) {
            PersonExtended deserializedPerson = (PersonExtended) in.readObject();
            System.out.println("Deserialized Person:");
            System.out.println("Name: " + deserializedPerson.getName());
            System.out.println("Age: " + deserializedPerson.getAge());
            System.out.println("Email: " + deserializedPerson.getEmail());
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Error deserializing object: " + e.getMessage());
        }
    }
}
