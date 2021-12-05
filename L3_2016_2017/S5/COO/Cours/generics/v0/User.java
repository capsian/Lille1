package generics.v0;

import java.util.*;

import generics.v0.goods.*;

public class User {
	
	private Map<Car, CarRentalAgency> rentedCars;
	
	public Car rentSomeCar(CarRentalAgency carAgency) {		
		Car rented = carAgency.rentTo(this);
		this.rentedCars.put(rented,carAgency);		
		return rented;
	}

	public void returnCar(Car rentedCar) {
		CarRentalAgency renter  = this.rentedCars.get(rentedCar);
		renter.rentalFinished(rentedCar);
	}

	
	private Map<Room, Hotel> rentedRooms;

	public Room rentSomeRoom(Hotel hotel) {		
		Room rented = hotel.rentTo(this);
		this.rentedRooms.put(rented,hotel);
		return rented;
	}
	public void returnRoom(Room rentedRoom) {
		Hotel renter  = this.rentedRooms.get(rentedRoom);
		renter.rentalFinished(rentedRoom);
	}
	
}

