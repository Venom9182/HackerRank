import math
import numpy as np
from scipy import stats

n = int(input())
xs = np.array(list(map(int, input().split())))
mean = xs.mean()
std = xs.std()
confidence_interval_critical_value = 1.96
print('{:.1f}'.format(mean))
print('{:.1f}'.format(np.median(xs)))
print(stats.mode(xs)[0][0])
print('{:.1f}'.format(std))
print('{:.1f} {:.1f}'.format(mean-confidence_interval_critical_value*std/math.sqrt(n), mean+confidence_interval_critical_value*std/math.sqrt(n)))
