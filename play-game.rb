gets.to_i.times {
  n = gets.to_i
  a = gets.split.map &:to_i
  a << 0 << 0
  s = [0]*(n+3)
  (n-1).downto(0) {|i|
    s[i] = [a[i]-s[i+1], a[i]+a[i+1]-s[i+2], a[i]+a[i+1]+a[i+2]-s[i+3]].max
  }
  p a.inject(&:+)+s[0] >> 1
}
