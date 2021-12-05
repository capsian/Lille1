package generics.v1;

import java.util.Random;

/**
 * a subtype of Renter using the same parameter type
 * @param <T> the type of the rented goods
 */
public class SpecificRenter<T> extends Renter<T> {

	protected static final Random ALEA = new Random();
	
	public SpecificRenter() {
	}

	
	/**
	 * @see generics.v1.Renter#add(java.lang.Object)
	 */
	public void add(T good) {
		System.out.println("do something more");
		super.add(good);
	}
	/** returns a randomly chosen available good to rent
	 * @return  a randomly chosen available good to rent
	 */
	public T randomGood() {
		return this.available.get(ALEA.nextInt(this.available.size()));			
	}
}
