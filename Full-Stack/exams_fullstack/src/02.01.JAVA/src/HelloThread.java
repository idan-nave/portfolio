package src;
public class HelloThread {

  public static void main(String[] args) {
      Thread thread = new Thread(() -> {
          for (int i = 0; i < 5; i++) {
              System.out.println("Hello from Thread");
              try {
                  Thread.sleep(1000);
              } catch (InterruptedException e) {
                  System.err.println("Thread Error");
              }
          }
      });

      thread.start();

      try {
          thread.join(); //waits for each completion
      } catch (InterruptedException e) {
          System.err.println("Main thread was interrupted: " + e.getMessage());
      }

  }
}
