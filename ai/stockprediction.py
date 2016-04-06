#!/usr/bin/env python
import math
import numpy as np

def stochastic_oscillator(a, k):
    mn = a[-k:].min()
    mx = a[-k:].max()
    return (a[-1]-mn)/(mx-mn) if mn < mx else 0

m, k, _ = input().split()
m = float(m)
k = int(k)
names = []
own = []
prices = []
for data in range(k):
    temp = input().split()
    names.append(temp[0])
    own.append(int(temp[1]))
    prices.append([float(i) for i in temp[2:7]])

prices = np.array(prices)
std = prices.std(1)
output = []
for i in reversed(np.argsort(std)):
    sa = stochastic_oscillator(prices[i], 3)
    if sa > 0.8 and own[i]:
        output.append('{} SELL {}'.format(names[i], own[i]))
    elif sa < 0.2 and m:
        num = int(math.floor(m / prices[i][-1] - 1e-9))
        if num:
            m -= num * prices[i][-1]
            output.append('{} BUY {}'.format(names[i], num))
print(len(output))
for line in output:
    print(line)
