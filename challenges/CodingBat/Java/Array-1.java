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


/*
Given an array of ints length 3, return a new array with the elements in reverse order, so {1, 2, 3}
becomes {3, 2, 1}.
*/

public int[] reverse3(int[] nums) {
  int[] result = new int[nums.length];
  for (int j = 0, i = nums.length - 1; i >= 0; j++, i--)
    result[j] = nums[i];
  return result;
}


/*
Given an array of ints length 3, figure out which is larger, the first or last element in the array,
and set all the other elements to be that value. Return the changed array.
*/

public int[] maxEnd3(int[] nums) {
  int max = nums[0] > nums[nums.length - 1] ? nums[0] : nums[nums.length - 1];
  int[] result = new int[nums.length];
  for (int i = 0; i < nums.length; i++)
    result[i] = max;
  return result;
}


/*
Given an array of ints, return the sum of the first 2 elements in the array. If the array length is
less than 2, just sum up the elements that exist, returning 0 if the array is length 0.
*/

public int sum2(int[] nums) {
  int sum = 0;
  int len = nums.length >= 2 ? 2 : nums.length;
  for (int i = 0; i < len; i++)
    sum += nums[i];
  return sum;
}


/*
Given 2 int arrays, a and b, each length 3, return a new array length 2 containing their middle
elements.
*/

public int[] middleWay(int[] a, int[] b) {
  int[] result = { a[1], b[1] };
  return result;
}


/*
Given an array of ints, return a new array length 2 containing the first and last elements from the
original array. The original array will be length 1 or more.
*/

public int[] makeEnds(int[] nums) {
  int len = nums.length;
  int[] result = { nums[0], nums[len - 1] };
  return result;
}


/*
Given an int array length 2, return true if it contains a 2 or a 3.
*/

public boolean has23(int[] nums) {
  for (int i = 0; i < nums.length; i++)
    if (nums[i] == 2 || nums[i] == 3)
      return true;
  return false;
}


/*
Given an int array length 2, return true if it does not contain a 2 or 3.
*/

public boolean no23(int[] nums) {
  for (int i = 0; i < nums.length; i++)
    if (nums[i] == 2 || nums[i] == 3)
      return false;
  return true;
}


/*
Given an int array, return a new array with double the length where its last element is the same
as the original array, and all the other elements are 0. The original array will be length 1 or
more. Note: by default, a new int array contains all 0's.
*/

public int[] makeLast(int[] nums) {
  int[] result = new int[nums.length * 2];
  result[nums.length * 2 - 1] = nums[nums.length - 1];
  return result;
}


/*
Given an int array, return true if the array contains 2 twice, or 3 twice. The array will be
length 0, 1, or 2.
*/

public boolean double23(int[] nums) {
  int cnt2 = 0, cnt3 = 0;

  for (int i = 0; i < nums.length; i++) {
    if (nums[i] == 2)
      cnt2++;
    if (nums[i] == 3)
      cnt3++;
    if (cnt2 == 2 || cnt3 == 2)
      return true;
  }

  return false;
}


/*
Given an int array length 3, if there is a 2 in the array immediately followed by a 3, set the 3
element to 0. Return the changed array.
*/

public int[] fix23(int[] nums) {
  int prev = 0;

  for (int i = 1; i < nums.length; i++) {
    if (nums[i - 1] == 2 && nums[i] == 3)
      nums[i] = 0;
  }

  return nums;
}

