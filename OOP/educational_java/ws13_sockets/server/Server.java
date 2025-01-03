// javac -d bin server/*.java
// java -cp bin server.Server 

package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import server.Handler;

public class Server {

	private final static int PORT = 3001;
	private final static int THREAD_POOL_SIZE = 6;

	public static void main(String[] args) {
		ExecutorService threadPool = Executors.newFixedThreadPool(THREAD_POOL_SIZE);
		
		try (ServerSocket server = new ServerSocket(PORT)){
			System.out.println("Server is listening on port "+PORT);
			
			while(true) {
				Socket socket = server.accept();
				System.out.println("New client connected");
				
				threadPool.submit(new Handler(socket));
			}
		} catch (IOException e) {
			System.out.println("ERROR IN SERVER");
			e.printStackTrace();
		}
	}
}
