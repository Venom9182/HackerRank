gets.to_i.times {
  x = gets.to_i
  a, b, c = 0, 1, 1
  while b < x
    if (a+c)*b <= x
      a, b, c = a*a+b*b, (a+c)*b, b*b+c*c
    else
      a, b, c = b, c, b+c
    end
  end
  puts (b == x || x == 0 ? 'IsFibo' : 'IsNotFibo')
}
