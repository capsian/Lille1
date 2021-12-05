package generics.v0;

import java.util.*;

import generics.v0.goods.Car;
import generics.v0.User;

public class CarRentalAgency {

	private List<Car> available;
	private List<Car> busy;
	
	public CarRentalAgency() {
		this.available = new ArrayList<Car>();
		this.busy = new ArrayList<Car>();
	}

	public void add(Car car) {
		this.available.add(car);
	}
	
	public Car rentTo(User u) {
		Car rentedCar = this.available.get(0);
		this.busy.add(rentedCar);
		return rentedCar;
	}

	public void rentalFinished(Car rentedCar) {
		this.busy.remove(rentedCar);
		this.available.add(rentedCar);		
	}
}
