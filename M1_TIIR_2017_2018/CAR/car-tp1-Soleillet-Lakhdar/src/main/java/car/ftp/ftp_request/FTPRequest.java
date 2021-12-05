package car.ftp.ftp_request;

import car.ftp.Server.DataSocket;
import car.ftp.messages.Response;
import car.ftp.usergestion.*;

import java.io.*;
import java.net.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;


/**
 * Main class to treat FTP requests
 */
public class FTPRequest extends Thread {

	/* commands */
	private Socket cmdSocket;
	private BufferedReader cmdIn;
	private DataOutputStream cmdOut;

	/* data */
	private DataSocket dataSocket;

	private User currentUser;
	private FTPState state;

	private boolean binaryMode;
	private boolean quit;

	/* IM NOT HERE */
    private String rnfr;

	public FTPRequest(Socket socket) throws IOException {

		super();

		/* init cmd socket */
		this.cmdSocket = socket;
		this.state = FTPState.NOTCONNECTED;

		/* init streams */
		this.cmdIn = new BufferedReader(new InputStreamReader(this.cmdSocket.getInputStream(), "US-ASCII"));
		this.cmdOut = new DataOutputStream(this.cmdSocket.getOutputStream());

		/* init */
		this.dataSocket  = null;
		this.currentUser = null;
		this.binaryMode  = false;
		this.rnfr        = null;
	}

	/*
	 *	Main method to treat all incoming requests
	 *
	 * @return void
	 * @throws IOException
	 */
	void processRequest() throws IOException {

		/* always cheking if the socket is not closed */
		if (!this.cmdSocket.isClosed()) {

			/* read */
			String cmd = this.cmdIn.readLine();
			if(cmd == null)
				return;

			System.out.println("processRequest() enter with cmd = " + cmd);

			/* split */
			Response rep;
			String[] cmds = cmd.split(" ");

			/* CHECK */
			if (cmds.length == 0) {
				System.out.println(" cmds.length == 0 !! ");
				return;
			}

			if (cmds[0].equals("USER") ) {
				
				this.processUSER(cmds);
			}
			else if (cmds[0].equals("PASS")) {
				this.processPASS(cmds);
			}
			else if (cmds[0].equals("PWD")) {
				this.processPWD(cmds);
			}
			else if (cmds[0].equals("CWD")) {
				this.processCWD(cmds);
			}
			else if (cmds[0].equals("SYST")) {
				this.processSYST(cmds);
			}
			else if (cmds[0].equals("RETR")) {
				this.processRETR(cmds);
			}
			else if (cmds[0].equals("STOR")) {
				this.processSTOR(cmds);
			}
			else if (cmds[0].equals("LIST")) {
				this.processLIST(cmds);
			}
			else if (cmds[0].equals("QUIT")) {
				this.processQUIT(cmds);
			}
			else if (cmds[0].equals("TYPE")) {
				this.processTYPE(cmds);
			}
			else if (cmds[0].equals("EPRT")) {
				this.processEPRT(cmds);
			}
			else if (cmds[0].equals("EPSV")) {
				this.processEPSV(cmds);
			}
			else if (cmds[0].equals("PASV")) {
				this.processPASV(cmds);
			}
			else if (cmds[0].equals("PORT")) {
				this.processPORT(cmds);
			}
			else if (cmds[0].equals("CDUP")) {
				this.processCDUP(cmds);
			}
			else if (cmds[0].equals("MKD")) {
				this.processMKD(cmds);
			}
			else if (cmds[0].equals("SIZE")) {
				this.processSIZE(cmds);
			}
			else if (cmds[0].equals("DELE")) {
				this.processDELE(cmds);
			}
            else if (cmds[0].equals("RNFR")) {
                this.processRNFR(cmds);
            }
            else if (cmds[0].equals("RNTO")) {
                this.processRNTO(cmds);
            }
			else {
				System.out.println("INVALID CMD !! : " + cmd);
				rep = new Response("502", "COMMAND NOT IMPLEMENTED");
				this.cmdOut.write(rep.getFormated());
			}
		}
		else {
			this.quit = true;
		}
	}

	private void processSIZE(String[] cmds) throws IOException {

		long size;
		Response rep;

		size = this.currentUser.getDirectoryManager().getSize(cmds[1]);

		rep = new Response("200", "SIZE " + size);

		this.cmdOut.write(rep.getFormated());

		System.out.println("SIZE command received !! " + cmds[1]);
	}

	private void processMKD(String[] cmds) throws IOException {

		Response rep;

		if (this.currentUser.getDirectoryManager().createDir(cmds[1]))
			rep = new Response("257", "Okay");
		else
			rep = new Response("550", "NOT EXECUTED");

		this.cmdOut.write(rep.getFormated());

		System.out.println("MKD command received !! "  + cmds[1]);
	}


    private void processDELE(String[] cmds) throws IOException {

        Response rep;

        if (this.currentUser.getDirectoryManager().delete(cmds[1]))
            rep = new Response("250", "Okay");
        else
            rep = new Response("550", "NOT EXECUTED");

        this.cmdOut.write(rep.getFormated());

        System.out.println("DELE command received !! "  + cmds[1]);
    }

    private void processRNFR(String[] cmds) throws IOException {

        Response rep;

        if (this.currentUser.getDirectoryManager().checkRename(cmds[1])) {

            this.rnfr = cmds[1];
            rep = new Response("250", "Okay");
        }
        else {
            rep = new Response("550", "NOT EXECUTED");
        }

        this.cmdOut.write(rep.getFormated());

        System.out.println("DELE command received !! "  + cmds[1]);
    }

    private void processRNTO(String[] cmds) throws IOException {

        Response rep;

        if (this.rnfr == null) {
            rep = new Response("503", "BAD SEQUENCE NUMBER");
        } else {
            if (this.currentUser.getDirectoryManager().moveFile(this.rnfr, cmds[1])) {

                this.rnfr = null;
                rep = new Response("250", "Okay");
            }
            else {
                rep = new Response("550", "NOT EXECUTED");
            }
        }

        this.cmdOut.write(rep.getFormated());

        System.out.println("DELE command received !! "  + cmds[1]);
    }

	/*
	 *	SYST request: UNIX
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processSYST(String[] cmds) throws IOException {

		Response rep;
		rep = new Response("215", "UNIX");

		this.cmdOut.write(rep.getFormated());

		System.out.println("SYST command received !!");
	}

	/*
	 *	USER request: check the user
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processUSER(String[] cmds) throws IOException {

		Response rep;
		String user;
		if(cmds.length < 2)
			user= "nopass";
		else user = cmds[1];
		/* fail */
		if (!UserDao.userList.isValidUserName(user)) {

			/* Update state */
			this.state = FTPState.NOTCONNECTED;

			/* error reply */
			rep = new Response("530", "INVALID USERNAME");
		}
		else {
			this.currentUser = UserDao.userList.getUser(user);
			/* check if we dont need a password */
			if (!this.currentUser.needAPassword()) {
				this.state = FTPState.CONNECTED;
				rep = new Response("230", "USER LOGGED IN");
			}
			else {
				this.state = FTPState.WAITINGPASSWORD;
				rep = new Response("331", "USERNAME OK, NEED PASSWORD");
			}
		}

		this.cmdOut.write(rep.getFormated());
		System.out.println("USER command received !! " + user);

	}

	/*
	 *	PASS request: check the password
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processPASS(String[] cmds) throws IOException {

		Response rep;
		String pass;
		if(cmds.length < 2)
			pass= "";
		else pass = cmds[1];
		if(this.state == FTPState.WAITINGPASSWORD) {
			/* fail */
			if (!this.currentUser.authenticate(pass)) {

				/* Update state && reply */
				this.state = FTPState.NOTCONNECTED;
				rep = new Response("530", "INVALID PASSWORD");
			}
			else {

				/* update state && reply*/
				this.state = FTPState.CONNECTED;
				rep = new Response("230", "SUCCESS AUTH");
			}
		}else {
			/*Dont have the right to use that commande now*/
			rep = new Response("503","Bad Sequence commande");
		}

		this.cmdOut.write(rep.getFormated());
		System.out.println("PASS command received !! " + pass);
	}

	/*
	 *	EPSV request: entering extended passive mode; let the server open the SvSocket
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processEPSV(String[] cmds) throws IOException {

		Response rep;
		int port;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* open server */
		this.dataSocket = new DataSocket(true, null, 0);
		port = this.dataSocket.getSvSocket().getLocalPort();

		/* resp with PORT */
		rep = new Response("229", "Entering Extended Passive Mode (|||" + port + "|)");

		this.cmdOut.write(rep.getFormated());

		/* WAIT */
		this.dataSocket.acceptPASV();

		System.out.println("EPSV command received !!, port opend = " + port);
	}

	/*
	 *	EPRT request: ...................
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processEPRT(String[] cmds) throws IOException {

		Response rep;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* split address */
		String[] cmdsSplit = cmds[1].split("\\|");

		int port = Integer.parseInt(cmdsSplit[3]);

		this.dataSocket = new DataSocket(false, "localhost", port);

		rep = new Response("200", "EPRT OK");

		this.cmdOut.write(rep.getFormated());
		System.out.println("EPRT command received !! port = " + port);
	}

	/*
	 *	PORT request, wiat for the server to connect to the PORT opened by the client
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processPORT(String[] cmds) throws IOException {

		Response rep;
		String ip;
		int port;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* split address */
		String[] cmdsSplit = cmds[1].split(",");

		/* extract ip */
		ip = cmdsSplit[0] + "." + cmdsSplit[1] + "." + cmdsSplit[2] + "." + cmdsSplit[3];

		/* extract port */
		port  = Integer.parseInt(cmdsSplit[4]) << 8;
		port += Integer.parseInt(cmdsSplit[5]);

		this.dataSocket = new DataSocket(false, "localhost", port);

		rep = new Response("200", "PORT OK");

		this.cmdOut.write(rep.getFormated());
		System.out.println("PORT command received !! ip = " + ip + ", port = " + port);
	}

	/*
	 *	PASV request: entering passive mode, let the server create the SvSocket
	 *				  return port + ip in the correct format
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processPASV(String[] cmds) throws IOException {

		Response rep;
		int ip1,ip2,ip3,port1,port2;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		this.dataSocket = new DataSocket(true, null, 0);

		port1 = this.dataSocket.getSocket().getLocalPort() / 256;
		port2 = this.dataSocket.getSocket().getLocalPort() % 256;

		rep = new Response("200", "PORT " + this.dataSocket.getSocket().getLocalPort());

		this.cmdOut.write(rep.getFormated());

		this.dataSocket.acceptPASV();

		System.out.println("PASV command received !! getPassivePort = " + this.dataSocket.getSocket().getLocalPort());
	}

	/*
	 *	PWD request: print working directory
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processPWD(String[] cmds) throws IOException {

		Response rep;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		rep = new Response("257", this.currentUser.getDirectoryManager().printWorkingDirectory());
		this.cmdOut.write(rep.getFormated());

		System.out.println("PWD command received !! FTPState = " + this.state + ", PWD = " + this.currentUser.getDirectoryManager().printWorkingDirectory());
	}

	/*
	 *	CWD request:	change working directory
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processCWD(String[] cmds) throws IOException {

		boolean ok = false;
		Response rep;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* check dir */
		ok = this.currentUser.getDirectoryManager().changeWorkingDirectory(cmds[1]);
		if (ok)
			rep = new Response("250", "Okay");
		else
			rep = new Response("550", cmds[1] + " No such file or directory.");

		this.cmdOut.write(rep.getFormated());
		System.out.println("CWD command received !! changed = " + ok);
	}

	/*
	 *	RETR request:	dowloand a file
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processRETR(String[] cmds) throws IOException {

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* notify for reply */
		Response open = new Response("150", "OPENING DATA SOCKET");
		this.cmdOut.write(open.getFormated());

		/* check file */
		Path target = this.currentUser.getDirectoryManager().getCurrentDir();
		target = target.resolve(Paths.get(cmds[1]));

		System.out.println("processRETR catched !! target = " + target.toString());

		/* copy */
		Files.copy(target.toAbsolutePath(), this.dataSocket.getOutputStream());

		Response close = new Response("226", "TRANSFER COMPLETE");
		this.cmdOut.write(close.getFormated());
		//this.dataSocket.close();
		this.dataSocket.getOutputStream().close();
		//this.dataSocket.getSvSocket().close();

		System.out.println("RETR command received !! \n");
	}

	/*
	 *	SOTR request:	Upload a file
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processSTOR(String[] cmds) throws IOException {

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* notify for reply */
		Response open = new Response("150", "OPENING DATA SOCKET");
		this.cmdOut.write(open.getFormated());

		/* check file */
		Path target = this.currentUser.getDirectoryManager().getCurrentDir();
		target = target.resolve(Paths.get(cmds[1]));

		/* copy */
		Files.copy(this.dataSocket.getInputStream(), target.toAbsolutePath());

		Response close = new Response("226", "TRANSFER COMPLETE");
		this.cmdOut.write(close.getFormated());
		//this.dataSocket.close();
		this.dataSocket.getOutputStream().close();

		System.out.println("STOR command received !! " + cmds[1]);
	}

	/*
	 *	LIST request:	list current directory
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processLIST(String[] cmds) throws IOException {

		String tmpList;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* update state && reply*/
		Response open = new Response("150", "OPENING DATA SOCKET");
		this.cmdOut.write(open.getFormated());

		OutputStream tmpDataSocket = this.dataSocket.getOutputStream();

		if(cmds.length == 1) {

			tmpList = this.currentUser.getDirectoryManager().listCurrentLocation("");

			tmpDataSocket.write(new Response(tmpList).getFormated());
		}
		else{
			tmpDataSocket.write(this.currentUser.getDirectoryManager().listCurrentLocation(cmds[1]).getBytes("US-ASCII"));
		}
			

		Response close = new Response("226", "TRANSFER COMPLETE");
		this.cmdOut.write(close.getFormated());
		tmpDataSocket.close();

		System.out.println("LIST command received !!");
	}

	/*
	 *	QUIT request
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processQUIT(String[] cmds) throws IOException {
		Response rep = new Response("221", "Disconnected");
		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		this.state = FTPState.NOTCONNECTED;
		this.currentUser.getDirectoryManager().reset();
		this.cmdOut.write(rep.getFormated());
		this.quit = true;
	}

	/*
	 *	TYPE request:	changing the format of communication
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processTYPE(String[] cmds) throws IOException {

		Response rep;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		rep = new Response("200", "CHANGED TYPE");

		if ((cmds[1].equals("I")) || ((cmds[1].equals("L"))) )
			this.binaryMode = true;
		else
			this.binaryMode = false;

		this.cmdOut.write(rep.getFormated());
		System.out.println("TYPE command received !! " + cmds[1] + ", binaryMode = " + this.binaryMode);
	}

	/*
	 *	CDUP request:	change to parent directory
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void processCDUP(String[] cmds) throws IOException {

		Response rep;
		boolean ok;

		/* CONNECTION FAIL */
		if (!checkConnection()) {
			return;
		}

		/* check dir */
		ok = this.currentUser.getDirectoryManager().changeWorkingDirectory("/..");
		if (ok) {
			rep = new Response("250", "Okay");
		}
		else {
			rep = new Response("550", " No such file or directory.");
		}

		this.cmdOut.write(rep.getFormated());
		System.out.println("CDUP command received !! ok = " + ok);
	}

	/*
	 *	Hello request:	hello message
	 *
	 * @param String[] cmd: the command (with params)
	 * @return void
	 * @throws IOException
	 */
	private void hello() throws IOException {

		Response rep = new Response("220", "Hello !");

		this.cmdOut.write(rep.getFormated());

		return;
	}

	/*
	 *	Check if there is a connected user
	 *
	 * @return boolean
	 * @throws IOException
	 */
	private boolean checkConnection() throws IOException {

		Response rep;

		if (this.state != FTPState.CONNECTED) {

			rep = new Response("530", "NOT CONNECTED");
			this.cmdOut.write(rep.getFormated());

			return false;
		}
		else
			return true;
	}

	public void run() {

		try {
			this.quit = false;
			this.hello();

		} catch (IOException e) {
			System.out.println("HELLO ERROR");
			return;
		}

		while (!this.quit) {

			try {

				processRequest();

			} catch (IOException e) {

				System.out.println("Erreur imposible de lire req client");
				e.printStackTrace();
				break;
			}
		}

		try {
			this.cmdSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
