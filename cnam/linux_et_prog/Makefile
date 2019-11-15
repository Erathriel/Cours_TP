# gcc de base ( creation du binaire )
cc = gcc -c 
# gcc creation executable
cco = gcc -o
# flags pour le gcc -o
ldflags = -lpthread
#flags pour le gcc -c
cflags = -Wall -std=c99
# liste des executables
EXEC = exemple calcul prg4

# $@ nom de la cible
# $< nom de la premiere dependance
# $^ liste des dependances
# $? liste des dependances plus recente que la cible
# $* nom du fichier sans suffixe

all: calcul exemple prg4

prg4: prg4.o
	@$(cco) $@ $< $(ldflags)

prg4.o: prg4.c
	@$(cc) $< $(cflags)

calcul: calcul.o
	@$(cco) $@ $< $(ldflags)

calcul.o: calcul.c
	@$(cc) $< $(cflags)

exemple: exemple.o
	@$(cco) $@ $< $(ldflags)

exemple.o: exemple.c
	@$(cc) $< $(cflags)

clean:
	@rm -f *.o

mrproper: clean
	@rm -rf $(EXEC)