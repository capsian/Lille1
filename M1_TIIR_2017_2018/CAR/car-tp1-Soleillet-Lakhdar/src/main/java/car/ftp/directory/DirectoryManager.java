package car.ftp.directory;


import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.PosixFileAttributeView;
import java.nio.file.attribute.PosixFileAttributes;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Set;

/**
 * @author soleillet
 *
 */
public class DirectoryManager {
	
	private Path baseDirectory;
	private Path currentDirectory;

	public DirectoryManager(String directory) {
		this.baseDirectory = Paths.get(directory);
		this.currentDirectory = Paths.get(directory);
	}
	
	/**
	 * @param repo : The directory or file to list must be in the currentDirectory
	 * @return List of string representation for each file in repo
	 * @throws IOException 
	 */
	public String listCurrentLocation(String repo) throws IOException  {
		repo = getRealDirectory(repo);
		System.out.println(repo);
		Path tmpPath;
		if (verifyCurrentDirectoryInsideBaseDirectory(repo)) {
			tmpPath = this.currentDirectory.resolve(repo);
			tmpPath = tmpPath.normalize();
		}
		else{
			tmpPath = this.baseDirectory;
		}
		
		String strInfo;
		if(Files.isDirectory(tmpPath)) {

			String stringDir = "";

			DirectoryStream<Path> directories = Files.newDirectoryStream(tmpPath);

			for(Path subDir : directories) {

				strInfo = getInfoFiles(subDir);

				if (strInfo != null)
					stringDir += strInfo;
			}

			return stringDir;
		}
		else
			return getInfoFiles(tmpPath);
	}

	public Path getCurrentDir() {
		return this.currentDirectory;
	}
	
	
	/**
	 * @param file The path to the file to get description
	 * @return String description for the given file
	 * @throws IOException if unable to read attribute file
	 */
	public String getInfoFiles(Path file) throws IOException{

		File tmpFile = file.toFile();
		String strInfo = "";
		String info2 = "";
		if(Files.exists(file) && Files.isReadable(file)) {
			
			if(Files.isDirectory(file)){
				strInfo += "d";
			}else{
				strInfo += "-";
			}
			Set<PosixFilePermission> set = Files.getPosixFilePermissions(file);
			strInfo += PosixFilePermissions.toString(set);
			
			PosixFileAttributes attr = Files.readAttributes(file, PosixFileAttributes.class);
			
			Integer nlink = (Integer) Files.getAttribute(file, "unix:nlink");
			strInfo += "  " + nlink + " ";
			/* set user & group */
			strInfo += attr.owner().getName() + " " + attr.group().getName() + " ";

			/* set size */
			info2 = attr.size() + " ";

			/* set date */
			Date dt = new Date(tmpFile.lastModified());
			SimpleDateFormat dtFormat = new SimpleDateFormat("dd HH:mm");
			SimpleDateFormat tmp = new SimpleDateFormat("MMM");
			String tmp2 = tmp.format(dt);
			tmp2 =  tmp2.substring(0,3);
			
			String dtTxt = dtFormat.format(dt);
			info2 +=  tmp2 + " " +dtTxt+ " " ;

			/* set filename */
			info2 += file.getFileName();
					
			strInfo += info2 + "\r\n";

	        return strInfo;

		}
		else
			return null;
}
	
	/**
	 * Print you the current directory
	 * @return current_directory
	 */
	public String printWorkingDirectory(){
		return this.currentDirectory.toString().replaceFirst(this.baseDirectory.toString(),"") + "/";
	}
	
	public String getRealDirectory(String repo){
		return this.currentDirectory.toString() + repo;
	}
	
	/**
	 * Permit you to change your current directory
	 * @param rep The directory you want to reach
	 * @return True if you can move to the directory else False
	 */
	public boolean changeWorkingDirectory(String rep){
		if(rep.charAt(0) != '/')
			rep = '/' + rep;
		rep = getRealDirectory(rep);
		System.out.println(rep);
		Path tmp_path = this.currentDirectory.resolve(rep);
		tmp_path = tmp_path.normalize();

		if(verifyCurrentDirectoryInsideBaseDirectory(rep)) {
			if(Files.exists(tmp_path)) {
				this.currentDirectory = tmp_path;
				return true;
			}
		}

		return false;
	}

	public boolean createDir(String path) throws IOException {
		path =  getRealDirectory(path);
		Path tmp = this.currentDirectory.resolve(path);
		tmp.normalize();

		//System.out.println("tmp = " + tmp.toAbsolutePath());

		return tmp.toFile().mkdir();
	}

	public boolean delete(String path) throws IOException {

		Path tmp = this.currentDirectory.resolve(path);
		tmp.normalize();

		//System.out.println("tmp = " + tmp.toAbsolutePath());

		return tmp.toFile().delete();
	}

	public boolean checkRename(String path) throws IOException {

		Path tmp = this.currentDirectory.resolve(path);
		tmp.normalize();

		//System.out.println("tmp = " + tmp.toAbsolutePath());

		return tmp.toFile().exists();
	}

	public long getSize(String path) {

		return Paths.get(path).toFile().length();
	}
	
	
	private boolean verifyCurrentDirectoryInsideBaseDirectory(String rep){
		Path tmp_path = this.currentDirectory.resolve(rep);
		tmp_path = tmp_path.normalize();
		if(tmp_path.startsWith(this.baseDirectory)){
			return true;
		}
		return false;
	}
	
	/**
	 * Permit you to move a file inside your baseDirectory
	 * @param oldPath The path to the old file relative path to your currentDirectory
	 * @param newPath The path where the old file will be move it's relative path to your currentDirectory
	 * @return True if success else false
	 */
	public boolean moveFile(String oldPath, String newPath){
		//Verify if you have the right to access to the directory
		if(verifyCurrentDirectoryInsideBaseDirectory(oldPath) && verifyCurrentDirectoryInsideBaseDirectory(newPath)){
			Path oldNamePath = this.currentDirectory.resolve(oldPath);
			Path newNamePath = this.currentDirectory.resolve(newPath);
			try {
				Files.move(oldNamePath, newNamePath);
				return true;
			} catch (IOException e) {
				return false;
			}
		}
		return false;
	}
	
	public static void main( String[] args )
	{
		DirectoryManager tmp = new DirectoryManager("/home/m1/soleillet/Documents");
		System.out.println(tmp.changeWorkingDirectory("CAR"));
		try {
			System.out.println(tmp.listCurrentLocation(""));
			
			System.out.println(tmp.changeWorkingDirectory(".."));
			System.out.println(tmp.changeWorkingDirectory("exemples"));
			System.out.println(tmp.printWorkingDirectory());
			System.out.println(tmp.listCurrentLocation(""));

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void reset() {
		this.currentDirectory = this.baseDirectory;
		
	}

}


