package generics.v2;
import java.util.*;

import generics.v2.goods.*;

public class ElectricVehicleRenterManager  {

	private Renter<Vehicle> myRenter;
	
	public ElectricVehicleRenterManager() {
		this.myRenter = new Renter<Vehicle>();
	}
	
	public <T extends Vehicle & Electric> void addVehicles(List<T> goods) {
		this.myRenter.addList(goods);
	}
}
