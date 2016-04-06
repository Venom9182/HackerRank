import numpy as np
from scipy import stats

input()
xs = np.array(list(map(int, input().split())))
print('{:.1f}'.format(xs.mean()))
print('{:.1f}'.format(np.median(xs)))
print(stats.mode(xs)[0][0])
print('{:.1f}'.format(xs.std()))
