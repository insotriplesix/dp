
import java.util.*;

public class Site {
	
	private ArrayList<String> locationCells;
	private String name;
	
	public void setLocationCells(ArrayList<String> loc) {
		locationCells = loc;
	}
	
	public void setName(String n) {
		name = n;
	}
	
	public String checkYourself(String userInput) {
		String result = "Missed that.";
		
		int idx = locationCells.indexOf(userInput);
		
		if (idx >= 0) {
			locationCells.remove(idx);
			
			if (locationCells.isEmpty()) {
				result = "Take it down.";
				System.out.println(name + " is done.");
			} else {
				result = "Got it!";
			}
		}
		
		return result;
	}
	
}