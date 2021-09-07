"""
ID: jeffrie1
LANG: PYTHON3
TASK: lamps
"""

from collections import defaultdict

def bitstring(x):
    return "{0:b}".format(x)

def chunks(xs, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(xs), n):
        yield xs[i:i + n]

def bitchunks(x):
    bs = bitstring(x)[::-1]
    revchunks = list(chunks(bs[::-1], 4))[::-1]
    return " ".join(map(lambda x: x[::-1], revchunks))

fin = open("lamps.in", "r")
fout = open("lamps.out", "w")

N = int(fin.readline())
C = int(fin.readline())


onlamps = list(map(int, fin.readline().split()))[:-1]
offlamps = list(map(int, fin.readline().split()))[:-1]

# no need to use bitmasks due
# to reduced problem size


def even(state):
    for i in range(2, N+1, 2):
        state[i] = 1 - state[i]

def odd(state):
    for i in range(1, N+1, 2):
        state[i] = 1 - state[i]

def flip(state):
    for i in range(1, N+1):
        state[i] = 1 - state[i]

def mod3(state):
    for i in range(1, N+1, 3):
        state[i] = 1 - state[i]

# check if state fits constraints
def match(state, onlamps, offlamps):
    for i in onlamps:
        if not state[i]:
            return False
    for i in offlamps:
        if state[i]:
            return False
    return True

sequences = set()
# for f in range(0, C+1):
#     for e in range(0, C+1-f):
#         for o in range(0, C+1-(e+f)):
#             for m in range(0, C+1-(e+f+o)):
for f in range(0, 2):
    for e in range(0, 2):
        for o in range(0, 2):
            for m in range(0, 2):
                if (f + e + o + m) % 2 == C % 2 and (f + e + o + m) <= C:
                    sequences.add((f % 2, e % 2, o % 2, m % 2))


funcs = [flip, even, odd, mod3]
final_states = set()
for seq in list(sequences):
    state = defaultdict(lambda : 1)
    for fi, amt in enumerate(seq):
        if amt:
            funcs[fi](state)

    # print("seq = ", list(map(lambda x: str(x).split()[1], seq)))
    # print("fs = ", state, bitstring(state))
    if match(state, onlamps, offlamps):
        xs = []
        for i in range(1, N+1):
            xs.append(str(state[i]))
        final_states.add("".join(xs))

if len(final_states):
    for s in sorted(list(final_states)):
        fout.write("{}\n".format(s))
else:
    fout.write("IMPOSSIBLE\n")


fout.close()

