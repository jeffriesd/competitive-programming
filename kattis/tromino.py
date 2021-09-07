# problem: https://open.kattis.com/problems/turningtrominos

def fun(x, y):
    h = np2(max(x, y)) // 2
    q = h // 2
    q3 = q + h
    if x == y:
        return 0
    if h <= 1:
        return 0

    if x > h and y > h:
        x -= h
        y -= h
        return fun(x, y)

    if x > y:
        if (y > q and x <= q3):
            return fun(x - q, y - q)
    
        xx = y - h + (q3 - q)

        yy = -x + (q3 + q + 1)
        return (-1 + fun(xx, yy)) % 4
    elif y > x:
        if (x > q and y <= q3):
            return fun(x - q, y - q)
        xx = -y + q + q3 + 1
        yy = x - h + (q3 - q)
        return (fun(xx, yy) + 1) % 4

def np2(a):
    p = 1
    while (p < a):
        p *= 2
    return p

def main():
    for _ in range(int(input())):
        x, y = map(int, input().split())
        print(fun(x+1, y+1))

main()
