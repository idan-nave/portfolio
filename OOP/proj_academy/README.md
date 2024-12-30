# YOU CAN FIND THIS PROJECT IN MY REPO COLLECTION !!!

---

# Academy Management System

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Installation](#installation)
    - [Clone the Repository](#clone-the-repository)
    - [Compiling the Code](#compiling-the-code)
    - [Running the Application](#running-the-application)
5. [Usage](#usage)
    - [Main Menu Options](#main-menu-options)
    - [Adding Students and Courses](#adding-students-and-courses)
    - [Enrolling Students in Courses](#enrolling-students-in-courses)
    - [Recording Grades](#recording-grades)
    - [Viewing Data](#viewing-data)
    - [Saving and Loading Data](#saving-and-loading-data)
    - [Exporting and Importing Data](#exporting-and-importing-data)
6. [Data Persistence](#data-persistence)
7. [Error Handling](#error-handling)
8. [Code Structure](#code-structure)
9. [Examples](#examples)
10. [Contributing](#contributing)
11. [License](#license)


## Overview

The **Academy Management System** is a console-based Java application designed to help academies manage students, courses, grades, and other related data. The system provides functionality to:
- Add students and courses.
- Enroll students in courses.
- Record grades for students.
- View all students, courses, and grades.
- Save and load data to/from a file.
- Serialize and deserialize the entire system for persistent data storage.

This system simulates an academic environment where the operations are managed through a simple command-line interface.

## Features

- **Add Student**: Add a student to the system with their name and email.
- **Add Course**: Add a new course with a course name and credit hours.
- **Enroll Student**: Enroll a student in a course (students can enroll in multiple courses).
- **Record Grade**: Record a grade for a student in a specific course.
- **Show Students**: Display a list of all students.
- **Show Courses**: Display a list of all courses.
- **Show Grades**: Display a list of all grades for enrolled students.
- **Save Data**: Save the current state of the system to a file.
- **Load Data**: Load the data from a previously saved file.
- **Export Data**: Export the system data to a serialized file.
- **Import Data**: Import data from a serialized file, replacing the current data in memory.

## Requirements

To run this project, ensure you have the following installed on your machine:
- **Java 11 or higher**
- **A terminal or command prompt** for running the application

## Installation

### Clone the Repository

Start by cloning the repository to your local machine. You can do this using the following Git command:

```bash
git clone https://github.com/your-username/academy-management-system.git
```

### Compiling the Code

After cloning the repository, navigate to the project folder and compile the Java files:

```bash
javac -d bin src/academy/*.java
```

This will compile all the Java files and place the compiled `.class` files in the `bin` directory.

### Running the Application

Once compiled, you can run the application using the following command:

```bash
java -cp bin academy.Main
```

This will start the application, and you'll be presented with the main menu in the console.

## Usage

### Main Menu Options

The application will display the following menu with available options:

```
1. Add Student                2. Add Course               3. Enroll Student
4. Record Grade               5. Show All Students        6. Show All Courses
7. Show All Grades            8. Save Data (to file)      9. Load Data (read last saved file)
10. Export Data (Serialized)  11. Import Data (Serialized) 12. Exit
```

### Adding Students and Courses

To add a student, select option `1`. You will be prompted to provide the student's name and email. A unique student ID will be automatically generated.

To add a course, select option `2`. You will be asked to provide the course name and the number of credit hours.

### Enrolling Students in Courses

To enroll a student in a course, select option `3`. You will need to input the student's ID and the course's ID. If the student is not already enrolled in the course, they will be added.

### Recording Grades

To record a grade for a student in a course, select option `4`. You will be prompted to provide the student ID, course ID, and the grade value. The grade will be stored in the system.

### Viewing Data

You can view the list of students, courses, and grades by selecting the corresponding options:

- Option `5` shows all students.
- Option `6` shows all courses.
- Option `7` shows all grades.

### Saving and Loading Data

You can save the current system state (students, courses, and grades) to a text file with option `8`:

- **Save Data**: Save the current data to a plain text file.
- **Load Data**: Option `9` allows you to load the data from the last saved file.

### Exporting and Importing Data

The system also supports exporting and importing the data in a serialized format:

- **Export Data (Serialized)**: Select option `10` to export the entire system data as a `.ser` file.
- **Import Data (Serialized)**: Option `11` imports the serialized data and overwrites the current system data.

### Exiting the Application

To exit the application, select option `12`.

## Data Persistence

The system supports data persistence in two ways:

1. **Saving to and loading from a plain text file**: This stores the basic system data (students, courses, and grades).
2. **Serialization and deserialization**: This allows the entire system state to be serialized into a `.ser` file, enabling a complete snapshot of the data (including student enrollments and grades).

### Save/Load File Format
- **Save Data**: Stores data in a plain text file (e.g., `academy_system_data.txt`) in a structured format.
- **Serialized Data**: Stores the entire system (students, courses, grades, etc.) as a serialized `.ser` file (e.g., `academy_system_data.ser`).

## Error Handling

The application is designed with robust error handling to ensure smooth user interaction. Some of the key error handling features include:

- **Invalid Input**: The system checks for invalid inputs (e.g., incorrect student ID or course ID) and informs the user if they try to perform an unsupported action.
- **Duplicate Entries**: Prevents a student from being enrolled in the same course multiple times.
- **File I/O Errors**: Handles errors when attempting to load/save data from/to a file.
- **Serialization Errors**: Catches errors that may occur during serialization or deserialization processes.

## Code Structure

The project is structured into the following key classes:

- **AcademySystem**: Manages all students, courses, and grades. Provides methods to add students, courses, enroll students, and record grades.
- **Student**: Represents a student, with properties such as ID, name, and email, and methods to manage enrollment in courses.
- **Course**: Represents a course, with properties such as ID, name, and credit hours, and methods to manage enrolled students.
- **Grade**: Represents a grade for a student in a specific course.
- **DataManager**: Handles file I/O, serialization, and deserialization operations, as well as data export and import.
- **AcademyErrorHandler**: Contains methods for custom error handling related to student, course, and grade operations.
- **Main**: Contains the main entry point for running the application and interacting with the user through the console interface.

## Examples

### Example Menu Interaction

```
Academy Management System
1. Add Student                2. Add Course               3. Enroll Student
4. Record Grade               5. Show All Students        6. Show All Courses
7. Show All Grades            8. Save Data (to file)      9. Load Data (read last saved file)
10. Export Data (Serialized)  11. Import Data (Serialized) 12. Exit

Choose an option: 1
Enter student name: John Doe
Enter student email: john.doe@example.com
Student John Doe has been added successfully.
```

### Example Error Handling

```
Choose an option: 3
Enter student ID: ABC123
Enter course ID: CS101
Error: Student with ID ABC123 not found.
```

## Contributing

Contributions to the Academy Management System are welcome! To contribute, follow these steps:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -m 'Add new feature'`).
4. Push to your branch (`git push origin feature-branch`).
5. Create a pull request.

Feel free to report any issues or suggestions in the issues section of this repository.

## License

This project is open-source and licensed under the [MIT License](LICENSE).


