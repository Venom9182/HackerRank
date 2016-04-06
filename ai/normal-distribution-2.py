from scipy.stats import norm
mu = 20
sigma = 2
print('{:.3f}'.format(norm.cdf(19.5, mu, sigma)))
print('{:.3f}'.format(norm.cdf(22, mu, sigma) - norm.cdf(20, mu, sigma)))
