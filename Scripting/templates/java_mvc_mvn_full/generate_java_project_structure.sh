#!/bin/bash

# Define the root project folder
PROJECT_DIR="MyJavaProject"

# Create the root project directory
mkdir -p $PROJECT_DIR

# Navigate into the project directory
cd $PROJECT_DIR

# Create the Maven standard folder structure
mkdir -p src/main/java/com/myapp/model
mkdir -p src/main/java/com/myapp/service
mkdir -p src/main/java/com/myapp/controller
mkdir -p src/main/java/com/myapp/dao
mkdir -p src/main/java/com/myapp/utils
mkdir -p src/main/resources
mkdir -p src/test/java/com/myapp/service
mkdir -p src/test/java/com/myapp/dao
mkdir -p target

# Create the Java files and add code to each

# Model Layer
cat <<EOL > src/main/java/com/myapp/model/User.java
package com.myapp.model;

public class User {
    private int id;
    private String name;

    public User(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "User{id=" + id + ", name='" + name + "'}";
    }
}
EOL

cat <<EOL > src/main/java/com/myapp/model/Product.java
package com.myapp.model;

public class Product {
    private int id;
    private String name;
    private double price;

    public Product(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return "Product{id=" + id + ", name='" + name + "', price=" + price + "}";
    }
}
EOL

# Service Layer
cat <<EOL > src/main/java/com/myapp/service/UserService.java
package com.myapp.service;

import com.myapp.model.User;
import com.myapp.dao.UserDao;

public class UserService {

    private UserDao userDao;

    public UserService(UserDao userDao) {
        this.userDao = userDao;
    }

    public User getUserById(int id) {
        return userDao.findById(id);
    }

    public void addUser(User user) {
        userDao.save(user);
    }
}
EOL

cat <<EOL > src/main/java/com/myapp/service/ProductService.java
package com.myapp.service;

import com.myapp.model.Product;
import com.myapp.dao.ProductDao;

public class ProductService {

    private ProductDao productDao;

    public ProductService(ProductDao productDao) {
        this.productDao = productDao;
    }

    public Product getProductById(int id) {
        return productDao.findById(id);
    }

    public void addProduct(Product product) {
        productDao.save(product);
    }
}
EOL

# Controller Layer
cat <<EOL > src/main/java/com/myapp/controller/UserController.java
package com.myapp.controller;

import com.myapp.model.User;
import com.myapp.service.UserService;

public class UserController {

    private UserService userService;

    public UserController(UserService userService) {
        this.userService = userService;
    }

    public void createUser(int id, String name) {
        User user = new User(id, name);
        userService.addUser(user);
    }

    public void displayUser(int id) {
        User user = userService.getUserById(id);
        System.out.println(user);
    }
}
EOL

cat <<EOL > src/main/java/com/myapp/controller/ProductController.java
package com.myapp.controller;

import com.myapp.model.Product;
import com.myapp.service.ProductService;

public class ProductController {

    private ProductService productService;

    public ProductController(ProductService productService) {
        this.productService = productService;
    }

    public void createProduct(int id, String name, double price) {
        Product product = new Product(id, name, price);
        productService.addProduct(product);
    }

    public void displayProduct(int id) {
        Product product = productService.getProductById(id);
        System.out.println(product);
    }
}
EOL

# DAO Layer
cat <<EOL > src/main/java/com/myapp/dao/UserDao.java
package com.myapp.dao;

import com.myapp.model.User;
import java.util.HashMap;
import java.util.Map;

public class UserDao {

    private Map<Integer, User> database = new HashMap<>();

    public User findById(int id) {
        return database.get(id);
    }

    public void save(User user) {
        database.put(user.getId(), user);
    }
}
EOL

cat <<EOL > src/main/java/com/myapp/dao/ProductDao.java
package com.myapp.dao;

import com.myapp.model.Product;
import java.util.HashMap;
import java.util.Map;

public class ProductDao {

    private Map<Integer, Product> database = new HashMap<>();

    public Product findById(int id) {
        return database.get(id);
    }

    public void save(Product product) {
        database.put(product.getId(), product);
    }
}
EOL

# Utility Layer
cat <<EOL > src/main/java/com/myapp/utils/DateUtils.java
package com.myapp.utils;

import java.text.SimpleDateFormat;
import java.util.Date;

public class DateUtils {

    public static String formatDate(Date date) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        return sdf.format(date);
    }
}
EOL

cat <<EOL > src/main/java/com/myapp/utils/StringUtils.java
package com.myapp.utils;

public class StringUtils {

    public static String capitalize(String input) {
        if (input == null || input.isEmpty()) {
            return input;
        }
        return input.substring(0, 1).toUpperCase() + input.substring(1);
    }
}
EOL

# Test Layer (Simple Unit Test Examples)
cat <<EOL > src/test/java/com/myapp/service/UserServiceTest.java
package com.myapp.service;

import com.myapp.model.User;
import com.myapp.dao.UserDao;
import org.junit.Test;
import static org.junit.Assert.*;

public class UserServiceTest {

    @Test
    public void testAddUser() {
        UserDao userDao = new UserDao();
        UserService userService = new UserService(userDao);

        User user = new User(1, "John Doe");
        userService.addUser(user);

        User result = userService.getUserById(1);
        assertNotNull(result);
        assertEquals("John Doe", result.getName());
    }
}
EOL

cat <<EOL > src/test/java/com/myapp/dao/UserDaoTest.java
package com.myapp.dao;

import com.myapp.model.User;
import org.junit.Test;
import static org.junit.Assert.*;

public class UserDaoTest {

    @Test
    public void testSaveAndFindById() {
        UserDao userDao = new UserDao();

        User user = new User(1, "Jane Doe");
        userDao.save(user);

        User result = userDao.findById(1);
        assertNotNull(result);
        assertEquals("Jane Doe", result.getName());
    }
}
EOL

# Create the resources folder and example properties file
touch src/main/resources/application.properties
touch src/main/resources/log4j2.xml

# Create a minimal pom.xml for Maven setup
cat <<EOL > pom.xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.myapp</groupId>
    <artifactId>my-java-project</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>

    <dependencies>
        <!-- JUnit for testing -->
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.13.1</version>
            <scope>test</scope>
        </dependency>

        <!-- Log4j for logging (optional) -->
        <dependency>
            <groupId>org.apache.logging.log4j</groupId>
            <artifactId>log4j-api</artifactId>
            <version>2.14.1</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <!-- Compiler plugin to ensure Java 1.8 compatibility -->
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>1.8</source>
                    <target>1.8</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>
EOL

# Create .gitignore file to exclude generated files
cat <<EOL > .gitignore
# Ignore compiled class files
*.class

# Ignore Maven target folder
/target/

# Ignore IDE specific files (IntelliJ, Eclipse, etc.)
.idea/
.vscode/

# Ignore log files
*.log

# Ignore operating system specific files
.DS_Store
Thumbs.db
EOL

# Confirmation message
echo "Project directory structure with MVC code created successfully!"
echo "Run 'mvn clean install' to build the project."

