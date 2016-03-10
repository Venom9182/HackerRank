MOD = 10**9+7
n, m = gets.split.map &:to_i
a = gets.split.map &:to_i
b = gets.split.map &:to_i
c = gets.split.map &:to_i
b.zip(c).group_by(&:first).each {|b,bcs|
  prod = bcs.inject(1) {|prod,c| prod*c[1]%MOD }
  i = b
  while i <= n
    a[i-1] = a[i-1]*prod%1000000007
    i += b
  end
}
puts a.join ' '
