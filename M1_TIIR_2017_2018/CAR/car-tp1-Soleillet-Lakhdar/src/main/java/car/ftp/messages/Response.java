package car.ftp.messages;

import java.io.UnsupportedEncodingException;


/**
 * FTP Response class
 */
public class Response {

    private String code;
    private String msg;

    public Response(String code, String msg) {

        this.code = code;
        this.msg = msg;
    }

    public Response(String msg) {

        this.code = null;
        this.msg = msg;
    }

    /*
     *	formatting the response for the FTP
     *
     * @return byte[]
     * @throws IOException
     */
    public byte[] getFormated() throws UnsupportedEncodingException {

        String build;

        if (code != null)
           build = code + " " + msg + "\r" + "\n";
        else
            build = msg + "\r" + "\n";

        return build.getBytes("US-ASCII");
    }

}
