import numpy as np
xs = [15,12,8,8,7,7,7,6,5,3]
ys = [10,25,17,11,13,17,20,13,9,15]
b, a = np.linalg.lstsq([[1,x] for x in xs], ys)[0]
print('{:.1f}'.format(10*a+b))
