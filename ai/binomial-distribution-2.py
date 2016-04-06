from scipy.stats import binom
print('{:.3f}'.format(1 - binom.cdf(3-1, 6, 1.09/(1+1.09))))
