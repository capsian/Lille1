package car.ftp.Server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class DataSocket {

    private Socket dataSocket;
    private ServerSocket dataSvSocket;

    /* ACTIVE socket */
    public DataSocket(boolean passive, String host, int port) throws IOException {

        if (passive) {
            this.dataSvSocket = new ServerSocket(0);
        }
        else {
            this.dataSvSocket = null;
            this.dataSocket = new Socket(host, port);
        }
    }

    public void acceptPASV() throws IOException {
        this.dataSocket = this.dataSvSocket.accept();
    }

    public Socket getSocket() {
        return this.dataSocket;
    }

    public ServerSocket getSvSocket() {
        return this.dataSvSocket;
    }

    public InputStream getInputStream() throws IOException {
        return this.dataSocket.getInputStream();
    }

    public OutputStream getOutputStream() throws IOException {
        return this.dataSocket.getOutputStream();
    }

    public void close() throws IOException {
        this.dataSvSocket.close();
        this.dataSocket.close();
    }
}
