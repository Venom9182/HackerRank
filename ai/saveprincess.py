#!/usr/bin/env python3
n = int(input())
a = []
for i in range(n):
    a.append(input())
    for j in range(n):
        if a[i][j] == 'm':
            x, y = i, j
        if a[i][j] == 'p':
            xx, yy = i, j
while x != xx or y != yy:
    if x < xx:
        print('DOWN')
        x += 1
        continue
    if x > xx:
        print('UP')
        x -= 1
        continue
    if y < yy:
        print('RIGHT')
        y += 1
        continue
    if y > yy:
        print('LEFT')
        y -= 1
        continue
