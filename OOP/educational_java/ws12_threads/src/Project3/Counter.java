// - **Project 3**: A synchronized counter value after multiple threads increment it.

public class Counter {
    private int count = 0;

    public synchronized void increment() {
        count++;
    }

    public int getCount() {
        return count;
    }
}

// What does synchronized do?
// The synchronized keyword ensures that only one thread at a time can access the increment() method for a particular instance of the Counter class. This mechanism is crucial for preventing race conditions when multiple threads are attempting to modify the shared count variable concurrently.

// How does synchronized work?
// When a method is marked as synchronized, Java ensures that only one thread can execute that method on a given object at a time. Here's how it works:

//     Locking:
//         When a thread enters a synchronized method, it must acquire a lock on the object that owns the method (in this case, the instance of the Counter object).
//         If another thread is already inside a synchronized method of the same Counter instance, the second thread will be blocked (i.e., it will have to wait) until the lock is released by the first thread.
//     Thread Access:
//         Only one thread can execute the synchronized method at a time for a particular object. So, if one thread is inside the increment() method, any other thread attempting to enter this method will have to wait until the first thread finishes and releases the lock.
//     Release of Lock:
//         The lock is released when the thread exits the synchronized method (either by finishing the method or throwing an exception).
//         If a thread is blocked on the lock, it will be allowed to enter the method once the lock becomes available.

// Will the entire class be locked?
// No, the entire class is not locked. The lock is applied to the instance of the class (the object on which the method is called). Here's why:

//     In your example, the increment() method is synchronized, so only one thread can access the method at a time for a particular Counter object.
//     This means if you have multiple Counter objects, each one can be accessed concurrently by different threads (because each object has its own lock). However, if multiple threads are working on the same instance of Counter, only one thread can execute the increment() method at any given time.