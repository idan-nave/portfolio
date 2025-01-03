```markdown
# MultiTaskingSystem - A Java Threading Demonstration

This project demonstrates key concepts of Java multithreading through several tasks such as thread creation, thread synchronization, priority handling, using thread pools, and managing shared resources. The project is designed to give you a deeper understanding of how threads operate in Java and how you can use them to improve performance and resource management.

## Project Structure

The project is divided into multiple Java classes that demonstrate various threading concepts:

- **BankAccount.java**: This class represents a bank account with a balance and provides synchronized methods for deposits and withdrawals using `ReentrantLock`.
- **TransferTask.java**: A `Runnable` task that performs a money transfer between two bank accounts, demonstrating thread coordination and synchronization.
- **WorkerThread.java**: A simple thread class that demonstrates creating, starting, naming, and managing threads.
- **ThreadMethodsDemo.java**: A class that demonstrates several thread management methods including thread naming, priority setting, sleep, join, and checking if a thread is alive.
- **Main.java**: The main entry point of the project that creates bank accounts and transfers money between them using an `ExecutorService`, demonstrating thread pools.

## Features

1. **Bank Account Management**:
   - Uses `ReentrantLock` to manage access to bank account balances safely from multiple threads.
   - Supports basic deposit and withdrawal operations.

2. **Multi-Threading Concepts**:
   - **Thread Creation**: Threads are created using both extending the `Thread` class and implementing the `Runnable` interface.
   - **Thread Priority**: Threads are given different priorities to simulate different work loads.
   - **Thread Sleep & Join**: Threads sleep for a specified time and use the `join()` method to wait for other threads to complete.
   - **Thread Synchronization**: Threads are synchronized using locks to prevent race conditions when accessing shared resources.

3. **ExecutorService**:
   - Manages a pool of threads to handle concurrent tasks efficiently.

4. **ReentrantLock**:
   - Prevents deadlocks and ensures safe handling of multiple threads accessing shared resources by locking and unlocking in a controlled manner.

## How to Run the Project

### 1. Clone or Download the Project

First, download or clone the repository to your local machine:

```bash
git clone <repository_url>
cd MultiTaskingSystem
```

### 2. Compile the Project

Navigate to the `src/main/java` directory and compile the Java files using the following command:

```bash
javac *.java
```

### 3. Run the Main Class

Once the project is compiled, run the main class to execute the program:

```bash
java Main
```

This will:
- Create two `BankAccount` objects.
- Start multiple threads to transfer money between these accounts.
- Use `ExecutorService` to manage the tasks.
- Display the final balance of each account.

### 4. View the Output

When running the program, you should see output like this:

```
Transfer of 1000.0 from Account-1 to Account-2 was successful.
Transfer of 500.0 from Account-2 to Account-1 was successful.
Final Balance of Account-1: 4500.0
Final Balance of Account-2: 3500.0
```

You will also see log messages demonstrating thread creation, thread names, priorities, and status, including whether the threads are alive or finished.

## Concepts Demonstrated

1. **Creating Threads**:
   - By extending the `Thread` class (`WorkerThread.java`).
   - By implementing the `Runnable` interface (`TransferTask.java`).

2. **Managing Thread Life Cycle**:
   - Starting and naming threads.
   - Setting thread priorities.
   - Managing thread state using `sleep`, `join`, and checking `isAlive()`.

3. **Thread Synchronization**:
   - Using `ReentrantLock` to synchronize shared resources and prevent race conditions.

4. **Using ExecutorService**:
   - Managing a pool of threads and executing tasks concurrently.

5. **Bank Account Simulation**:
   - Demonstrates real-world multi-threading by simulating bank account transactions (transfers between accounts) and safely managing the shared account balance using synchronized methods.

## File Structure

```
MultiTaskingSystem/
├── src/
│   └── main/
│       └── java/
│           ├── BankAccount.java
│           ├── TransferTask.java
│           ├── WorkerThread.java
│           ├── ThreadMethodsDemo.java
│           └── Main.java
```

## Prerequisites

- **Java 8+** is required to compile and run the project.
- An IDE like **Eclipse**, **IntelliJ IDEA**, or a simple text editor and terminal for manual compilation.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```

### How to Add the `README.md` File:

1. **Create the README.md file**:
   - In the root directory of the project, create a new file named `README.md`.

2. **Paste the content**:
   - Copy and paste the content from the markdown above into the `README.md` file.

3. **Commit and Push**:
   - If you are using a version control system (like Git), commit and push the `README.md` file to your repository.

---

This `README.md` file will provide instructions on how to use, build, and run the project, as well as explain the core concepts and classes within the project.
