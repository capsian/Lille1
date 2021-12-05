package generics.v1.goods;

import generics.v1.User;

public class Room {
	
	public static int MINIMAL_AGE = 18;
	
	public Room() {
	}

	public boolean canBeRentBy(User user) {
		return user.getAge() >= MINIMAL_AGE;
	}
}
