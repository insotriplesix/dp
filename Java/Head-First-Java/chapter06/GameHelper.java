
import java.io.*;
import java.util.*;

public class GameHelper {
	
	private static final String alphabet = "abcdefg";
	private int gridLength = 7;
	private int gridSize = 49;
	
	private int[] grid = new int[gridSize];
	private int sitesCounter = 0;
	
	public String getUserInput(String prompt) {
		String inputLine = null;
		
		System.out.print(prompt + " ");
		
		try {
			BufferedReader is = new BufferedReader(
			new InputStreamReader(System.in));
			inputLine = is.readLine();
			
			if (inputLine.length() == 0) return null;
		} catch (IOException e) {
			System.out.println("IOException: " + e);
		}
		
		return inputLine;
	}
	
	public ArrayList<String> placeSite(int numSites) {
		ArrayList<String> alphaCells = new ArrayList<String>();
		
		// Keeps coords in 'letter + number' format (e.g. f6)
		String[] alphaCoords = new String[numSites];
		
		// For concatenation stuff
		String temp = null;
		
		// Coordinates of the current site
		int[] coords = new int[numSites];
		
		int attempts = 0;
		
		// For locating
		boolean success = false;
		
		// Primary location
		int location = 0;
		
		// Starts with 'n' site
		sitesCounter++;
		
		// Horizontal | vertical locating
		int incr = 1;
		if ((sitesCounter % 2) == 1) incr = gridLength;
		
		// Routine
		while (!success & attempts++ < 200) {
			// Get random point
			location = (int) (Math.random() * gridSize);
			
			// Position for site
			int x = 0;
			
			// Try to find next position
			success = true;
			while (success && x < numSites) {
				// If it's not used 
				if (grid[location] == 0) {
					// Use it!
					coords[x++] = location;
					
					// Check if exceed the bounds 
					location += incr;
					if ((location >= gridSize) || (x > 0 && (location % gridLength == 0)))
						success = false;
				} else {
					// Point already using
					success = false;
				}
			}
		}
		
		// Now convert this to the alpha coords
		int x = 0;
		int row = 0;
		int col = 0;
		
		while (x < numSites) {
			// Mark the cells as used
			grid[coords[x]] = 1;
			
			// Get row values
			row = (int) (coords[x] / gridLength);
			
			// Get column value
			col = coords[x] % gridLength;
			
			// Convert it to the string
			temp = String.valueOf(alphabet.charAt(col));
			
			// Add it to the array list
			alphaCells.add(temp.concat(Integer.toString(row)));
			x++;
		}
		
		return alphaCells;
	}
	
}