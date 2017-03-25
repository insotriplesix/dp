
public class SimpleDotCom {

	int[] locationCells;
	int numOfHits = 0;
	
	public void setLocationCells(int[] locs) {
		locationCells = locs;
	}
	
	public String checkYourself(String stringGuess) {
		int guess = Integer.parseInt(stringGuess);
		String result = "Missed that.";
		
		for (int cell : locationCells) {
			if (guess == cell) {
				if (++numOfHits == locationCells.length) {
					result = "Explode the site.";
					break;
				} else
					result = "Got it!";
			}
		}
		
		System.out.println(result);
		
		return result;
	}
}