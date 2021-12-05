package car.ftp;

import java.io.IOException;

import car.ftp.Server.Server;
import car.ftp.usergestion.UserDao;

public class Main {

	static private Server ftpServer;

    public static void main( String[] args ) {

    	int port = 2048;

		System.out.println( "FTP Server !!");

		if (args.length != 0)
			port = Integer.parseInt(args[0]);

		System.out.print("Init server ..... ");
		UserDao.init();
		System.out.println( "Done !");

    	try {

			System.out.print("Starting server on port " + port + " ............. ");
			ftpServer = new Server(port, "");
			ftpServer.start();
			System.out.println( "Done !");

		} catch (IOException e) {

			System.out.println( "Starting Server .... FAILS !!!");
			e.printStackTrace();
		}

        while(true);
    }
}
