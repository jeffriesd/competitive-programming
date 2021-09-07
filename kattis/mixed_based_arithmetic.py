# problem: https://open.kattis.com/problems/mixedbasearithmetic

import sys
from math import floor, ceil

def to_decimal(num):
  sum = 0
  placevalue = 1
  #print("\nconverting %s to decimal" % num)
  for dig in reversed(num):
    try:
      i = int(dig)
      sum += i * placevalue 
      placevalue *= 10
    except ValueError:
      #not base 10  
      i = ord(str.lower(dig)) - ord('a') + 1
      sum += i * placevalue 
      #print("sum += %s * %s" % (i, placevalue))
      placevalue *= 26 

  return sum

def get_pv(digtype):
  if "d" in digtype:
    return 10
  else:
    return 26

def to_base(dec, base):
  placevalue = 1
   
  for digtype in reversed(base):
    placevalue *= get_pv(digtype)
  
  highest_order = base[0] 

  #print("dec = %s, p*h = %s" % (dec, placevalue ))

  num_added = 0
   
  new_num = ""
  div = dec

  diglist = []

  for digtype in reversed(base):
    if "d" in digtype:
      div, rem = div_remainder_dec(div) 
    elif "a" in digtype:
      div, rem = div_remainder_str(div, "a")
    else:
      div, rem = div_remainder_str(div, "A")
       
    #print("rem = %s" % rem, end = " ")
    new_num = str(rem) + new_num
    diglist.insert(0, rem)

  #print("div = %s, rem = %s" % (div, type(rem))) 
  # take care of remaining dividend
  while (div > 0):
    if "d" in highest_order:
      div, rem = div_remainder_dec(div)
    elif "a" in highest_order:
      div, rem = div_remainder_str(div, "a")
    else:
      div, rem = div_remainder_str(div, "A")
    if type(rem) is str:
      rem = chr(ord(rem))
    new_num = str(rem) + new_num 
    diglist.insert(0, rem)

  return new_num 
  
def div_remainder_str(num, case):
  rem = (num - 1) % 26
  div = (num - 1) // 26
  start = ord(case)
  return div, chr(rem + start)
  
def div_remainder_dec(num):
  rem = num % 10
  div = num // 10
  return div, rem

def get_base(num):
  base = []
  for s in str(num):
    if ord(s) < 58:
      base.append("d")
    elif ord(s) < 91:
      #upper
      base.append("A")
    else:
      base.append("a")

  return base

def main():

  for line in sys.stdin:
    spl = line.split(" ")
    num = spl[0]
    inc = int(spl[1])
  
    base = get_base(num)
    dec = to_decimal(num)
    answer = (to_base(dec+inc, base))
    #print("before %s, after %s" % (to_decimal(num), to_decimal(answer)))
    print(answer)
    
def inc_test():
  num = "a0"
  base = get_base(num)
  dec = to_decimal(num)
  for i in range(8000):
    print(to_base(dec+i, base))

def div_test():
  for line in sys.stdin:
    spl = line.split(" ")
    num = int(spl[0])
    digtype = spl[1]
    print("num = %s" % num)
    print(div_remainder_dec(num))     

main()
#inc_test()
#div_test()


