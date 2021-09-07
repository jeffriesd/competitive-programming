# problem: https://open.kattis.com/problems/howmanydigits

import math
import sys
def digits(num):
  sum = 0
  for i in range(num, 1, -1):
    sum += math.log(i, 10)
    if math.ceil(sum) == 0:
      return 1
    return math.ceil(sum)


def fill_dic(dic, target, max_key):
  if not dic:
    start = 1
    stop = target
    logsum = 0
  else: 
    start = max_key 
    stop = target 
    logsum = dic[max_key]
  #print("start = %s, stop = %s" % (start, stop))
  for i in range(start + 1, stop + 1):
    #print("sum += log(%s)" % i)
    logsum += math.log(i, 10)
    dic[i] = logsum 
    #print("dic[%s] = %s" % (i, logsum))  
  #print()  

def main():
  digdic = {0: 0.0, 1: 0.0}
  max_key = 1
  for i in sys.stdin:
    num = int(i)
    logsum = 0.0 
    #print("doing %s" % num)
    if num in digdic:
      logsum = digdic[num]
    else:
      fill_dic(digdic, num, max_key)
      logsum = digdic[num]
      max_key = num
    c = math.ceil(logsum)
    #print("digs = %s" % logsum)
    if c == 0:
      c = 1
    print(c)

main()
