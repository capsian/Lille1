package generics.v1;

import java.util.HashMap;
import java.util.Map;

public class User {
	
	private Map<Object, Renter<?>> rentedGoods;

	
	public User() {
		this.rentedGoods = new HashMap<Object,Renter<?>>();
	}

	/** rents some object from given renter
	 * @param renter the renter
	 * @return the rented object
	 */
	public <T> T rentSomething(Renter<T> renter) {		
		T rented = renter.rentTo(this);
		this.storeRented(renter, rented);
		return rented;
	}
	
	/** stores the renter that has rent the good
	 * @param renter the renter tht rents the good
	 * @param rented the good rented by the renter
	 */
	protected void storeRented(Renter<?> renter, Object rented) {
		this.rentedGoods.put(rented, renter);
	}
	
	@SuppressWarnings("unchecked")
	public <T> Renter<T> getRenter(T rented) {
		return (Renter<T>) this.rentedGoods.get(rented);
	}
	
	public <T> void returnRentedGood(T rented) {
		Renter<T> renter  = this.getRenter(rented);
		this.rentedGoods.remove(rented);
		renter.rentalFinished(rented);
	}
	
	public boolean hasDrivingLicence(){
		return true;
	}
	public int getAge() {
		return 20;  
	}
}

