from scipy.stats import pearsonr, spearmanr
a = [10, 9.8, 8, 7.8, 7.7, 7, 6, 5, 4, 2]
b = [200, 44, 32, 24, 22, 17, 15, 12, 8, 4]
print('{:.3f}'.format(pearsonr(a, b)[0]))
print('{:.1f}'.format(spearmanr(a, b).correlation))
