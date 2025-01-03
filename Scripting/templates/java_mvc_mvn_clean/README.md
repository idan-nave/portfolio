### Project Hierarchy for an MVC Design Pattern & Maven Project - Clean (Skeleton, no code)

```
MyJavaProject/                          # Root folder of the project
├── src/                                # Maven source directory
│   ├── main/                           # Main application code (Java code and resources)
│   │   ├── java/                       # Java source files
│   │   │   └── com/                    # Root package for your application
│   │   │       └── myapp/              # Custom package name, replace 'myapp' with your own app name
│   │   │           ├── model/          # Model/Domain layer (data entities, business objects)
│   │   │           │   ├── User.java   # Represents a 'User' entity (user data like id, name, email, etc.)
│   │   │           │   └── Product.java # Represents a 'Product' entity (product data like id, name, price, etc.)
│   │   │           ├── service/        # Service/Business logic layer (handles core logic)
│   │   │           │   ├── UserService.java   # Logic to manage user-related operations (e.g., register, update)
│   │   │           │   └── ProductService.java # Logic to manage product-related operations (e.g., add, remove)
│   │   │           ├── controller/     # Presentation/Controller layer (e.g., Spring MVC controller)
│   │   │           │   ├── UserController.java   # Controller for handling user-related HTTP requests
│   │   │           │   └── ProductController.java # Controller for handling product-related HTTP requests
│   │   │           ├── dao/             # Data Access layer (interacts with database)
│   │   │           │   ├── UserDao.java  # Database operations for the 'User' entity (insert, update, delete)
│   │   │           │   └── ProductDao.java # Database operations for the 'Product' entity
│   │   │           └── utils/           # Utility/helper layer for reusable code (e.g., formatting)
│   │   │               ├── DateUtils.java    # Utility methods for date manipulation
│   │   │               └── StringUtils.java  # Utility methods for string operations
│   │   ├── resources/                  # Non-code resources like config files
│   │   │   ├── application.properties  # Configuration file (e.g., Spring config, DB settings)
│   │   │   └── log4j2.xml              # Logging configuration for Log4j2 or other frameworks
│   ├── test/                           # Unit tests for the project
│   │   ├── java/                       # Test source files
│   │   │   └── com/                    # Mirror of 'src/main/java/com'
│   │   │       └── myapp/              # Custom test package name
│   │   │           ├── service/        # Unit tests for the service layer
│   │   │           │   └── UserServiceTest.java  # Test class for UserService methods
│   │   │           └── dao/            # Unit tests for the data access layer
│   │   │               └── UserDaoTest.java  # Test class for UserDao methods
│   └── target/                         # Output directory for compiled files (generated by Maven)
├── .gitignore                          # Specifies files and directories Git should ignore (e.g., compiled classes, IDE files)
├── README.md                           # Project documentation: Setup, instructions, etc.
└── pom.xml                             # Maven Project Object Model (POM) file that defines the project configuration and dependencies
```

### Key Points:
1. **`src/main/java/`**: Contains all the core Java source code.
   - **Model**: Holds data classes such as `User.java` and `Product.java`.
   - **Service**: Contains business logic classes like `UserService.java` and `ProductService.java`.
   - **Controller**: Responsible for handling user requests (e.g., `UserController.java` and `ProductController.java`).
   - **DAO**: Responsible for interacting with the database or other data sources, such as `UserDao.java` and `ProductDao.java`.
   - **Utils**: Contains utility classes, such as `DateUtils.java` and `StringUtils.java`, used across the application.

2. **`src/main/resources/`**: Contains non-Java resources.
   - **`application.properties`**: Configuration settings (e.g., database connection settings, application settings).
   - **`log4j2.xml`**: Configuration for logging.

3. **`src/test/java/`**: Contains test classes.
   - These classes should mirror the structure of the main source code.
   - For example, tests for `UserService.java` would go in `UserServiceTest.java`.

4. **`target/`**: This is where Maven will output compiled class files after running the build (`mvn compile`), along with the packaged application (`mvn package`). You shouldn't put source code or tests here manually.

5. **`bin/`**: This folder is not typically needed in Maven projects. Maven handles compilation and output automatically through the `target/` folder. You should remove `bin/`.

### MVC Hierarchy:
    Model Layer: Defines the basic entities like User and Product.
    Service Layer: Contains business logic, such as UserService and ProductService, which interact with the DAO layer.
    Controller Layer: Implements basic controllers, UserController and ProductController, that interact with the services and represent the "controller" in MVC.
    DAO Layer: Provides simple data storage and retrieval functionality using in-memory HashMap. The UserDao and ProductDao classes simulate data access operations like save and findById.
    Utility Layer: Includes utility methods for common tasks such as string capitalization (StringUtils) and date formatting (DateUtils).
    Test Layer: Provides basic unit tests for the UserService and UserDao classes using JUnit.

After Running the Script:

    Start writing your code or modify the generated files as needed.
    Run the unit tests with Maven:

mvn test

### Building and Running the Project:

Using Maven:

    mvn clean install
    
Using Javac:

1. Compile the code

To compile the project, navigate to the src directory and run the following command in your terminal:

javac -d bin src/main/java/com/myapp/*.java

This will compile the .java files and output the .class files into the bin/ directory.
2. Run the Project

To run the compiled Java classes, use the following command:

java -cp bin com.myapp.Main

This assumes your Main.java is located in src/main/java/com/myapp/ and contains the main() method to start the application.
Testing the Project

After running the create_basic_java_project.sh script, unit tests are automatically placed in the src/test/java/com/myapp/ directory. You can compile and run these tests using the following commands:
Compile the tests:

javac -d bin src/test/java/com/myapp/*.java

Run the tests:

java -cp bin org.junit.runner.JUnitCore com.myapp.utils.MathUtilsTest

Note: You must have JUnit set up as a dependency if you are running tests. If you don't already have it installed, you can either include it manually or add it to a build tool like Maven.

### Additional Notes:
- **`pom.xml`**: This file defines your project's dependencies, plugins, and other build configurations. This is the heart of a Maven project and needs to be configured correctly for dependency management and building the project.
- **`.gitignore`**: This file will tell Git to ignore compiled files (`target/`, `.class` files), IDE settings (e.g., `.idea/`, `.vscode/`), and other generated files that don’t belong in source control.

### Conclusion:
- This structure ensures that your project remains modular and follows the **MVC design pattern**.
- The separation of concerns between the **Model**, **View (Controller)**, **Service**, and **DAO** layers is preserved, which makes the code more maintainable and testable.
- Maven's default directory structure works well with the MVC pattern, and once set up properly, it will manage dependencies, build, and testing effectively.


