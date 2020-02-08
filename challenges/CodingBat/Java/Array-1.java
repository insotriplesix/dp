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


/*
Start with 2 int arrays, a and b, of any length. Return how many of the arrays have 1 as their
first element.
*/

public int start1(int[] a, int[] b) {
  int cnt = 0;

  for (int i = 0; i < a.length; i++) {
    if (a[0] == 1) {
      cnt++;
    }
    break;
  }

  for (int i = 0; i < b.length; i++) {
    if (b[0] == 1) {
      cnt++;
    }
    break;
  }

  return cnt;
}


/*
Start with 2 int arrays, a and b, each length 2. Consider the sum of the values in each array.
Return the array which has the largest sum. In event of a tie, return a.
*/

public int[] biggerTwo(int[] a, int[] b) {
  int win = 0;
  int sumA = 0, sumB = 0;

  for (int i = 0; i < a.length; i++)
    sumA += a[i];

  for (int i = 0; i < b.length; i++)
    sumB += b[i];

  win = sumA - sumB;

  return win >= 0 ? a : b;
}


/*
Given an array of ints of even length, return a new array length 2 containing the middle two elements
from the original array. The original array will be length 2 or more.
*/

public int[] makeMiddle(int[] nums) {
  int[] result = {
    nums[nums.length / 2 - 1],
    nums[nums.length / 2]
  };
  return result;
}


/*
Given 2 int arrays, each length 2, return a new array length 4 containing all their elements.
*/

public int[] plusTwo(int[] a, int[] b) {
  int[] result = new int[a.length + b.length];
  int i, j;

  for (i = 0; i < a.length; i++)
    result[i] = a[i];

  for (j = 0; j < b.length; j++, i++)
    result[i] = b[j];

  return result;
}


/*
Given an array of ints, swap the first and last elements in the array. Return the modified array.
The array length will be at least 1.
*/

public int[] swapEnds(int[] nums) {
  int tmp = nums[0];
  nums[0] = nums[nums.length - 1];
  nums[nums.length - 1] = tmp;
  return nums;
}


/*
Given an array of ints of odd length, return a new array length 3 containing the elements from the
middle of the array. The array length will be at least 3.
*/

public int[] midThree(int[] nums) {
  int[] result = {
    nums[nums.length / 2 - 1],
    nums[nums.length / 2],
    nums[nums.length / 2 + 1]
  };
  return result;
}


/*
Given an array of ints of odd length, look at the first, last, and middle values in the array and
return the largest. The array length will be a least 1.
*/

public int maxTriple(int[] nums) {
  int first = nums[0];
  int mid = nums[nums.length / 2];
  int last = nums[nums.length - 1];

  return first > mid ? (
    first > last ? first : last
  ) : (last > mid ? last : mid);
}


/*
Given an int array of any length, return a new array of its first 2 elements. If the array is smaller
than length 2, use whatever elements are present.
*/

public int[] frontPiece(int[] nums) {
  int len = nums.length > 2 ? 2 : nums.length;
  int[] result = new int[len];

  for (int i = 0; i < len; i++)
    result[i] = nums[i];

  return result;
}


/*
We'll say that a 1 immediately followed by a 3 in an array is an "unlucky" 1. Return true if the
given array contains an unlucky 1 in the first 2 or last 2 positions in the array.
*/

public boolean unlucky1(int[] nums) {
  if (nums.length < 2) return false;

  if (nums[0] == 1 && nums[1] == 3
    || nums[1] == 1 && nums[2] == 3
    || nums[nums.length - 2] == 1 && nums[nums.length - 1] == 3)
    return true;

  return false;
}


/*
Given 2 int arrays, a and b, return a new array length 2 containing, as much as will fit, the
elements from a followed by the elements from b. The arrays may be any length, including 0, but
there will be 2 or more elements available between the 2 arrays.
*/

public int[] make2(int[] a, int[] b) {
  int maxLen = 2;
  int cnt = 0;

  int[] result = new int[maxLen];

  for (int i = 0; i < a.length; i++) {
    if (cnt == maxLen)
      return result;

    result[cnt++] = a[i];
  }

  for (int j = 0; j < b.length; j++) {
    if (cnt == maxLen)
      return result;

    result[cnt++] = b[j];
  }

  return result;
}


/*
Given 2 int arrays, a and b, of any length, return a new array with the first element of each array.
If either array is length 0, ignore that array.
*/

public int[] front11(int[] a, int[] b) {
  int cnt = 0;
  int len = 0;

  if (a.length > 0)
    len++;

  if (b.length > 0)
    len++;

  int[] result = new int[len];

  if (a.length != 0)
    result[cnt++] = a[0];

  if (b.length != 0)
    result[cnt++] = b[0];

  return result;
}

