package generics.v2;

import generics.v2.Renter;
import generics.v2.goods.*;

public class Main {


	public static void main(String[] args) {
		User user = new User();
		
		Renter<Car> carAgency = new Renter<Car>();
		carAgency.rentTo(user);
	
		Hotel hotel = new Hotel();
		hotel.rentTo(user);
				
		Car someCar = user.rentSomething(carAgency);
		someCar.canBeRentBy(user);
		
		
		Room someRoom = hotel.rentTo(user);
		someRoom.canBeRentBy(user);

		// ???TYPE? anotherCar = carAgency.rentTo(user);
		Renter<?> r = carAgency;
		Rentable anotherCar = r.rentTo(user);
		anotherCar.canBeRentBy(user);

	}

}
