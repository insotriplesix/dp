/*
Given a string and a non-negative int n, return a larger string that is n copies of the original
string.
*/

public String stringTimes(String str, int n) {
  String res = "";

  for (int i = 0; i < n; i++)
    res += str;

  return res;
}


/*
Given a string and a non-negative int n, we'll say that the front of the string is the first 3
chars, or whatever is there if the string is less than length 3. Return n copies of the front;
*/

public String frontTimes(String str, int n) {
  int realN = str.length() >= 3 ? 3 : str.length();
  String res = "";

  for (int i = 0; i < n; i++)
    res += str.substring(0, realN);

  return res;
}


/*
Count the number of "xx" in the given string. We'll say that overlapping is allowed, so "xxx"
contains 2 "xx".
*/

int countXX(String str) {
  int len = str.length();

  if (len < 2)
    return 0;

  int result = 0;

  for (int i = 0; i < len - 1; i++)
    if (str.charAt(i) == 'x' && str.charAt(i + 1) == 'x')
      result++;

  return result;
}


/*
Given a string, return true if the first instance of "x" in the string is immediately followed by
another "x".
*/

boolean doubleX(String str) {
  int len = str.length();

  for (int i = 0; i < len; i++) {
    if (str.charAt(i) == 'x') {
      if (i + 1 < len && str.charAt(i + 1) == 'x')
        return true;
      else
        return false;
    }
  }

  return false;
}


/*
Given a string, return a new string made of every other char starting with the first, so "Hello"
yields "Hlo".
*/

public String stringBits(String str) {
  String result = "";

  for (int i = 0; i < str.length(); i += 2)
    result += Character.toString(str.charAt(i));

  return result;
}


/*
Given a non-empty string like "Code" return a string like "CCoCodCode".
*/

public String stringSplosion(String str) {
  String result = "";

  for (int i = 0; i < str.length(); i++)
    result += str.substring(0, i);

  return result + str;
}


/*
Given a string, return the count of the number of times that a substring length 2 appears in the
string and also as the last 2 chars of the string, so "hixxxhi" yields 1 (we won't count the end
substring).
*/

public int last2(String str) {
  int len = str.length();

  if (len <= 2)
    return 0;

  int result = 0;
  String last2 = str.substring(len - 2, len);

  for (int i = 0; i < len - 2; i++)
    if (str.substring(i, i+2).equals(last2))
      result++;

  return result;
}


/*
Given an array of ints, return the number of 9's in the array.
*/

public int arrayCount9(int[] nums) {
  int result = 0;
  for (int i = 0; i < nums.length; ++i)
      if (nums[i] == 9)
        result++;
  return result;
}


/*
Given an array of ints, return true if one of the first 4 elements in the array is a 9. The array
length may be less than 4.
*/

public boolean arrayFront9(int[] nums) {
  int realLen = nums.length < 4 ? nums.length : 4;
  for (int i = 0; i < realLen; i++)
    if (nums[i] == 9)
      return true;
  return false;
}


/*
Given an array of ints, return true if the sequence of numbers 1, 2, 3 appears in the array somewhere.
*/

public boolean array123(int[] nums) {
  int mark = 0;

  for (int i = 0; i < nums.length; i++) {
    switch(nums[i]) {
      case 1:
        if (mark == 0) mark = 1;
        break;
      case 2:
        if (mark == 1) mark = 2;
        break;
      case 3:
        if (mark == 2) mark = 3;
        break;
      default:
        mark = 0;
    }

    if (mark == 3) return true;
  }

  return false;
}


/*
Given 2 strings, a and b, return the number of the positions where they contain the same length 2
substring. So "xxcaazz" and "xxbaaz" yields 3, since the "xx", "aa", and "az" substrings appear in
the same place in both strings.
*/

public int stringMatch(String a, String b) {
  int len = a.length() < b.length() ? a.length() : b.length();
  int result = 0;

  for (int i = 0; i < len - 1; i++) {
    if (a.substring(i, i+2).equals(b.substring(i, i+2)))
      result++;
  }

  return result;
}


/*
Given a string, return a version where all the "x" have been removed. Except an "x" at the very
start or end should not be removed.
*/

public String stringX(String str) {
  int len = str.length();
  String result = "";

  for (int i = 0; i < len; i++)
    if (str.charAt(i) != 'x' || i == 0 || i == len - 1)
      result += Character.toString(str.charAt(i));

  return result;
}


/*
Given a string, return a string made of the chars at indexes 0,1, 4,5, 8,9 ... so "kittens" yields
"kien".
*/

public String altPairs(String str) {
  String result = "";
  int k = 0;
  boolean skip = false;

  for (int i = 0; i < str.length(); i++, k++) {
    if (k == 2) {
      skip = !skip;
      k = 0;
    }

    if (!skip) {
      result += Character.toString(str.charAt(i));
    }
  }

  return result;
}


/*
Suppose the string "yak" is unlucky. Given a string, return a version where all the "yak" are
removed, but the "a" can be any char. The "yak" strings will not overlap.
*/

public String stringYak(String str) {
  int yakLen = "yak".length();
  int strLen = str.length();
  String result = "";

  for (int i = 0; i < strLen; i++) {
    int len = strLen - i > yakLen ? yakLen : strLen - i;

    String sub = str.substring(i, i + len);

    if (sub.equals("yak")) {
      i += yakLen - 1;
    } else {
      result += Character.toString(str.charAt(i));
    }
  }

  return result;
}


/*
Given an array of ints, return the number of times that two 6's are next to each other in the
array. Also count instances where the second "6" is actually a 7.
*/

public int array667(int[] nums) {
  int mark = 0;
  int result = 0;

  for (int i = 0; i < nums.length; i++) {
    switch(nums[i]) {
      case 6:
        if (mark == 0) {
          mark = 1;
        } else if (mark == 1) {
          result++;
        }
        break;
      case 7:
        if (mark == 1) {
          mark = 0;
          result++;
        }
        break;
      default:
        mark = 0;
    }
  }

  return result;
}


/*
Given an array of ints, we'll say that a triple is a value appearing 3 times in a row in the
array. Return true if the array does not contain any triples.
*/

public boolean noTriples(int[] nums) {
  int count = 0;
  int cur = -1, prev = -1;

  for (int i = 0; i < nums.length; i++) {
    cur = nums[i];

    if (cur == prev)
      count++;
    else
      count = 0;

    if (count == 2)
      return false;

    prev = cur;
  }

  return true;
}


/*
Given an array of ints, return true if it contains a 2, 7, 1 pattern: a value, followed by the
value plus 5, followed by the value minus 1. Additionally the 271 counts even if the "1" differs
by 2 or less from the correct value.
*/

public boolean has271(int[] nums) {
  int mark = 0;

  for (int i = 0; i < nums.length - 2; i++) {
    if (nums[i] + 5 == nums[i + 1]
      && Math.abs(nums[i + 2] - (nums[i] - 1)) <= 2)
      return true;
  }

  return false;
}

