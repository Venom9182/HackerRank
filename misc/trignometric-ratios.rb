gets.to_i.times{x=gets.to_f;s=c=0;f=1;5.times{|i|j=i*2;s+=f*x/(j+1);c+=f;f*=-x*x/(j+1)/(j+2)};p s.round 3;p c.round 3}
