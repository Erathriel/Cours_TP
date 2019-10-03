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

# plus long mot d'une phrase

def longerWord(string):
	liste = string.split()
	longer = liste[0]
	for i in liste:
		if len(i)>= len(longer):
			longer = i
	return longer		

print("longerWord function \n")
print(longerWord("Je suis grand"))
print("\n------------------------ \n")

# si la phrase est un pangramme

def pangramme(string):
	alphabet="abcdefghijklmnopqrstuvwxyz"
	for i in alphabet:
		if i not in string.lower():
			return False
	return True

print("Pangramme function \n")
print(pangramme("Portez ce vieux whisky au juge blond qui fume"))
print("\n------------------------ \n")

def chiffrementCesar(cle, string):
	encrypt=""
	for i in string.upper():
		a = ord(i) + (cle%26)
		if a > 90:
			encrypt = encrypt + chr(64+(a-90))
		elif ord(i) == 32:
			encrypt += i
		elif ord(i) == 10:
			encrypt += i
		else:
			encrypt = encrypt + chr(a)
	return encrypt

print("chiffrementCesar function \n")
print(chiffrementCesar(3,"BONJOUR LES AMIS"))
print("\n------------------------ \n")

def dechiffrementCesar(cle, string):
	encrypt=""
	for i in string.upper():
		a = ord(i) - (cle%26)
		if a > 32 and a<65:
			encrypt = encrypt + chr(90-(64-a))
		elif ord(i) == 32:
			encrypt += i
		elif ord(i) == 10:
			encrypt += i
		else:
			encrypt = encrypt + chr(a)
	return encrypt

print("dechiffrementCesar function \n")
print(dechiffrementCesar(3,"ERQMRXU OHV DPLV"))
print("\n------------------------ \n")

def chiffrementVigenere( message, cle) :
    encrypt= ""
    compteur=0
    for i,c in enumerate(message) :
    	if c == " ":
    		encrypt += " "
    		compteur += 1
    	else:
	        d = cle[ (i+compteur) % len(cle) ]
	        d = ord(d) - 65
	        encrypt += chr((ord(c)-65+d)%26+65)
    return encrypt

print("chiffrementVigenere function \n")
print(chiffrementVigenere("BONJOUR LES AMIS", "CA"))
print("\n------------------------ \n")

def dechiffrementVigenere( message, cle) :
    encrypt= ""
    compteur=0
    for i,c in enumerate(message) :
    	if c == " ":
    		encrypt += " "
    		compteur += 1
    	else:
	        d = cle[ (i+compteur) % len(cle) ]
	        d = ord(d) - 65
	        d = 26-d
	        encrypt += chr((ord(c)-65+d)%26+65)
    return encrypt

print("dechiffrementVigenere function \n")
print(dechiffrementVigenere("DOPJQUT LGS CMKS", "CA"))
print("\n------------------------ \n")

def chiffreRomain(nb):
	romain = ["M","CM","D","CD","C","XC","L","VL","XL","X","IX","V","IV","I"]
	nombre = [1000,900,500,400,100,90,50,45,40,10,9,5,4,1]
	newNb = ""
	for i in range(len(romain)):
		while nb>= nombre[i]:
			newNb += romain[i]
			nb -= nombre[i]
	return newNb

print("chiffreRomain \n")
print(chiffreRomain(41))
print("\n------------------------ \n")