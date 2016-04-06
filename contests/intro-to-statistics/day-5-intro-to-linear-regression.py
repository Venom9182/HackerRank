import numpy as np
a = [(95,85),(85,95),(80,70),(70,65),(60,70)]
coef = np.linalg.lstsq([[1, x[0]] for x in a], [x[1] for x in a])[0]
print('{:.1f}'.format(coef[1]*80+coef[0]))
