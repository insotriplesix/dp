public class PhraseOMatic {
	public static void main(String[] args) {
		String[] list1 = { "huy", "pizda", "jopa" };
		String[] list2 = { "sosok", "hrush", "posos" };
		String[] list3 = { "pidor", "loh", "perdak"};
		
		int len1 = list1.length;
		int len2 = list2.length;
		int len3 = list3.length;
		
		int rand1 = (int) (Math.random() * len1);
		int rand2 = (int) (Math.random() * len2);
		int rand3 = (int) (Math.random() * len3);
		
		String phrase = list1[rand1] + " " + list2[rand2] + " " + list3[rand3];
		System.out.println("All you need is: " + phrase);
	}
}