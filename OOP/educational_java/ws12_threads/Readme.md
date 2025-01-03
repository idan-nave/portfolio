### README.md

```markdown
# Java Threading Projects

This repository contains solutions for various threading exercises in Java. Each project demonstrates different aspects of working with threads, synchronization, and thread pools.

## Projects Overview

### Project 1: Creating Threads by Extending Thread
- **Goal**: Start five threads where each thread prints numbers from 1 to 10.
- **Explanation**: This project demonstrates how to create a thread by extending the `Thread` class and overriding the `run()` method.
- **Files**:
  - `NumberPrinter.java`: The main class that extends `Thread` and prints numbers from 1 to 10 in each thread.

### Project 2: Implementing Runnable + Thread Priority
- **Goal**: Create multiple threads using the `Runnable` interface, set different thread priorities, and have each thread print numbers that are multiples of its own priority.
- **Explanation**: This project shows how to implement the `Runnable` interface and control thread priorities using `Thread.setPriority()`.
- **Files**:
  - `PriorityPrinter.java`: A `Runnable` implementation that prints multiples of the current thread’s priority.

### Project 3: Synchronization (Shared Counter)
- **Goal**: Synchronize access to a shared counter to avoid race conditions.
- **Explanation**: This project demonstrates how to use synchronization to safely increment a shared counter in multiple threads.
- **Files**:
  - `Counter.java`: A class with a synchronized method to increment a counter.
  - `IncrementTask.java`: A `Runnable` implementation that repeatedly increments the counter in a loop.

### Project 4: Thread Pool (ExecutorService)
- **Goal**: Use an `ExecutorService` to manage a group of threads and submit multiple tasks for parallel execution.
- **Explanation**: This project demonstrates how to use `ExecutorService` to handle a fixed number of threads in a pool and execute multiple tasks concurrently.
- **Files**:
  - `SimpleTask.java`: A simple task that is executed by the thread pool.

### Project 5: Managing Multiple Shared Resources with ReentrantLock
- **Goal**: Use `ReentrantLock` to manage concurrent access to multiple shared resources (e.g., bank accounts).
- **Explanation**: This project demonstrates how to use `ReentrantLock` to handle concurrent transfers between multiple bank accounts while avoiding deadlocks.
- **Files**:
  - `Account.java`: A class representing a bank account with a `ReentrantLock` for thread-safe operations.
  - `TransferTask.java`: A `Runnable` that performs money transfers between bank accounts.

## How to Run the Projects

1. **Clone the repository** (or download the `src` folder if you've generated it using the provided script).
   
2. **Navigate to the desired project directory**:
   ```bash
   cd src/Project1
   ```

3. **Compile and run the project**:
   - For **Project 1** (NumberPrinter):
     ```bash
     javac NumberPrinter.java
     java NumberPrinter
     ```
   - For **Project 2** (PriorityPrinter):
     ```bash
     javac PriorityPrinter.java
     java PriorityPrinter
     ```
   - For **Project 3** (Counter and IncrementTask):
     ```bash
     javac Counter.java IncrementTask.java
     java IncrementTask
     ```
   - For **Project 4** (SimpleTask with ExecutorService):
     ```bash
     javac SimpleTask.java
     java SimpleTask
     ```
   - For **Project 5** (Bank Account with ReentrantLock):
     ```bash
     javac Account.java TransferTask.java
     java TransferTask
     ```

4. **Expected Output**:
   - **Project 1**: Multiple threads printing numbers from 1 to 10 concurrently.
   - **Project 2**: Threads printing multiples of their priority (from 1 to 50).
   - **Project 3**: A synchronized counter value after multiple threads increment it.
   - **Project 4**: Tasks executed by threads in a thread pool, with a shutdown after completion.
   - **Project 5**: Multiple bank account transfers occurring concurrently with proper synchronization using `ReentrantLock`.

## Notes

- For **Project 5**, if you encounter deadlocks or synchronization issues, try using `tryLock` for detecting and handling lock acquisition failures.
- All projects rely on basic multithreading concepts, including thread creation, synchronization, thread priorities, and thread pools.
- The projects are written for Java 8 or later.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```

### Explanation of the README

1. **Project Overview**: A brief description of each project along with the goal and a summary of what it demonstrates.
2. **How to Run the Projects**: Provides clear instructions on how to compile and run each project. Users need to navigate to the appropriate project folder, compile the Java files using `javac`, and then run the class using `java`.
3. **Expected Output**: Describes what the user should expect to see when they run the projects.
4. **Notes**: Additional notes on synchronization and possible deadlock scenarios in Project 5.
5. **License**: A placeholder for the project's license (you can modify or remove it depending on your needs).

You can copy this `README.md` into the root directory of the generated Java project, and it will guide the user on how to interact with each project.
