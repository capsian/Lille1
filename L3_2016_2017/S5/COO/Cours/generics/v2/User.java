package generics.v2;

import java.util.HashMap;
import java.util.Map;

import generics.v2.goods.Rentable;

public class User {
	
	private Map<Rentable, Renter<? extends Rentable>> rentedGoods;

	
	public User() {
		this.rentedGoods = new HashMap<Rentable,Renter<? extends Rentable>>();
	}

	public <T extends Rentable> T rentSomething(Renter<T> renter) {		
		T rented = renter.rentTo(this);
		this.storeRented(renter, rented);
		return rented;
	}
	
	protected void storeRented(Renter<? extends Rentable> renter, Rentable rented) {
		this.rentedGoods.put(rented, renter);
	}
	
	
	@SuppressWarnings("unchecked")
	public <T extends Rentable> void returnRentedGood(T rented) {
		Renter<T> renter  = (Renter<T>) this.rentedGoods.get(rented);
		renter.rentalFinished(rented);
	}
}

