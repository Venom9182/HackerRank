from collections import defaultdict

for _ in range(int(input())):
    a = input()
    n = len(a)
    c = defaultdict(int)
    for i in range(n):
        for j in range(i, n):
            c[''.join(sorted(list(a[i:j+1])))] += 1
    ans = 0
    for i in c.values():
        ans += i*(i-1)//2
    print(ans)
