xs = [15,12,8,8,7,7,7,6,5,3]
ys = [10,25,17,11,13,17,20,13,9,15]
n = len(xs)
sumx = sum(xs)
sumy = sum(ys)
sumxy = sum(x*y for x, y in zip(xs, ys))
sumxx = sum(x*x for x in xs)
print('{:.3f}'.format((n*sumxy-sumx*sumy) / (n*sumxx-sumx**2)))
#from scipy.stats import linregress
#print('{:.3f}'.format(linregress(xs, ys).slope))
