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

# Create empty Java files in src/main/java
touch src/main/java/com/myapp/model/User.java
touch src/main/java/com/myapp/model/Product.java
touch src/main/java/com/myapp/service/UserService.java
touch src/main/java/com/myapp/service/ProductService.java
touch src/main/java/com/myapp/controller/UserController.java
touch src/main/java/com/myapp/controller/ProductController.java
touch src/main/java/com/myapp/dao/UserDao.java
touch src/main/java/com/myapp/dao/ProductDao.java
touch src/main/java/com/myapp/utils/DateUtils.java
touch src/main/java/com/myapp/utils/StringUtils.java

# Create the resources folder and example properties file
touch src/main/resources/application.properties
touch src/main/resources/log4j2.xml

# Create test files
touch src/test/java/com/myapp/service/UserServiceTest.java
touch src/test/java/com/myapp/dao/UserDaoTest.java

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
echo "Project directory structure created successfully!"
echo "Run 'mvn clean install' to build the project."

