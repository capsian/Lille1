package generics.v2;

import java.util.ArrayList;
import java.util.List;

import generics.v2.goods.Rentable;

public class RentableDisplayer<T extends Rentable> {

	public void displayRentable(Renter<T> renter, User user) {
		List<T> selected = this.selectRentableGoods(renter, user);
		
	}

	private List<T> selectRentableGoods(Renter<T> renter, User user) {
		List<T> rentable = new ArrayList<T>();
		for(T good : renter.availableGoods()) {
			if (good.canBeRentBy(user)) {
				rentable.add(good);
			}
		}
		return rentable;
	}
	
	
	
}
