c = Hash.new 0
gets.to_i.times {|i|
  gets.strip.each_byte {|x| c[x] += 1 if c[x] > 0 || i == 0 }
  c.each_key {|k| c[k] = [c[k]-1, 1].min } if i > 0
}
p c.each_value.count 1
