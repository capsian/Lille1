package generics.v2;

import java.util.*;

import generics.v2.goods.*;

public class Main3 {

	public static void main(String[] args) {
		User user = new User();

		Renter<Car> carAgency = new Renter<Car>();
		carAgency.rentTo(user);

		//
		List<Car> cars = new ArrayList<Car>();
		cars.add(new Car());
		cars.add(new Car());
		carAgency.addList(cars);

		//
		Renter<Vehicle> vehicleAgency = new Renter<Vehicle>();
		carAgency.transferAllGoodsTo(vehicleAgency);

		//
		
		cars = new ArrayList<Car>();
		cars.add(new Car());
		cars.add(new Car());
		Renter<Car> otherAgency = new Renter<Car>();
		carAgency.addGoodsAndTransferDuplicate(cars, otherAgency);
		
		List<ElectricCar> eCars = new ArrayList<>();
		carAgency.addGoodsAndTransferDuplicate(eCars, vehicleAgency);
		
		
	}
}
