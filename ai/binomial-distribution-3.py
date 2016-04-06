from scipy.stats import binom
print('{:.3f}'.format(binom.cdf(2, 10, 0.12)))
print('{:.3f}'.format(1 - binom.cdf(2-1, 10, 0.12)))
