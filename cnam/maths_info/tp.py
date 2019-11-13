#####################################################################
#                     name : TP.PY									#
#					  author : Geoffrey NORO						#
#####################################################################

# xor = ^ en python

# addition et multiplication dans les corps de galois 2**8

#!/usr/bin/env python
# -*- coding: utf-8 -*-



def addition(a,b):
	c=ord(a)^ord(b)
	return c

def multiplication(a,b):
	result = 0 #init result
	x = ord(a) #init x
	y = ord(b) #init y
	for i in range(8):
		if (y%2)==1:
			result = x
		x = xtimes(chr(x))
		y = int(y/2)
	return result

def xtimes(a):
	result = 0
	if ord(a)>128:
		result=((ord(a)-128)*2)^27
	else:
		result=ord(a)*2
	return result

def inverse(a):
	pass



print("addition")
print (addition('5','2'))
print (addition('7','2'))
print("multiplication")
print(multiplication('5','7'))
print("xtimes")
print(xtimes("a"))
print(ord('à'))
print(xtimes("à"))