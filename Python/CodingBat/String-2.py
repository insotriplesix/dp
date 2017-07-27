'''
Given a string, return a string where for every char in the original, there are two chars.
'''
def double_char(str):
  new_str = ""
  
  for c in str:
    new_str += c * 2
    
  return new_str
  
  
'''
Return the number of times that the string "hi" appears anywhere in the given string.
'''
def count_hi(str):
  return str.count('hi')
  
  
'''
Return True if the string "cat" and "dog" appear the same number of times in the given string.
'''
def cat_dog(str):
  return str.count('cat') == str.count('dog')
  
  
'''
Return the number of times that the string "code" appears anywhere in the given string,
except we'll accept any letter for the 'd', so "cope" and "cooe" count.
'''
def count_code(str):
  cnt = 0
  
  for i in range(0, len(str) - 3):
    if str[i] == 'c' and str[i + 1] == 'o' and str[i + 3] == 'e':
      cnt += 1
      
  return cnt
  
  
'''
Given two strings, return True if either of the strings appears at the very end of the other string,
ignoring upper/lower case differences (in other words, the computation should not be "case sensitive").
Note: s.lower() returns the lowercase version of a string.
'''
def end_other(a, b):
  less = a if len(a) < len(b) else b
  greater = a if less != a else b
  
  if less.lower() == greater[-len(less):].lower():
      return True
  else:
      return False
  
  
'''
Return True if the given string contains an appearance of "xyz" where the xyz is not directly preceeded by a period (.).
So "xxyz" counts but "x.xyz" does not.
'''
def xyz_there(str):
  for i in range(0, len(str) - 2):
    if 'xyz' == str[i:i + 3]:
      if i == 0:
        return True
      elif i != 0 and str[i - 1] != '.':
        return True
        
  return False
