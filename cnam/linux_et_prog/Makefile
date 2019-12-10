# gcc de base ( creation du binaire )
cc = gcc -c 
# gcc creation executable
cco = gcc -o
# flags pour le gcc -o
ldflags = -lpthread
#flags pour le gcc -c
cflags = -Wall -std=c99
# liste des executables
EXEC = exemple calcul prg4 prg1 sig sig2 sig3

# $@ nom de la cible
# $< nom de la premiere dependance
# $^ liste des dependances
# $? liste des dependances plus recente que la cible
# $* nom du fichier sans suffixe

OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += -D LINUX
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		OSFLAG += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif

cflags += $(OSFLAG)

all: calcul exemple prg4 prg1 sig sig2 sig3

prg4: prg4.o
	@$(cco) $@ $< $(ldflags)

prg4.o: prg4.c
	@$(cc) $< $(cflags)

prg1: prg1.o
	@$(cco) $@ $< $(ldflags)

prg1.o: prg1.c
	@$(cc) $< $(cflags)

calcul: calcul.o
	@$(cco) $@ $< $(ldflags)

calcul.o: calcul.c
	@$(cc) $< $(cflags)

exemple: exemple.o
	@$(cco) $@ $< $(ldflags)

exemple.o: exemple.c
	@$(cc) $< $(cflags)

sig: sig.o
	@$(cco) $@ $< $(ldflags)

sig.o: sig.c
	@$(cc) $< $(cflags)

sig2: sig2.o
	@$(cco) $@ $< $(ldflags)

sig2.o: sig2.c
	@$(cc) $< $(cflags)

sig3: sig3.o
	@$(cco) $@ $< $(ldflags)

sig3.o: sig3.c
	@$(cc) $< $(cflags)

clean:
	@rm -f *.o

mrproper: clean
	clear
	@rm -rf $(EXEC)