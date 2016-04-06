import math

def pearson(xs, ys):
    n = len(xs)
    e_x = sum(xs)/n
    e_x2 = sum(x*x for x in xs)/n
    var_x = e_x2-e_x**2
    e_y = sum(ys)/n
    e_y2 = sum(y*y for y in ys)/n
    var_y = e_y2-e_y**2
    return sum((x-e_x)*(y-e_y) for x, y in zip(xs, ys))/n/math.sqrt(var_x*var_y)

n = int(input())
xs, ys, zs = [], [], []
for i in range(n):
    x, y, z = list(map(int, input().split()))
    xs.append(x)
    ys.append(y)
    zs.append(z)
print('{:.2f}'.format(pearson(xs, ys)))
print('{:.2f}'.format(pearson(ys, zs)))
print('{:.2f}'.format(pearson(xs, zs)))
