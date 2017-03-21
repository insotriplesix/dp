public class BeerSong {
	public static void main(String[] args) {
		boolean isEnd = false;
		int bottles = 10;
		while (!isEnd) {
			if (bottles != 1) {
				System.out.println(bottles + " bottles of beer on the wall");
				System.out.println(bottles + " bottles of beer!");
				System.out.println("Take one down, pass it around");
				bottles--;
				System.out.println(bottles + " bottles of beer on the wall");
				System.out.println("");
			} else {
				System.out.println(bottles + " bottle of beer on the wall");
				System.out.println(bottles + " bottle of beer!");
				System.out.println("Take one down, pass it around");
				bottles--;
				System.out.println(bottles + " bottles of beer on the wall");
				isEnd = true;
			}
		}
	}
}
