from scipy.stats import norm
mu = 70
sigma = 10
print('{:.2f}'.format((1 - norm.cdf(80, mu, sigma)) * 100))
print('{:.2f}'.format((1 - norm.cdf(60, mu, sigma)) * 100))
print('{:.2f}'.format(norm.cdf(60, mu, sigma) * 100))
