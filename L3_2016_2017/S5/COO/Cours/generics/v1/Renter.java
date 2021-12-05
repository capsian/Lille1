package generics.v1;

import java.util.*;

/**
 * This class represents rental services. They rent goods to users.
 * @param <T> the type of the rented goods
 */
public class Renter<T> {

	/** The goods available for rental */
	protected List<T> available;
	/** The rented goods */
	protected List<T> busy;
	
	public Renter() {
		this.available = new ArrayList<T>();
		this.busy = new LinkedList<T>();
	}

	/** adds a new rentable good to this renter
	 * @param good the new rentable good 
	 */
	public void add(T good) {
		this.available.add(good);
	}
	
	/** A user rents one of the good of this renter
	 * @param u the user that wants to rent 
	 * @return the rented good
	 */
	public T rentTo(User u) {
		T rented = this.available.get(0);
		this.busy.add(rented);
		this.available.remove(0);
		return rented;
	}

	/** The given good is returned when rental has finished.
	 * @param rentedGood the returned good
	 */
	public void rentalFinished(T rentedGood) {
		this.busy.remove(rentedGood);
		this.available.add(rentedGood);		
	}
	
}
