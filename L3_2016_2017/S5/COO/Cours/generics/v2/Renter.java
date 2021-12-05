package generics.v2;

import java.util.*;

import generics.v2.User;
import generics.v2.goods.Rentable;

public class Renter<T extends Rentable> {

	private List<T> available;
	private List<T> busy;

	public Renter() {
		this.available = new ArrayList<T>();
		this.busy = new LinkedList<T>();
	}

	public void add(T good) {
		this.available.add(good);
	}

	/** adds a list of rentable goods to this renter
	 * @param goods the list of new rentable goods
	 */
	public void addList(List<? extends T> goods) {
		for (T good : goods) {
			this.add(good);
		}
	}
	
	/** this renter transfers all its available goods to another renter 
	 * @param other the renter that receives the available goods
	 */
	public void transferAllGoodsTo(Renter<? super T> other) {
		other.addList(this.available);
		this.available.clear();
	}
	

	
	/** add list of new goods to this renter, duplicate good are transfered to given alternate renter
	 * @param goods the list of goods to add 
	 * @param other the renter that receives the duplicate goods
	 */
	public void addGoodsAndTransferDuplicate(List<? extends T> goods, Renter<? super T> other) {
		for (T good : goods) {
			if (this.available.contains(good) || this.busy.contains(good)) {
				this.add(good);
			} else {
				other.add(good);
			}
		}
	}
	

	
	
	/** A user rents one of the good of this renter.  
	 * @param u the user that wants to rent 
	 * @return the rented good
	 */
	public T rentTo(User u) {
		T rented = this.available.get(0);
		if (rented.canBeRentBy(u)) {
			this.busy.add(rented);
			this.available.remove(0);
			return rented;
		}
		else {
			return null;
		}
	}

	public void rentalFinished(T rented) {
		this.busy.remove(rented);
		this.available.add(rented);
	}

	
	
	
//	public void displayRentable(User user) {
//		List<T> selected = this.selectRentableGoods(user);
//		
//	}
//
//	public List<T> selectRentableGoods(User user) {
//		List<T> rentable = new ArrayList<T>();
//		for(T good : this.available) {
//			if (good.canBeRentBy(user)) {
//				rentable.add(good);
//			}
//		}
//		return rentable;
//	}
//	
//	public void display(List<T> goods) {
//		for(T good : goods) {
//			System.out.println(good);
//		}
//	}
	

	
	public List<T> availableGoods() {
		return this.available;
	}
}
