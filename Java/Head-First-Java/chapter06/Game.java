
import java.util.*;

public class Game {
	
	private GameHelper helper = new GameHelper();
	private ArrayList<Site> sites = new ArrayList<Site>();
	private int numOfGuesses = 0;
	
	public static void main(String[] args) {
		Game game = new Game();
		game.setUpGame();
		game.startPlaying();
		
	}
	
	private void setUpGame() {
		// Create few sites
		Site one = new Site();
		one.setName("joma.com");
		Site two = new Site();
		two.setName("cocks.org");
		Site three = new Site();
		three.setName("sisek.net");
		
		// Add them to the array list
		sites.add(one);
		sites.add(two);
		sites.add(three);
		
		// Dump info
		System.out.println("You need to blow three sites: ");
		System.out.println("joma.com, cocks.org, sisek.net");
		
		// Place the sites to random positions
		for (Site s : sites) {
			ArrayList<String> loc = helper.placeSite(3);
			s.setLocationCells(loc);
		}
	}
	
	private void startPlaying() {
		// Do while list not empty
		while (!sites.isEmpty()) {
			String userGuess = helper.getUserInput("Input cell for strike: ");
			checkUserGuess(userGuess);
		}
		// Dump final statistics
		finishGame();
	}
	
	private void checkUserGuess(String userGuess) {
		// Increase attempts
		numOfGuesses++;
		
		// Default value
		String result = "Missed that.";
		
		for (Site s : sites) {
			result = s.checkYourself(userGuess);
			
			if (result.equals("Got it!")) break;
			if (result.equals("Take it down.")) {
				sites.remove(s);
				break;
			}
		}
		
		// Dump result
		System.out.println(result);
	}
	
	private void finishGame() {
		System.out.println("Job is done.");
		System.out.println("It takes " + numOfGuesses + " attempts.");
		if (numOfGuesses <= 18)
			System.out.println("Nice result, sweety!");
		else
			System.out.println("Nice result, sweety! (no)");
	}
	
}
