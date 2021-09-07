# problem: https://open.kattis.com/problems/calculatingdartscores

import sys

def test_combinations(f, s, t, target):
    
    for a in range(1, 4):
        for b in range(1, 4):
            for c in range(1, 4):
                if a*f + b*s + c*t == target:
                    return a, b, c
    return None
    
def test_all_scores(target):
    possible_scores = [i+1 for i in range(20)]

    for f in possible_scores:
        for s in possible_scores:
            for t in possible_scores:
                ans = test_combinations(f, s, t, target)
                if ans:
                    return ans, (f, s, t)
    
def mult_to_word(m):
    if m == 1:
        return "single"
    if m == 2:
        return "double"
    if m == 3:
        return "triple"

def output(target):
    target = int(target)
    ans = test_all_scores(target)
    if ans is None:
        if target < 3:
            return "single %s" % target
        return "impossible"
    m1 = mult_to_word(ans[0][0])
    m2 = mult_to_word(ans[0][1])
    m3 = mult_to_word(ans[0][2])
    s1 = ans[1][0]
    s2 = ans[1][1]
    s3 = ans[1][2]

    string = m1 + " " + str(s1) + "\n"
    string += m2 + " " + str(s2) + "\n"
    string += m3 + " " + str(s3)
    return string

def __main__():
    for i in sys.stdin:
        target = int(i)
        break    
    print(output(target))   

__main__()



