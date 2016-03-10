#!/usr/bin/env python3
from collections import deque
r0, c0 = map(int, input().split())
r1, c1 = map(int, input().split())
n, m = map(int, input().split())
a = [input() for _ in range(n)]
p = [[None]*m for _ in range(n)]
p[r0][c0] = (-1, -1)

expanded = []
q = deque([(r0,c0)])
while q:
    r, c = q.popleft()
    expanded.append((r,c))
    if r == r1 and c == c1:
        break
    for d in ((-1,0),(0,-1),(0,1),(1,0)):
        rr, cc = r+d[0], c+d[1]
        if 0 <= rr < n and 0 <= cc < m and a[rr][cc] != '%' and not p[rr][cc]:
            p[rr][cc] = (r,c)
            q.append((rr,cc))

print(len(expanded))
for r, c in expanded:
    print(r, c)

path = []
while r1 != r0 or c1 != c0:
    path.append((r1, c1))
    r1, c1 = p[r1][c1]
path.append((r0, c0))
print(len(path)-1)
for r, c in path[::-1]:
    print(r, c)
