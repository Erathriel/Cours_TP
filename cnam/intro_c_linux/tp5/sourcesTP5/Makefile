# gcc de base ( creation du binaire )
cc = gcc -c 
# gcc creation executable
cco = gcc -o
# flags pour le gcc -o
ldflags = -lpthread
#flags pour le gcc -c
cflags = -Wall -std=c99
# liste des executables
EXEC = 2th Echec_thread 4th Trois_Thread mult

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

# commande qui fonctionne pour compiler selon l'os !
#gcc -o Echec_thread Echec_thread.c -Wall -std=c99 -D LINUX -lpthread

all: 2th Echec_thread 4th Trois_Thread mult

2th: 2th.o
	@$(cco) $@ $< $(ldflags)

2th.o: 2th.c
	@$(cc) $< $(cflags)

Echec_thread: Echec_thread.o
	@$(cco) $@ $< $(ldflags)

Echec_thread.o: Echec_thread.c
	@$(cc) $< $(cflags)

4th: 4th.o
	@$(cco) $@ $< $(ldflags)

4th.o: 4th.c
	@$(cc) $< $(cflags)

Trois_Thread: Trois_Thread.o
	@$(cco) $@ $< $(ldflags)

Trois_Thread.o: Trois_Thread.c
	@$(cc) $< $(cflags)

mult: mult.o
	@$(cco) $@ $< $(ldflags)

mult.o: mult.c
	@$(cc) $< $(cflags)

clean:
	@rm -f *.o

mrproper: clean
	@rm -rf $(EXEC)
