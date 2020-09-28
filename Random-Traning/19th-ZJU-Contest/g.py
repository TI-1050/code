t = int(input())
while (t != 0) :
	t -= 1
	n = int(input())
	res = 0
	while (n > 0) : 
		n /= 2
		res += n
	print res
