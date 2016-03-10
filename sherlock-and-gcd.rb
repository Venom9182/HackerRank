gets.to_i.times {
  n = gets.to_i
  if gets.split.map(&:to_i).inject(0) {|x,y| x, y = y, x%y while y > 0; x } == 1
    puts 'YES'
  else
    puts 'NO'
  end
}
