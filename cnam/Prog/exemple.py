# 1) fonction max entre 2 nbre
def max(num1,num2):
	if num1>num2:
		return num1
	else :
		return num2

print("max function \n")
print(max(10,44))
print("\n------------------------ \n")

# 2) fonction max entre 3 nbre sans max
def maxTroisA(num1,num2,num3):
	if num1 > num2:
		if num1 > num3:
			return num1
		else:
			return num3
	else:
		if num2 > num3:
			return num2
		else:
			return num3

print("maxTroisA function \n")
print(maxTroisA(-55,6,77))
print("\n------------------------ \n")

# 2) fonction max entre 3 nbre avec max
def maxTroisB(num1,num2,num3):
	if max(num1,num2) == num1:
		if max(num1,num3) == num1:
			return num1
		else:
			return num3
	else:
		if max(num2,num3) == num2:
			return num2
		else:
			return num3

print("maxTroisB function \n")
print(maxTroisB(-55,6,77))
print("\n------------------------ \n")

"""
def maxListe(num1,num2,num3):
	l = [num1,num2,num3]
	max = l[0]
	for i in l:
		if i>=max:
			max=i
	return max

print("maxListe function \n")
print(maxListe(-55,6,77))
print("\n------------------------ \n")
"""

# 3) max d'une liste
def maxListe(liste):
	max = liste[0]
	for i in liste:
		if i>=max:
			max=i
	return max

print("maxListe function \n")
print(maxListe([20,55,77,3,5,88]))
print("\n------------------------ \n")

# 3.1) addition tous les elems d'une liste
def addition(liste):
	total=0
	for i in liste:
		total+=i
	return total

print("addition function \n")
print(addition([20,55,77,3,5,88]))
print("\n------------------------ \n")

# 3.2) trie de liste decroissant
def trieListe(liste):
	listeTriee=[]
	while liste:
		a = maxListe(liste)
		listeTriee.append(a)
		liste.remove(a)
	return listeTriee
		

print("trieListe function \n")
print(trieListe([20,55,77,3,5,88]))
print("\n------------------------ \n")

# 4) inverser une chaine de caractere

def reverseStr(string):
	revStr=""
	for i in string:
		revStr = i + revStr
	return revStr

print("reverseStr function \n")
print(reverseStr("Je suis grand"))
print("\n------------------------ \n")

# 5) Palyndrome
def palyndrome(string):
	if string == reverseStr(string):
		return True
	else:
		return False
		

print("reverseStr function \n")
print(palyndrome("abba"))
print(palyndrome("toto"))
print("\n------------------------ \n")