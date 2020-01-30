/*
Given an array of ints, return true if 6 appears as either the first or last element in the array.
The array will be length 1 or more.
*/

public boolean firstLast6(int[] nums) {
  int len = nums.length;
  return nums[0] == 6 || nums[len - 1] == 6;
}


/*
Given an array of ints, return true if the array is length 1 or more, and the first element and the
last element are equal.
*/

public boolean sameFirstLast(int[] nums) {
  return nums.length >= 1 && nums[0] == nums[nums.length-1];
}


/*
Return an int array length 3 containing the first 3 digits of pi, {3, 1, 4}.
*/

public int[] makePi() {
  return new int[] { 3, 1, 4 };
}


/*
Given 2 arrays of ints, a and b, return true if they have the same first element or they have the
same last element. Both arrays will be length 1 or more.
*/

public boolean commonEnd(int[] a, int[] b) {
  return a[0] == b[0] || a[a.length - 1] == b[b.length - 1];
}


/*
Given an array of ints length 3, return the sum of all the elements.
*/

public int sum3(int[] nums) {
  int sum = 0;
  for (int i = 0; i < nums.length; i++) sum += nums[i];
  return sum;
}

/*
Given an array of ints length 3, return an array with the elements "rotated left" so {1, 2, 3}
yields {2, 3, 1}.
*/

public int[] rotateLeft3(int[] nums) {
  int[] result = new int[nums.length];
  for (int i = 0; i < nums.length - 1; i++)
    result[i] = nums[i + 1];
  result[nums.length - 1] = nums[0];
  return result;
}


