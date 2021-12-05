package car.ftp.usergestion;

import car.ftp.directory.DirectoryManager;

public class User {
	private String username;
	private String password;
	private DirectoryManager userDirectory;
	
	public User(String username,String directory) {
		this.username = username;
		this.userDirectory = new DirectoryManager(directory);
		this.password = null;
	} 
	
	public User(String username, String password,String directory) {
		this.username = username;
		this.password = password;
		this.userDirectory = new DirectoryManager(directory);
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public boolean isValidPassword(String password) {
		return this.password.equals(password);
	}

	public boolean needAPassword() {
		return this.password != null;
	}

	public boolean authenticate(String password) {
		return this.password.equals(password);
	}
	
	public DirectoryManager getDirectoryManager() {
		return this.userDirectory;
	}

}
