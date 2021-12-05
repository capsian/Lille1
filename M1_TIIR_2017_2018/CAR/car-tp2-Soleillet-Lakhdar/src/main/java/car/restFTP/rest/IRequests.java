package car.restFTP.rest;

import org.glassfish.jersey.media.multipart.FormDataParam;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.io.IOException;
import java.io.InputStream;

public interface IRequests {


    /**
     * @param ip : The ip for the FTP Server
     * @param port : The port for the FTP server
     * @param user : The user for the FTP server
     * @param pass : The pass for the FTP server
     * @return String from FTP Server
     * @throws IOException
     */
    @GET
    @Produces(MediaType.TEXT_PLAIN)
    @Path("{ip}:{port}")
    String processConnectToFTP(@PathParam("ip") String ip, @PathParam("port") int port,
                               @HeaderParam("user") String user, @HeaderParam("pass") String pass) throws IOException;


    /**
     * @param ip : The ip for the FTP Server
     * @param port : The port for the FTP server
     * @param user : The user for the FTP server
     * @param pass : The pass for the FTP server
     * @param filename : The file
     * @return Response in octet_stream
     * @throws IOException
     */
    @GET
    @Produces(MediaType.APPLICATION_OCTET_STREAM)
    @Path("{ip}:{port}/retv{filename :(/.*)+}")
    Response processRetv(@PathParam("ip") String ip, @PathParam("port") int port,
                                @HeaderParam("user") String user, @HeaderParam("pass") String pass,
                                @PathParam("filename") String filename) throws IOException;

    /**
     * @param ip : The ip for the FTP Server
     * @param port : The port for the FTP server
     * @param user : The user for the FTP server
     * @param pass : The pass for the FTP server
     * @param uploadedInputStream : The inputStream from form
     * @param fileName : The file
     * @return Response in text
     * @throws IOException
     */
    @POST
    @Consumes(MediaType.MULTIPART_FORM_DATA)
    @Path("{ip}:{port}/stor/{fileName}")
    @Produces("text/html")
    Response processStor(@PathParam("ip") String ip, @PathParam("port") int port,
                                @HeaderParam("user") String user, @HeaderParam("pass") String pass,
                                @FormDataParam("file") InputStream uploadedInputStream,
                                @PathParam("fileName") String fileName) throws IOException;

    /**
     * @param ip : The ip for the FTP Server
     * @param port : The port for the FTP server
     * @param user : The user for the FTP server
     * @param pass : The pass for the FTP server
     * @param curpath : The path
     * @return Response in text_html
     * @throws IOException
     */
    @GET
    @Produces(MediaType.TEXT_HTML)
    @Path("{ip}:{port}/list{curpath :(/.*)+}")
    String processLIST(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass,
                       @PathParam("curpath") String curpath) throws IOException;


    /**
     * @param ip : The ip for the FTP Server
     * @param port : The port for the FTP server
     * @param user : The user for the FTP server
     * @param pass : The pass for the FTP server
     * @param curpath : The path
     * @return Response in text_html
     * @throws IOException
     */
    @GET
    @Produces(MediaType.TEXT_HTML)
    @Path("{ip}:{port}/cwd{curpath :(/.*)+}")
    String processCwd(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass,
                      @PathParam("curpath") String curpath) throws IOException;

    /**
     * @param ip : The ip for the FTP Server
     * @param port : The port for the FTP server
     * @param user : The user for the FTP server
     * @param pass : The pass for the FTP server
     * @param curpath : The path
     * @return Response in text_html
     * @throws IOException
     */
    @GET
    @Produces(MediaType.TEXT_HTML)
    @Path("{ip}:{port}/cwdup{curpath :(/.*)+}")
    String processCwdUp(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass,
                        @PathParam("curpath") String curpath) throws IOException;

    /**
     * @param ip : The ip for the FTP Server
     * @param port : The port for the FTP server
     * @param user : The user for the FTP server
     * @param pass : The pass for the FTP server
     * @return Response in text_html
     * @throws IOException
     */
    @GET
    @Produces(MediaType.TEXT_PLAIN)
    @Path("{ip}:{port}/pwd")
    String processPWD(@PathParam("ip") String ip, @PathParam("port") int port, @HeaderParam("user") String user, @HeaderParam("pass") String pass) throws IOException;

}
