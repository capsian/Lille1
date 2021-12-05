package car.ftp.Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import car.ftp.ftp_request.FTPRequest;
/**
 * @author soleillet
 *
 */
public class Server extends Thread {

	private ServerSocket server_socket;
	private boolean run = false;
	private List<FTPRequest> clients;
	
	/**
	 * @param port : The port for the FTP Server
	 * @param root_directory : The root directory for the FTP server 
	 * @throws IOException 
	 */
	public Server(int port, String root_directory) throws IOException{
		super();
		this.server_socket = new ServerSocket(port);
		this.clients = new ArrayList<FTPRequest>();
	}
	
	
	/**
	 * Permit to start listening on the ServerSocket
	 * Once he is connected we delegate to an FtpRequest Session
	 * @throws IOException
	 */
	public void start_listening() throws IOException{
		Socket socketClient;
		FTPRequest newClient;
		this.run = true;
		while(this.run){
			socketClient = this.server_socket.accept();
			newClient = new FTPRequest(socketClient);
			this.clients.add(newClient);
			newClient.start();
		}
	}
	
	public void run(){
		try {
			start_listening();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void close_server(){
		this.run = false;
	}
}
