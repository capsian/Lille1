package generics.v2.goods;

import generics.v2.User;

public class Room implements Rentable {

	public Room() {
	}
	public boolean canBeRentBy(User u) {
		return true;
	}
}
