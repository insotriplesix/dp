'''
We want to make a row of bricks that is goal inches long. We have a number of small bricks (1 inch each) and big bricks (5 inches each).
Return True if it is possible to make the goal by choosing from the given bricks. This is a little harder than it looks and can be done
without any loops.
'''
def make_bricks(small, big, goal):
  return False if big * 5 + small < goal or goal % 5 > small else True
  
  
'''
Given 3 int values, a b c, return their sum. However, if one of the values is the same as another of the values,
it does not count towards the sum.
'''
def lone_sum(a, b, c):
  if a != b and a != c:
    if b != c:
      return a + b + c
    else:
      return a
  elif a != b and b != c:
    return b
  elif a != c and b != c:
    return c
  else:
    return 0
  
  
'''
Given 3 int values, a b c, return their sum. However, if one of the values is 13 then it does not count towards the sum
and values to its right do not count. So for example, if b is 13, then both b and c do not count.
'''
def lucky_sum(a, b, c):
  nums = [a, b, c]
  total = 0

  for i in range(0, len(nums)):
    if (nums[i] == 13):
      break
    else:
      total += nums[i]

  return total
  
  
'''
Given 3 int values, a b c, return their sum. However, if any of the values is a teen -- in the range 13..19 inclusive --
then that value counts as 0, except 15 and 16 do not count as a teens. Write a separate helper "def fix_teen(n):"that takes
in an int value and returns that value fixed for the teen rule. In this way, you avoid repeating the teen code 3 times
(i.e. "decomposition"). Define the helper below and at the same indent level as the main no_teen_sum().
'''
def no_teen_sum(a, b, c):
  def fix_teen(n):
    return n if n not in range(13, 20) or n == 15 or n == 16 else 0

  return fix_teen(a) + fix_teen(b) + fix_teen(c)
  
  
'''
For this problem, we'll round an int value up to the next multiple of 10 if its rightmost digit is 5 or more, so 15 rounds up to 20.
Alternately, round down to the previous multiple of 10 if its rightmost digit is less than 5, so 12 rounds down to 10.
Given 3 ints, a b c, return the sum of their rounded values. To avoid code repetition, write a separate helper "def round10(num):"
and call it 3 times. Write the helper entirely below and at the same indent level as round_sum().
'''
def round_sum(a, b, c):
  def round10(num):
    return num - num % 10 if num % 10 < 5 else num - num % 10 + 10

  return round10(a) + round10(b) + round10(c)
  
  
'''
Given three ints, a b c, return True if one of b or c is "close" (differing from a by at most 1), while the other is "far",
differing from both other values by 2 or more. Note: abs(num) computes the absolute value of a number.
'''
def close_far(a, b, c):
  return True if (abs(a - b) < 2 and abs(a - c) >= 2 and abs(b - c) > 1) or
                 (abs(a - c) < 2 and abs(a - b) >= 2 and abs(b - c) > 1) else False
  
  
'''
We want make a package of goal kilos of chocolate. We have small bars (1 kilo each) and big bars (5 kilos each).
Return the number of small bars to use, assuming we always use big bars before small bars. Return -1 if it can't be done.
'''
# STOLEN FROM HERE >>> https://stackoverflow.com/questions/19932034/a-sample-java-code-reviewmakechocolate-at-codingbat
rem = goal - min(big, goal // 5) * 5
  return rem if rem <= small else -1
