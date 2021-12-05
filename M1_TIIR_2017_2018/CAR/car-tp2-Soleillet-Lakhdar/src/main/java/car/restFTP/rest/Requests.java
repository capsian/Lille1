package car.restFTP.rest;

import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.apache.commons.net.ftp.FTPReply;

import java.io.*;
import java.net.SocketException;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import org.glassfish.jersey.media.multipart.FormDataParam;

@Path("ftp")
public class Requests implements IRequests {

    private FTPClient myClientFtp;

    public Requests(){
        this.myClientFtp = new FTPClient();
    }

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    @Path("{ip}:{port}")
    public String processConnectToFTP(@PathParam("ip") String ip, @PathParam("port") int port,@HeaderParam("user") String user, @HeaderParam("pass") String pass) throws IOException {

        System.out.println("processConnectToFTP catched !!! ip:" + ip + ",port: " + port + ", user: " + user + ", pass:" + pass);

        String reply = connectToFTP(ip,port,user,pass);
    	disconnectFTP();
    	return reply;
    }
    
    @GET
    @Produces(MediaType.APPLICATION_OCTET_STREAM)
    @Path("{ip}:{port}/retv{filename :(/.*)+}")
    public Response processRetv(@PathParam("ip") String ip, @PathParam("port") int port,
                                       @HeaderParam("user") String user, @HeaderParam("pass") String pass,
                                       @PathParam("filename") String filename) throws IOException {

        String retour = connectToFTP(ip, port,user,pass);
        String[] rets = retour.split(" ");
        int replyCode = Integer.parseInt(rets[0]);

        if(replyCode != 230){
            System.out.println("processRetv error !!!!");
            disconnectFTP();
            return Response.serverError().build();
        }else{

            InputStream in = this.myClientFtp.retrieveFileStream(filename);
            disconnectFTP();

            System.out.println("processRetv catched !!! ip:" + ip + ",port: " + port + ", user: " + user + ", pass:" + pass + ", filename:" + filename);

            return Response.ok(in) //TODO: set content-type of your file
                    .header("content-disposition", "attachment; filename = "+ filename)
                    .build();
        }
    }

    @POST
    @Consumes(MediaType.MULTIPART_FORM_DATA)
    @Path("{ip}:{port}/stor/{fileName}")
    @Produces("text/html")
    public Response processStor(@PathParam("ip") String ip, @PathParam("port") int port,
                                @HeaderParam("user") String user, @HeaderParam("pass") String pass,
                                @FormDataParam("file") InputStream uploadedInputStream,
                                @PathParam("fileName") String fileName
                                ) throws IOException {

        System.out.println("processStor catched !!! ip:" + ip + ",port: " + port + ", user: " + user + ", pass:" + pass + ", file: " + fileName);

        String retour = connectToFTP(ip, port,user,pass);
        String[] rets = retour.split(" ");
        int replyCode = Integer.parseInt(rets[0]);

        if(replyCode != 230){
            System.out.println("processStor error !!!!");
            return Response.serverError().build();
        }else{

            this.myClientFtp.storeFile(fileName,uploadedInputStream);

            if (this.myClientFtp.getReplyCode() == 226) {

                disconnectFTP();
                return Response.ok(1).build();
            } else {
                disconnectFTP();
                return Response.ok(-1).build();
            }
        }
    }

    @GET
    @Produces(MediaType.TEXT_HTML)
    @Path("{ip}:{port}/list{curpath :(/.*)+}")
    public String processLIST(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass, @PathParam("curpath") String curpath) throws IOException {

        System.out.println("processLIST catched !!! ip:" + ip + ",port: " + port + ", user: " + user + ", pass:" + pass + ", curpath:" + curpath);

        String reply = connectToFTP(ip, port,user,pass);
        String[] rets = reply.split(" ");
        int replyCode = Integer.parseInt(rets[0]);
        if(replyCode == 230){
        	//List current directory
        	reply = "<html><body>";
        	FTPFile[] files;
        		files = this.myClientFtp.listFiles(curpath);
        		reply += "<a title=\".\" href=\"/ftp/"+ ip + ":" + port +"/list"+ curpath +"\">.</a><br>";
        		reply += "<a title=\"..\" href=\"/ftp/"+ ip + ":" + port +"/cwdup"+ curpath +"\">..</a><br>";
        	for(FTPFile f : files){
        		if(f.isDirectory())
        			reply += "<a title=\""+ f.getName() + "\" href=\"/ftp/"+ ip + ":" + port +"/cwd"+ curpath +f.getName() +"/\">" + f.getName() + "/</a><br>";
        		else
        			reply += "<a title=\""+ f.getName() + "\" href=\"/ftp/"+ ip + ":" + port +"/retv"+ curpath + f.getName() +"/\">" + f.getName() + "/</a><br>";
        	}
        	disconnectFTP();
        	reply += "</body></html>";
        }
        return reply;
    }
    
    @GET
    @Produces(MediaType.TEXT_HTML)
    @Path("{ip}:{port}/cwd{curpath :(/.*)+}")
    public String processCwd(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass, @PathParam("curpath") String curpath) throws IOException {

        System.out.println("processCwd catched !!! ip:" + ip + ",port: " + port + ", user: " + user + ", pass:" + pass + ", curpath:" + curpath);

        String reply = connectToFTP(ip, port,user,pass);
        String[] rets = reply.split(" ");
        int replyCode = Integer.parseInt(rets[0]);
        if(replyCode == 230){
        	this.myClientFtp.changeWorkingDirectory(curpath);
        	String newPath = this.myClientFtp.printWorkingDirectory();
            disconnectFTP();
            return processLIST(ip, port, user, pass,newPath);
        }
        return reply;
    }
    
    @GET
    @Produces(MediaType.TEXT_HTML)
    @Path("{ip}:{port}/cwdup{curpath :(/.*)+}")
    public String processCwdUp(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass, @PathParam("curpath") String curpath) throws IOException {

        System.out.println("processCwdUp catched !!! ip:" + ip + ",port: " + port + ", user: " + user + ", pass:" + pass + ", curpath:" + curpath);

        String reply = connectToFTP(ip, port,user,pass);
        String[] rets = reply.split(" ");
        int replyCode = Integer.parseInt(rets[0]);
        if(replyCode == 230){
        	this.myClientFtp.changeWorkingDirectory(curpath);
        	this.myClientFtp.changeToParentDirectory();
        	String newPath = this.myClientFtp.printWorkingDirectory();
            disconnectFTP();
            return processLIST(ip, port, user, pass,newPath);
        }
        return reply;
    }

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    @Path("{ip}:{port}/pwd")
    public String processPWD(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass) throws IOException {

        System.out.println("processCwdUp catched !!! ip:" + ip + ",port: " + port + ", user: " + user + ", pass:" + pass);

        String reply = connectToFTP(ip, port,user,pass);
        String[] rets = reply.split(" ");
        int replyCode = Integer.parseInt(rets[0]);
        
        if(replyCode == 230){
        	//List current directory
        	reply= this.myClientFtp.printWorkingDirectory();
        	disconnectFTP();
        	
        }
        return reply;
    }

    private String connectToFTP(String ip, int port,String user, String pass) throws SocketException, IOException {

        if (this.connectFTP(ip,port)){
            String reply;
            if(!this.myClientFtp.login(user, pass)){
                reply = this.myClientFtp.getReplyString();
                this.myClientFtp.logout();
                return reply;
            }

            int replyCode = this.myClientFtp.getReplyCode();

            /* FAIL */
            if (!FTPReply.isPositiveCompletion(replyCode)) {
                reply = this.myClientFtp.getReplyString();
                this.myClientFtp.disconnect();
                return reply;
            }
            return this.myClientFtp.getReplyString();
        }
        else
            return "-1 Connection refused";
    }

    private boolean connectFTP(String ip, int port) throws IOException {

        this.myClientFtp.connect(ip,port);

        return this.myClientFtp.getReplyCode() == 220;
    }

   private void disconnectFTP() throws IOException{
	   
   		this.myClientFtp.logout();
   		this.myClientFtp.disconnect();
   }
}
