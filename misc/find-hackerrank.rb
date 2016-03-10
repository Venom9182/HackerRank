gets.to_i.times {
  s = gets.strip
  r = 0
  r |= 2 if s.start_with? 'hackerrank'
  r |= 1 if s.end_with? 'hackerrank'
  p r > 0 ? 3-r : -1
}
