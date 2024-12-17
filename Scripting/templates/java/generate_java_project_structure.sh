#!/bin/bash

# Define the project structure
create_structure() {
  # Root directory
  mkdir -p MyJavaProject

  # Create directories for source code
  mkdir -p MyJavaProject/src/main/java/com/myapp/model
  mkdir -p MyJavaProject/src/main/java/com/myapp/service
  mkdir -p MyJavaProject/src/main/java/com/myapp/controller
  mkdir -p MyJavaProject/src/main/java/com/myapp/dao
  mkdir -p MyJavaProject/src/main/java/com/myapp/utils
  mkdir -p MyJavaProject/src/main/resources
  mkdir -p MyJavaProject/src/test/java/com/myapp/service
  mkdir -p MyJavaProject/src/test/java/com/myapp/dao
  mkdir -p MyJavaProject/src/test/resources

  # Create files for source code
  touch MyJavaProject/src/main/java/com/myapp/model/User.java
  touch MyJavaProject/src/main/java/com/myapp/model/Product.java
  touch MyJavaProject/src/main/java/com/myapp/service/UserService.java
  touch MyJavaProject/src/main/java/com/myapp/service/ProductService.java
  touch MyJavaProject/src/main/java/com/myapp/controller/UserController.java
  touch MyJavaProject/src/main/java/com/myapp/controller/ProductController.java
  touch MyJavaProject/src/main/java/com/myapp/dao/UserDao.java
  touch MyJavaProject/src/main/java/com/myapp/dao/ProductDao.java
  touch MyJavaProject/src/main/java/com/myapp/utils/DateUtils.java
  touch MyJavaProject/src/main/java/com/myapp/utils/StringUtils.java

  # Create resource files
  touch MyJavaProject/src/main/resources/application.properties
  touch MyJavaProject/src/main/resources/log4j2.xml

  # Create test files
  touch MyJavaProject/src/test/java/com/myapp/service/UserServiceTest.java
  touch MyJavaProject/src/test/java/com/myapp/dao/UserDaoTest.java

  # Create the top-level files
  touch MyJavaProject/pom.xml
  touch MyJavaProject/README.md
  touch MyJavaProject/.gitignore

  # Write basic content into some of the files

  # pom.xml (Maven project configuration)
  cat <<EOF > MyJavaProject/pom.xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.myapp</groupId>
    <artifactId>MyJavaProject</artifactId>
    <version>1.0-SNAPSHOT</version>
</project>
EOF

  # README.md (Project documentation)
  cat <<EOF > MyJavaProject/README.md
# MyJavaProject
This is a Java project.
EOF

  # .gitignore (Git ignore file)
  cat <<EOF > MyJavaProject/.gitignore
# Ignore compiled bytecode files
*.class

# Ignore target folder (build artifacts)
/target/

# Ignore IDE config files (e.g., IntelliJ, Eclipse)
.idea/
*.iml
*.project
*.classpath
EOF
}

# Call the function to create the project structure
create_structure

echo "Java project structure generated successfully!"

