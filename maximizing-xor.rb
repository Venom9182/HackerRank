a = gets.to_i
b = gets.to_i
31.downto(0) {|i|
  if (a^b)>>i & 1 == 1
    p (1<<i+1)-1
    exit
  end
}
p 0
