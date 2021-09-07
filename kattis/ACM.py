# problem : https://open.kattis.com/problems/acm

def get_pen(pens, problem):
  if problem in pens:
    return pens[problem]
  else:
    pr 

def update_score(score, t, prob, rw, pens):
  if rw == "right":
    # if previous penalties
    if prob in pens:
      score += pens[prob] * 20
    score += t
  else:
    if prob in pens:
      pens[prob] += 1
    else:
      pens[prob] = 1
  return score
 
def __main__():
  line = input()
  score = 0
  correct = 0
  pens = {} 
  while line != "-1":
    spl = line.split()
    t = int(spl[0])
    prob = spl[1]
    rw = spl[2]
    score = update_score(score, t, prob, rw, pens) 
    if rw == "right":
      correct += 1
    line = input()
  print(correct, score)
__main__()
