package generics.v2;

import java.util.*;

import generics.v2.goods.*;

public class Main4 {

	public static void main(String[] args) {
		User user = new User();

		ElectricVehicleRenter<ElectricCar> eCarRenter = new ElectricVehicleRenter<ElectricCar>();
//		ElectricVehicleRenter<Car> eRenter = new ElectricVehicleRenter<Car>();		

		eCarRenter.add(new ElectricCar());
//		eCarRenter.add(new Car());

		
		List<ElectricScooter> scooters = new ArrayList<>();
		List<ElectricCar> eCars = new ArrayList<>();
		List<Car> cars = new ArrayList<Car>();
		
				
//		eCarRenter.addList(scooters);
//		eCarRenter.addList(eCars);
//		eCarRenter.addList(cars);

		
//		Vehicle good = eCarRenter.rentTo(user);
//		Electric good2 = eCarRenter.rentTo(user);		
// 		ElectricCar good3 = eCarRenter.rentTo(user);
// 		Car good3bis = eCarRenter.rentTo(user);
//		Rentable good4 = eCarRenter.rentTo(user);		
//		
		
		ElectricVehicleRenterManager erm = new ElectricVehicleRenterManager();	
//		erm.addVehicles(scooters);
//		erm.addVehicles(eCars);
//		erm.addVehicles(cars);
//		
	}
}
