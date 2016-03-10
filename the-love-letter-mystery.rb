gets.to_i.times {
  a = gets.strip
  p (a.size/2).times.map {|i| (a[i].ord-a[a.size-1-i].ord).abs }.inject &:+
}
