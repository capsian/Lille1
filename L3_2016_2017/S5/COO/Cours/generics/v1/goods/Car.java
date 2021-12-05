package generics.v1.goods;

import generics.v1.User;

public class Car {

	private String brand;

	public Car() {
	}

	public boolean canBeRentBy(User user) {
		return user.hasDrivingLicence();
	}
}
