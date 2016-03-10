def find(x):
    while uf[x] >= 0:
        if uf[uf[x]] >= 0:
            uf[x] = uf[uf[x]]
        x = uf[x]
    return x

n = int(input())
uf = [-1]*(2*n)
for i in range(n):
    x, y = map(int, input().split())
    x, y = find(x-1), find(y-1)
    if x != y:
        if uf[x] > uf[y]:
            x, y = y, x
        uf[x] += uf[y]
        uf[y] = x
mn, mx = 2*n, 0
for i in range(2*n):
    if uf[i] < -1:
        mn = min(mn, - uf[i])
        mx = max(mx, - uf[i])
print(mn, mx)
