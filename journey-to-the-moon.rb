n, m = gets.split.map &:to_i
djs = [-1]*n
m.times {
  a, b = gets.split.map &:to_i
  while djs[a] >= 0
    djs[a] = djs[djs[a]] if djs[djs[a]] >= 0
    a = djs[a]
  end
  while djs[b] >= 0
    djs[b] = djs[djs[b]] if djs[djs[b]] >= 0
    b = djs[b]
  end
  if a != b
    a,b = b,a if djs[a] > djs[b]
    djs[a] += djs[b]
    djs[b] = a
  end
}
s = 0
sum = -(djs.select {|x| x < 0}.inject &:+)
djs.each {|x| s += (-x)*(sum+x) if x < 0 }
p s>>1
