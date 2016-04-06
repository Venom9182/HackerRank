#!/usr/bin/env python
import numpy as np
X, Y = [], []
with open('trainingdata.txt') as f:
    for line in f.readlines():
        x, y = map(float, line.split(','))
        if x <= 4:
            X.append(x)
            Y.append(y)
poly = np.poly1d(np.polyfit(X, Y, 1))
x = float(input())
print('{:.2f}'.format(poly(x) if x <= 4 else 8))
