from scipy.stats import binom
n = 4
p = 0.8
print('{:.3f}'.format(1 - binom.cdf(2, n, p)))
print('{:.3f}'.format(binom.cdf(4-3, n, p)))
