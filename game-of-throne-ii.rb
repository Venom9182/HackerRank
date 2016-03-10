MOD = 1000000007

def inv x
  n = MOD-2
  s = 1
  while n > 0
    s = s*x%MOD if n & 1 == 1
    x = x*x%MOD
    n >>= 1
  end
  s
end

a = gets.strip
c = [0]*256
a.each_byte {|x| c[x] += 1 }
if 127.times.count {|i| c[i]%2 == 1 } > a.size%2
  p 0
else
  fac = [1]*(a.size/2+1)
  1.upto(a.size/2) {|i| fac[i] = fac[i-1]*i%MOD }
  p 127.times.inject(fac[a.size/2]) {|ans,i| ans*inv(fac[c[i]/2])%MOD }
end
