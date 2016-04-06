import numpy as np
f, n = map(int, input().split())
A = np.zeros((n, f+1))
B = np.zeros(n)
for i in range(n):
    xs = list(map(float, input().split()))
    A[i] = [1] + xs[:-1]
    B[i] = xs[-1]
coef = np.linalg.lstsq(A, B)[0]
for i in range(int(input())):
    print(np.dot(coef, [1] + list(map(float, input().split()))))
