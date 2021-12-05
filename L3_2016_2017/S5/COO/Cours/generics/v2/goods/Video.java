package generics.v2.goods;

import generics.v2.User;

public class Video implements Rentable {

	public Video() {
	}
	public boolean canBeRentBy(User u) {
		return true;
	}
}
