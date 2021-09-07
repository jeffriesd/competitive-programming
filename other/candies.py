
def main():
  n, T = map(int, input().split())

  booths = []
  for idx, b in enumerate(input().split()):
    booths.append((int(b), idx))

  stack = []
  goround = 0
  for k in sorted(booths, key=lambda x: x[0]):
    stack.append((k[0], k[1]))
    goround += k[0]

  candies = 0
  num_dead = 0 
  position = 0
  while T > 0:
    # if can afford full go round
    if goround < T:
      num_rounds = T // goround

      candies += (n - num_dead) * num_rounds

      T -= num_rounds * goround
    else:

      # start removing max from stack
      while stack and stack[-1][0] > T:
        maxbooth, idx = stack.pop()

        # mark booth as dead
        booths[idx] = None
        num_dead += 1

      # if full goround still > T, go one by one
      position = (position + 1) % n 
      num_moves = 0
      while booths[position] is None:
        position = (position + 1) % n 
        # print(num_moves)
        num_moves += 1
        # if cycling dead booths 
        if num_moves >= n:
          print(candies)
          return

      num_dead = 0
      for b in booths:
        if b is None:
          num_dead += 1
          if num_dead == n:
            print(candies)
            return
          continue
        c, idx = b
        if T >= c:
          T -= c
          candies += 1
          
          if c > T:
            booths[idx] = None
        else:
          booths[idx] = None

  print(candies) 

main()
