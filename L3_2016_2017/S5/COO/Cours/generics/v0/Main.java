package generics.v0;

import generics.v0.User;
import generics.v0.goods.Car;

public class Main {

	public static void main(String[] args) {
		User user = new User();
		
		CarRentalAgency carAgency = new CarRentalAgency();
		Car rentedCar = carAgency.rentTo(user);
		carAgency.rentalFinished(rentedCar);
	
		Hotel hotel = new Hotel();
		hotel.rentTo(user);
				
	}

}
