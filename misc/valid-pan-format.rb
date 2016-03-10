gets.to_i.times {
  if gets.strip =~ /^[A-Z]{5}\d{4}[A-Z]$/
    puts 'YES'
  else
    puts 'NO'
  end
}
