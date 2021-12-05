package generics.v2.goods;

import generics.v2.User;

public class Vehicle implements Rentable {

	public Vehicle() {
	}

	public boolean canBeRentBy(User u) {
		return true;
	}

	
	// ne pas oublier pour la hashMap : (mais implémentatiojn à faire) 
	public int hashCode() {
		return 0;
	}
	public boolean equals(Object o) {
		return this ==o;
	}
	
}
