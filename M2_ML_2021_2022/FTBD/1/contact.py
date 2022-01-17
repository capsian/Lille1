def concat(str1, str2):
	if len(str2) == 0:
		return str1 
	return concat(str1 + str2[0], str2[1:])
	
print(concat("hello", "selim"))
