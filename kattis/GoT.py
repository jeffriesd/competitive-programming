# problem: https://open.kattis.com/problems/throwns 

import sys

def final(n, commands):
    coms = []
    n_com = commands.__len__()
    i = 0
    while i < n_com:    
        c = commands[i]
        if c.__contains__("u"):
            num_undo = int(commands[i+1])
            coms = coms[0:-num_undo]
            i += 1
        else:
            c = int(c)
            coms.append(c)
        i += 1

    final_pos = 0
    for i in coms:
        final_pos = (final_pos + n + i) % n
    return final_pos
     
def __main__():
    i = 0
    for line in sys.stdin:
        if i % 2 == 0:
            n_students, n_com = line.split(" ")
        else:
            commands = line.split(" ")
            print(final(int(n_students), commands))
        i += 1

__main__()
