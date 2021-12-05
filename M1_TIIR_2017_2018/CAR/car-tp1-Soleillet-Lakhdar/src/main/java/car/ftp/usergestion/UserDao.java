package car.ftp.usergestion;

import java.util.HashMap;
import java.util.Map;

public class UserDao {
	
	
	public static UserDao userList = new UserDao();
	private Map<String, User> users;
	private UserDao() {
		this.users = new HashMap<>();
	}
	
	public void addUser(String username,String directory){
		this.users.put(username,new User(username,directory)); 
	}
	public void addUser(String username,String password,String directory){
		this.users.put(username,new User(username,password,directory)); 
	}
	public void removeUser(String username){
		this.users.remove(username);
	}
	/** 
	 * Permit you to know if an user is in the db
	 * @param username : The username to check if he is known
	 * @return True : if the user is known else False
	 */
	public boolean isValidUserName(String username){
		return this.users.containsKey(username);
	}
	/**
	 * Init the users into the DB
	 */
	public static void init(){
		UserDao.userList.addUser("nopass","/tmp/nopass");
		UserDao.userList.addUser("pass", "pass","/tmp/pass");
		UserDao.userList.addUser("toto", "toto","/tmp/toto");
	}

	public User getUser(String username) {
		return this.users.get(username);
	}

}
