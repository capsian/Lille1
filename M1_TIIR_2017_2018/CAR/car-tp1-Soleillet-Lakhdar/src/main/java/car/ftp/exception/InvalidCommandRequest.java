package car.ftp.exception;

import java.io.IOException;

public class InvalidCommandRequest extends IOException {
	
	public InvalidCommandRequest(String message) {
		super(message);
	}

}
