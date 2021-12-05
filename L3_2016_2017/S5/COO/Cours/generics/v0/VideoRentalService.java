package generics.v0;

import java.util.*;

import generics.v0.goods.Video;
import generics.v0.User;

public class VideoRentalService {

	private List<Video> available;
	private List<Video> busy;
	
	public VideoRentalService() {
		this.available = new ArrayList<Video>();
		this.busy = new ArrayList<Video>();
	}

	public void add(Video Video) {
		this.available.add(Video);
	}
	
	public Video rentTo(User u) {
		Video rentedVideo = this.available.get(0);
		this.busy.add(rentedVideo);
		return rentedVideo;
	}
	
}
