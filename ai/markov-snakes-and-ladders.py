def gauss_jordan(A):
    n = len(A)
    pi = [-1]*n
    for i in range(n):
        pivotv = 0
        for j in range(n):
            if abs(A[i][j]) > pivotv:
                pivot, pivotv = j, abs(A[i][j])
        if pivotv < 1e-9:
            continue
        pi[pivot] = i
        t = A[i][pivot]
        for j in range(n+1):
            A[i][j] /= t
        for j in range(n):
            if j != i:
                t = A[j][pivot]
                for k in range(n+1):
                    A[j][k] -= A[i][k]*t
    return A[pi[0]][n]

for _ in range(int(input())):
    die = list(map(float, input().split(',')))
    n = 100
    to = list(range(n))
    input()
    for ladder in input().split():
        x, y = map(int, ladder.split(','))
        to[x-1] = y-1
    for snake in input().split():
        x, y = map(int, snake.split(','))
        to[x-1] = y-1
    A = [[0.0]*(n+1) for i in range(n)]
    for i in range(n-1):
        A[i][i] = 1.0
        r = 0
        for j in range(min(6, n-1-i)):
            t = to[i+j+1]
            if i != t:
                r += die[j]
        r = 1 / r
        A[i][n] = r if i < n-1 else 0.0
        for j in range(min(6, n-1-i)):
            t = to[i+j+1]
            if i != t:
                A[i][t] -= die[j] * r
    A[n-1][n-1] = 1.0
    print(int(round(gauss_jordan(A))))
