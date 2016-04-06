from scipy.stats import norm
mu = 30
sigma = 4
print('{:.3f}'.format(norm.cdf(40, mu, sigma)))
print('{:.3f}'.format(1 - norm.cdf(21, mu, sigma)))
print('{:.3f}'.format(norm.cdf(35, mu, sigma) - norm.cdf(30, mu, sigma)))
