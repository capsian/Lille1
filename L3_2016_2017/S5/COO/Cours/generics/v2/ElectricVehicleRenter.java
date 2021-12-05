package generics.v2;

import generics.v2.goods.*;


public class ElectricVehicleRenter<T extends Vehicle & Electric> extends Renter<T> {
	
}
