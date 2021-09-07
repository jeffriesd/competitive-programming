# problem: https://open.kattis.com/problems/akcija

def get_min(prices, size):
  min_price = 0
  i = 0
  for p in prices:
    if i % 3 < 2:
      min_price += p
    i += 1

  return min_price

def __main__():
  n = int(input())
  prices = []
  for _ in range(n):
    price = int(input())
    prices.append(price)
  prices = reversed(sorted(prices))
  print(get_min(prices, n)) 
  
__main__()
