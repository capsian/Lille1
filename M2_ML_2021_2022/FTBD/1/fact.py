# Selim Lakhdar
# selim.lakhdar.etu@univ-lille.fr

def fact(n):
	if n < 0:
		raise Exception("n should be positif") 
	if n == 0:
		return 1
	else:
		return n * fact(n-1)
		

print('fact(0):', fact(0))
print('fact(1):', fact(1))
print('fact(2):', fact(2))
print('fact(3):', fact(3))
print('fact(4):', fact(4))
print('fact(5):', fact(5))
print('fact(-1):', fact(-1))
