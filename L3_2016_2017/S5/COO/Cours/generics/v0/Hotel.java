package generics.v0;

import java.util.*;

import generics.v0.goods.Room;
import generics.v0.User;

public class Hotel { // == RoomRenter

	private List<Room> available;
	private List<Room> busy;
	
	public Hotel() {
		this.available = new ArrayList<Room>();
		this.busy = new ArrayList<Room>();
	}

	public void add(Room Room) {
		this.available.add(Room);
	}
	
	public Room rentTo(User u) {
		Room rentedRoom = this.available.get(0);
		this.busy.add(rentedRoom);
		return rentedRoom;
	}
	
	public void rentalFinished(Room rentedRoom) {
		this.busy.remove(rentedRoom);
		this.available.add(rentedRoom);		
	}
	
}
