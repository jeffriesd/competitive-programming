# problem: https://open.kattis.com/problems/textencryption

import sys

def encrypted(line, n):
  length = line.__len__()
  string = ""
  answer = [' '] * length 
  start_index = 0
  visited = 0
  while (visited < length):
    ie = 0 
    for i in range(start_index, length, n):
      answer[i] = line[visited].upper()
      visited += 1
      ie += 1
    start_index += 1
  for i in answer:
    string += i
  return string
  
def trim_spaces(line):
  answer = ""
  for c in line:
    if c != " ":
      answer += c
  return answer

def main():

  while 1:
    try: 
      n = int(input())
      line = trim_spaces(input())
      print(encrypted(line, n)) 
    except EOFError:
      exit() 
 
main()
