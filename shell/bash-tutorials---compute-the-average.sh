#!/bin/bash
read n
x=$({ echo -n 'scale=4;(';{ cat;echo;}|tr -s '\n'|tr '\n' '+';echo "0)/$n";} | bc)
(($(echo $x | sed 's/.*\....\(.\)/\1/') >= 5)) && x=$(echo "scale=3;($x+0.001)/1" | bc) || x=$(echo "scale=3;$x/1" | bc)
echo $x
