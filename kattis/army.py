# problem: https://open.kattis.com/problems/armystrengtheasy 

def winner(garmy, marmy, ng, nm):
  while not (garmy.__len__() == 0 or marmy.__len__() == 0):
    gweakest = min(garmy)
    mweakest = min(marmy)
    
    if gweakest < mweakest:
      garmy.remove(gweakest)
    else:
      marmy.remove(mweakest)

  if garmy.__len__() == 0:
    return "MechaGodzilla"
  else:
    return "Godzilla"

def __main__():
  num_cases = int(input())
  
  for _ in range(num_cases):
    input()
    sizes = input().split()
    ng = sizes[0]
    nm = sizes[1]
    gline = input().split()
    mline = input().split()
    garmy = []
    for g in gline:
      garmy.append(int(g))
    marmy = []
    for m in mline:
      marmy.append(int(m))
    print(winner(garmy, marmy, ng, nm))
  
__main__()
