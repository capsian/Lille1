package generics.v1;

import generics.v1.goods.*;

public class Main {


	public static void main(String[] args) {
		User user = new User();
		
		Renter<Car> carAgency = new Renter<Car>();
		carAgency.rentTo(user);
	
		Hotel hotel = new Hotel();
		hotel.rentTo(user);
				
		// typage ???
		// ?TYPE? someRoom = hotel.rentTo(user);
		Room someRoom = hotel.rentTo(user);
		someRoom.canBeRentBy(user);
		
		user.storeRented(hotel,someRoom);
		
		// ?TYPE? someCar = user.rentSomething(carAgency);
		Car someCar = user.rentSomething(carAgency);
		someCar.canBeRentBy(user);
		
		
		// ?TYPE? anotherCar = carAgency.rentTo(user);
		Renter<?> anonymous = carAgency;
		Object anotherCar = anonymous.rentTo(user);
		((Car) anotherCar).canBeRentBy(user);


	
	}

}
