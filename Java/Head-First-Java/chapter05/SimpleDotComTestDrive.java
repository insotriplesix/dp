
public class SimpleDotComTestDrive {
	
	public static void main(String[] args) {
		
		float f = 3.14f;
		int x = (int) f;
		System.out.println(f + " " + x);
		
		int numOfGuesses = 0;
		
		GameHelper helper = new GameHelper();

		SimpleDotCom dot = new SimpleDotCom();

		int r = (int) (Math.random() * 5);
		int[] locations = { r, r+1, r+2 };
		dot.setLocationCells(locations);
		
		while (true) {
			String userGuess = helper.getUserInput("Input cell to bomb: ");
			String result = dot.checkYourself(userGuess);
			numOfGuesses++;
			
			if (result.equals("Explode the site.")) {
				System.out.println("Takes " +  numOfGuesses + " attempt(s).");
				break;
			}	
		}
	}
	
}
