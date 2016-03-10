#!/usr/bin/env python3
n = int(input())
r, c = map(int, input().split())
for i in range(n):
    a = input()
    for j in range(n):
        if a[j] == 'p':
            if i < r:
                print('UP')
                exit()
            if i > r:
                print('DOWN')
                exit()
            if j < c:
                print('LEFT')
                exit()
            if j > c:
                print('RIGHT')
                exit()
