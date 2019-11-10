'''
The parameter weekday is True if it is a weekday, and the parameter vacation is True if we are on vacation.
We sleep in if it is not a weekday or we're on vacation. Return True if we sleep in.
'''
def sleep_in(weekday, vacation):
  if (weekday is False and vacation is False):
    return True
  elif (weekday is True and vacation is False):
    return False
  elif (weekday is False and vacation is True):
    return True
  elif (weekday is True and vacation is True):
    return True
    
   
'''
We have two monkeys, a and b, and the parameters a_smile and b_smile indicate if each is smiling.
We are in trouble if they are both smiling or if neither of them is smiling. Return True if we are in trouble.
'''
def monkey_trouble(a_smile, b_smile):
  if (a_smile is b_smile):
    return True
  else:
    return False   
    
    
'''
Given two int values, return their sum. Unless the two values are the same, then return double their sum.
'''
def sum_double(a, b):
  if (a != b):
    return a + b
  else:
    return (a + b) * 2    
    
    
'''
Given an int n, return the absolute difference between n and 21, except return double the absolute difference if n is over 21.
'''
def diff21(n):
  if (n <= 21):
    return (abs(n - 21))
  else:
    return (abs(n - 21)) * 2
    
    
'''
We have a loud talking parrot. The "hour" parameter is the current hour time in the range 0..23.
We are in trouble if the parrot is talking and the hour is before 7 or after 20. Return True if we are in trouble.
'''
def parrot_trouble(talking, hour):
  if (talking is True and (hour < 7 or hour > 20)):
    return True
  else:
    return False
    
        
'''
Given 2 ints, a and b, return True if one if them is 10 or if their sum is 10.
'''
def makes10(a, b):
  if (a == 10 or b == 10 or a + b == 10):
    return True
  else:
    return False    
        
        
'''
Given an int n, return True if it is within 10 of 100 or 200. Note: abs(num) computes the absolute value of a number.
'''
def near_hundred(n):
  a = 100 - n
  b = 200 - n
  return abs(a) <= 10 or abs(b) <= 10
  
  
'''
Given 2 int values, return True if one is negative and one is positive.
Except if the parameter "negative" is True, then return True only if both are negative.
'''
def pos_neg(a, b, negative):
  if (a < 0 and b >= 0 and negative is not True):
    return True
  elif (b < 0 and a >= 0 and negative is not True):
    return True
  elif (a < 0 and b < 0 and negative is True):
    return True
  else:
    return False
      
  
'''
Given a string, return a new string where "not " has been added to the front.
However, if the string already begins with "not", return the string unchanged.
'''
def not_string(str):
  if (str[:3] == 'not'):
    return str
  else:
    return 'not ' + str;
    
    
'''
Given a non-empty string and an int n, return a new string where the char at index n has been removed.
The value of n will be a valid index of a char in the original string (i.e. n will be in the range 0..len(str)-1 inclusive).
'''
def missing_char(st, n):
  if (n == 0):
    return st[1:]
  else:
    return st[0:n] + st[n + 1:]
        
    
'''
Given a string, return a new string where the first and last chars have been exchanged.
'''
def front_back(str):
  if (len(str) == 1 or len(str) == 0):
    return str
  elif (len(str) == 2):
    return str[-1] + str[0]
  else:
    return str[-1] + str[1:-1] + str[0]
  

'''
Given a string, we'll say that the front is the first 3 chars of the string.
If the string length is less than 3, the front is whatever is there.
Return a new string which is 3 copies of the front.
'''
def front3(str):
  if (len(str) >= 3):
    return str[:3] * 3
  else:
    return str * 3
