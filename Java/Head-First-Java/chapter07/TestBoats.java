public class TestBoats {
	public static void main(String [] args) {
		Boat b1 = new Boat();
		Sailboat b2 = new Sailboat ();
		Rowboat b3 = new Rowboat();
		
		b2.setLength(32);
		b1.move();
		b3.getLenght();
		b2.move();
	}
}

class Boat {
	private int length;
	
	public void setLength(int len) {
		length = len;
	}
	
	public int getLenght() {
		return length ;
	}
	
	public void move() {
		System.out.print("Drift Drift.. ");
	}
}

class Rowboat extends Sailboat {
	public void rowTheBoat() {
		System.out.print("C'mon, Natasha!");
	}
}

class Sailboat extends Boat {
	public void move() {
		System.out.print("Hoist the sails!");
	}
}
