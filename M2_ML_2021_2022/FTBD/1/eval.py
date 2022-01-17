def eval(tuples):
	if len(tuples) == 1:
		return tuples
	if tuples[1] == '+':
		return eval(tuples[0]) + eval(tuples[2])
	if tuples[1] == '*':
		return eval(tuples[0]) * eval(tuples[2])

def eval2(tuples):
	if tuples[1] == '+':
		return eval(int(tuples[0])) + eval(int(tuples[2]))
	if tuples[1] == '*':
		return eval(int(tuples[0])) * eval(int(tuples[2]))
	return tuples

print('eval:', eval(('1','+','2')))
print('eval2:', eval2(('1','+','2')))
