```markdown
# Consistent Memory Addresses Simulation

This project demonstrates the concept of consistent memory addresses (simulated via Java's `identityHashCode`) for objects before and after toggling ASLR (Address Space Layout Randomization) in a Linux system. The goal is to observe how memory addresses change across different runs of the program when ASLR is enabled or disabled.

## Files in the Project

1. **ConsistentMemoryAddresses.java**  
   This file demonstrates how memory addresses (simulated via `identityHashCode`) for objects can be observed using a simple Java program. The program creates objects, stores them in a `Map`, and prints out their "memory addresses" (simulated by `System.identityHashCode()`) to show how they are allocated in memory.

2. **ConsistentMemoryAddressesSimulated.java**  
   This file is a modified version of `ConsistentMemoryAddresses.java` with an infinite loop added to keep the program running. This was included in the original code you provided, but it doesn't affect the memory address simulation. The infinite loop is removed in the improved version of the program.

3. **aslr_toggle.sh**  
   This is a Bash script that allows you to easily toggle ASLR on or off. The script provides a simple menu for enabling or disabling ASLR on your Linux system.

## Purpose of the Project

This project helps you understand how ASLR can affect the memory layout in systems. The Java Virtual Machine (JVM) abstracts away direct memory management, so the observed memory addresses (via `identityHashCode()`) may vary regardless of ASLR settings. The program attempts to simulate what would happen in a native application if you disabled or enabled ASLR, although it doesn't directly interact with low-level memory management.

### How ASLR Affects Memory
ASLR changes the locations where code, data, and libraries are mapped in memory. While ASLR is mainly relevant to native applications, Java’s memory model abstracts direct memory management from the user, meaning the `identityHashCode()` values can change between runs, but not in the same way as physical memory addresses in C/C++ programs.

## Requirements

- **Operating System:** Linux (for toggling ASLR)
- **Java:** Java 8 or later (Java Development Kit)
- **Permissions:** You must have sufficient permissions to modify system parameters like ASLR (`sudo` access).
- **Bash:** For running the `aslr_toggle.sh` script.

## Steps to Run the Program

### 1. Compile the Java files:

First, compile both Java files using the `javac` command.

```bash
javac ConsistentMemoryAddresses.java
javac ConsistentMemoryAddressesSimulated.java
```

### 2. Use the Bash Script to Toggle ASLR

The project includes a Bash script `aslr_toggle.sh` to help you easily toggle ASLR on or off. To use it:

1. Make the script executable:
   ```bash
   chmod +x aslr_toggle.sh
   ```

2. Run the script:
   ```bash
   sudo ./aslr_toggle.sh
   ```

The script will provide you with a simple menu:
- **Option 1:** Disable ASLR
- **Option 2:** Enable ASLR
- **Option 3:** Exit the script

Choose the option you need based on your testing scenario.

### 3. Run the Java Programs

After compiling the Java files and toggling ASLR (if needed), you can run both programs to observe the simulated memory addresses.

#### Running `ConsistentMemoryAddresses.java`:
```bash
java ConsistentMemoryAddresses
```

#### Running `ConsistentMemoryAddressesSimulated.java`:
```bash
java ConsistentMemoryAddressesSimulated
```

### 4. Observe the output

Both programs will output the simulated memory addresses (using `identityHashCode()`) of the objects stored in the `Map`. If you toggle ASLR, you may notice the addresses could differ across runs, but due to JVM optimizations, the memory addresses of Java objects do not directly correlate with system-level memory addresses affected by ASLR.

### 5. Compare Results

Run the programs multiple times with ASLR enabled and disabled. Compare the outputs to see how the simulated memory addresses change (or remain the same) across runs.

## Notes

- **Simulated Memory Addresses:** The addresses printed by the programs are simulated via `System.identityHashCode()`. These are not real memory addresses, but unique values that can be used to simulate how objects are stored in memory.
  
- **ASLR and Java:** ASLR primarily affects native applications that interact directly with system memory. Java programs, on the other hand, are managed by the JVM, which abstracts memory management. Hence, the effects of ASLR may not be directly observable in Java programs.

- **JVM Optimizations:** The JVM may move objects around in memory for garbage collection or other optimizations, making it harder to observe memory consistency even with ASLR disabled.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for more details.
```

### Key Changes:
1. **Introduction of `aslr_toggle.sh`**: The README now includes a section about the `aslr_toggle.sh` Bash script, which helps the user easily toggle ASLR on or off. This script provides a simple interactive menu to enable/disable ASLR with options for the user.
   
2. **Instructions for Using the Bash Script**: Detailed steps for making the script executable and running it (`chmod +x` and `sudo ./aslr_toggle.sh`), along with an explanation of the interactive menu options.

3. **Improved Workflow**: The README now provides a more streamlined approach for testing memory addresses by first using the script to toggle ASLR, and then running the Java programs to observe any potential changes in simulated memory addresses.

This updated `README.md` should now clearly guide the user through all the steps necessary to test the effects of ASLR on memory addresses using your Java code and the accompanying Bash script.
