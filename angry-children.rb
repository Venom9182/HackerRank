n = gets.to_i
k = gets.to_i
a = n.times.map { gets.to_i }.sort!
s = a[k-1]-a[0]
k.upto(n-1) {|i|
  t = a[i]-a[i-k+1]
  s = t if t < s
}
p s
