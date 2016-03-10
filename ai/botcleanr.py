#!/usr/bin/env python3
n = 5
x, y = map(int, input().split())
a = [input() for _ in range(5)]
for i in range(5):
    for j in range(5):
        if a[i][j] == 'd':
            if i == x and j == y:
                print('CLEAN')
            elif i < x:
                print('UP')
            elif i > x:
                print('DOWN')
            elif j < y:
                print('LEFT')
            elif j > y:
                print('RIGHT')
            exit()
