egrep ".*([aeiou].*){3}.*" | egrep "(.)\1" | egrep -v "(ab)|(cd)|(pq)|(xy)" -c
