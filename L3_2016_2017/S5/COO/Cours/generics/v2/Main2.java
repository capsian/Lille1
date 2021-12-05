package generics.v2;

import java.util.*;

import generics.v2.goods.*;

public class Main2 {

	public static void main(String[] args) {
		User user = new User();

		Renter<Vehicle> carAgency = new Renter<Vehicle>();
		carAgency.rentTo(user);

		//
		List<Vehicle> vehicles = new ArrayList<Vehicle>();
		vehicles.add(new Vehicle());
		vehicles.add(new Car());

		carAgency.addList(vehicles);

		//
		List<Car> cars = new ArrayList<Car>();
		vehicles.add(new Car());

		carAgency.addList(cars);

			
	}
}
