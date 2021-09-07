# problems: https://open.kattis.com/problems/racingalphabet

import sys
import math


def letter_to_angle(letter):
    letters = ["A", "B", "C", "D", "E", "F", "G",
                "H", "I", "J", "K", "L", "M", "N",
                "O", "P", "Q", "R", "S", "T", "U",
                "V", "W", "X", "Y", "Z", " ", "'"]
    index = letters.index(letter)
    return 2 * math.pi * index/28.0

def arc_distance(a, b, r):
    theta_a = letter_to_angle(a)
    theta_b = letter_to_angle(b)

    angle_dif = abs(theta_a - theta_b)
    if abs(theta_a - theta_b) > math.pi:
        angle_dif = 2*math.pi - abs(theta_a - theta_b)
    return angle_dif * r
 
def best_time(aph):
    total_time = 1
    for i in range(0, aph.__len__() - 1):
        a = aph[i]
        b = aph[i+1]
        distance_ft = arc_distance(a, b, 30)
        secs = distance_ft / 15.0
        total_time += secs + 1.0
    return total_time

def __main__():
    i = 0
    num_lines = 0
    aph = []
    for line in sys.stdin:
        if i == 0:
            num_lines = int(line)
        elif i == num_lines:
            aph.append(line[:-1])
            for a in aph:
                print(best_time(a))
        else:
            aph.append(line[:-1])
        i+= 1

__main__()
