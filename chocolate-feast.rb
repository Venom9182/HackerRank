gets.to_i.times {
  n, c, m = gets.split.map &:to_i
  w = s = n/c
  while w >= m
    s += w/m
    w = w%m+w/m
  end
  p s
}
