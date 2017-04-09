class A {
	int ivar = 7;
	
	void m1() {
		System.out.print("A`s m1, ");
	}
	
	void m2() {
		System.out.print("A`s m2, ");
	}
	
	void m3() {
		System.out.print("A`s m3, ");
	}
}

class B extends A{
	void m1() {
		System.out.print("B`s m1, ");
	}
}

class C extends B{
	void m3() {
		System.out.print("C`s m1, " + (ivar + 6));
	}
}

public class Mixed2 {
	public static void main(String [] args) {
		A a = new A();
		B b = new B();
		C c = new C();
		A a2 = new C();
		
		b.m1();
		c.m2();
		a.m3();
		System.out.println();
		
		c.m1();
		c.m2();
		c.m3();
		System.out.println();
		
		a.m1();
		b.m2();
		c.m3();
		System.out.println();
		
		a2.m1();
		a2.m2();
		a2.m3();
		System.out.println();
	}
}