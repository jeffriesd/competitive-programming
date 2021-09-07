"""
ID: jeffrie1
LANG: PYTHON3
TASK: fence6
"""
from collections import defaultdict
from heapq import *


fin = open("fence6.in", "r")
fout = open("fence6.out", "w")

N = int(fin.readline())

weights = {}

adj = defaultdict(dict)

num_nodes = 0
nodes = set()

processed_edges = set()
leaves = set()

# par[ei] = ni
# par maps edge idx to node idx 
par = {}

edgemap = defaultdict(dict)

lefts = {}
rights = {}

for _ in range(N):
    si, L, _1, _2 = map(int, fin.readline().split())

    weights[si] = L

    # connected edges on first end
    left = list(map(int, fin.readline().split()))
    right = list(map(int, fin.readline().split()))

    lefts[si] = (left)
    rights[si] = (right)


# construct adjacency list 
for si in range(1, N+1):
    left = lefts[si]
    right = rights[si]

    # node indices for endpoints of edge si
    endps = [0, 0]
    for (nbi, nbs) in enumerate([left, right]):
        # if any([x in processed_edges for x in nbs]):

        # use edgemap to figure out index of node 
        # given by previously processed edge

        prev_incl = False
        for ei in nbs: 
            if ei in processed_edges:
                # print("query", edgemap, ei, si)
                # print("set endp as em[", ei, si, " ]", edgemap[ei][si])
                endps[nbi] = edgemap[ei][si]
                prev_incl = True
                break

        if prev_incl:
            for ei in nbs:
                # print("set em", si, ei, "= ", endps[nbi])
                edgemap[si][ei] = endps[nbi]
        else:
            # add a new node 

            new_node = num_nodes
            num_nodes += 1
            nodes.add(new_node)

            endps[nbi] = new_node

            for ei in nbs:
                edgemap[si][ei] = new_node
                
                if ei in leaves:
                    # edge ei is already connected
                    # dist is length of ei
                    d = weights[ei]
            
                    # print("update adj", ei)

                    adj[new_node][par[ei]] = d
                    adj[par[ei]][new_node] = d
                else:
                    # add new leaf
                    # print("Add ", ei, "as leaf")
                    par[ei] = new_node
                    leaves.add(ei)

    adj[endps[0]][endps[1]] = weights[si]
    adj[endps[1]][endps[0]] = weights[si]
    
    processed_edges.add(si)
    

# now that we have adj, we can solve the problem 
# by induction on the nodes


min_perim = float("inf")

# do induction on nodes

# set of nodes
included = set()

# shortest path using first k nodes
sp = defaultdict(lambda : defaultdict(lambda: float("inf")))
for n in range(num_nodes):
    sp[n][n] = 0

# add first node
included.add(0)

# find another node to add
nb = list(adj[0])[0]

sp[0][nb] = adj[0][nb]
sp[nb][0] = sp[0][nb]

included.add(nb)

queue = list(range(num_nodes))
queue.remove(0)
queue.remove(nb)

for cur in queue:  
    inclist = list(included)

    # compute min perim going through
    # current node using nodes encountered so far
    for i in range(len(inclist)):
        for j in range(i+1, len(inclist)):
            ni, nj = inclist[i], inclist[j]
            if ni in adj[cur] and nj in adj[cur]:
                di = adj[cur][ni]
                dj = adj[cur][nj]

                per = di + dj + sp[ni][nj]

                min_perim = min(per, min_perim)

    # update sp to include paths going through 
    # current node

    # first compute single source shortest path from cur
    # to all included nodes 
    curdist = defaultdict(lambda: float("inf"))

    q = [(0, cur)]

    while q:
        cost, v = heappop(q)

        for u in adj[v]:
            if u not in included:
                continue
            if cost + adj[v][u] < curdist[u]:
                curdist[u] = cost + adj[v][u]
                sp[u][cur] = curdist[u]

                heappush(q, (curdist[u], u))


    # update all pairs
    for i in range(len(inclist)):
        for j in range(i+1, len(inclist)):
            ni, nj = inclist[i], inclist[j]
            if curdist[ni] + curdist[nj] < sp[ni][nj]:
                sp[ni][nj] = curdist[ni] + curdist[nj]
                sp[nj][ni] = sp[ni][nj]


    included.add(cur)


fout.write("{}\n".format((min_perim)))

fout.close()

