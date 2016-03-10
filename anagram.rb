gets.to_i.times {
  s = gets.chomp
  if s.size % 2 == 1
    p -1
  else
    c = Hash.new 0
    s[0...s.size/2].each_byte {|i| c[i] += 1 }
    s[s.size/2..-1].each_byte {|i| c[i] -= 1 }
    p c.each_value.inject(0) {|x,y| x+y.abs }/2
  end
}
