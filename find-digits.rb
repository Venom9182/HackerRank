gets.to_i.times {
  y = x = gets.to_i
  c = 0
  while x > 0
    c += 1 if x%10 > 0 && y%(x%10) == 0
    x /= 10
  end
  p c
}
