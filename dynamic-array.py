#!/usr/bin/env python3
n, q = map(int, input().split())
ans = 0
a = [[] for i in range(n)]
for i in range(q):
    op, x, y = map(int, input().split())
    if op == 1:
        a[(ans^x)%n].append(y)
    else:
        b = a[(ans^x)%n]
        ans = b[y%len(b)]
        print(ans)
