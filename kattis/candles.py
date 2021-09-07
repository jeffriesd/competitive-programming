# problem: https://open.kattis.com/problems/candlebox

# difference in ages
D = int(input())
R = int(input())
T = int(input())

rsums = dict()
tsums = dict()

s = 0 
for i in range(4,10000):
    s += i 
    rsums[s] = i 

s = 0
for i in range(3,10000):
    s += i 
    tsums[s] = i 

# try removing every amount of candles 
for i in range(1001):
    Rx = R - i 
    Tx = T + i 

    if Rx in rsums and Tx in tsums:
        if tsums[Tx] + D == rsums[Rx]:
            print(i)
            break
