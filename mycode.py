def fib(n):
  def aux(n,r):
	if(n<1):
		return r
	else:
		return aux(n-1, r*n)

result = fib(10)
print(result)
