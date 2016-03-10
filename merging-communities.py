def find(x):
    while uf[x] >= 0:
        if uf[uf[x]] >= 0:
            uf[x] = uf[uf[x]]
        x = uf[x]
    return x

n, m = map(int, input().split())
uf = [-1]*n
for i in range(m):
    ls = input().split()
    if ls[0] == 'Q':
        print(- uf[find(int(ls[1])-1)])
    else:
        x, y = find(int(ls[1])-1), find(int(ls[2])-1)
        if x != y:
            if uf[x] > uf[y]:
                x, y = y, x
            uf[x] += uf[y]
            uf[y] = x
