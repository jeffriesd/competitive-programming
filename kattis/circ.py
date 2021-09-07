# problem: https://naq19.kattis.com/problems/circuitmath

n = int(input())

truths = input().split(" ")
truths = list(map(lambda t : t == "T", truths))

tr = dict()

c = "A"
i = 0 
for t in truths:
    tr[c] = truths[i]
    i += 1
    c = chr(ord(c) + 1)

ops = input().split(" ")

# do some postfix circuit arithmetic 
stack = []
for x in ops:
    if x in ["+", "*"]:
        a = stack.pop()
        b = stack.pop()
        if x is "+":
            stack.append(a or b)
        else:
            stack.append(a and b)
    elif x is "-":
        stack.append(not stack.pop())
    else:
        stack.append(tr[x])


if stack[0]:
    print("T")
else:
    print("F")
