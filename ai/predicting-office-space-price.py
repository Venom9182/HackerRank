from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
import numpy as np

f, n = map(int, input().split())
poly = PolynomialFeatures(3)
A, B = np.empty((n, f)), np.empty(n)
for i in range(n):
    xs = list(map(float, input().split()))
    A[i] = xs[:-1]
    B[i] = xs[-1]
lr = LinearRegression()
lr.fit(poly.fit_transform(A), B)
for i in range(int(input())):
    xs = list(map(float, input().split()))
    print(lr.predict(poly.fit_transform([xs]))[0])
