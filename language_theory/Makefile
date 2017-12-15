CC = cc
CFLAGS = -Wall -O2 -g -Iinclude -std=c99

CXX = c++
CXXFLAGS = -Wall -O2 -g -Iinclude -Itests -Itests/include

SRCDIR = src

SRCALGO_OBJ = $(SRCDIR)/fa.o $(SRCDIR)/testfa.o

RUNTESTS_OBJ = tests/src/gtest-all.o tests/faTestUnit.o run_tests.o

all: libalgo.a compil test

test: run_tests
	./run_tests

libalgo.a: $(SRCALGO_OBJ)
	ar cru $@ $(SRCALGO_OBJ)

run_tests: $(RUNTESTS_OBJ) libalgo.a
	$(CXX) -o $@ $(RUNTESTS_OBJ) -L. -lalgo -lpthread

clean:
	rm -f $(SRCALGO_OBJ)
	rm -f $(RUNTESTS_OBJ)

mrproper: clean
	rm -f libalgo.a
	rm -f run_tests
	rm -f testfa

ARCHIVEDIR = biblialgo

archive: clean
	test "$(SRCDIR)" = "lib"
	rm -rf $(ARCHIVEDIR)
	mkdir $(ARCHIVEDIR)
	cp -r include lib tests Makefile run_tests.cc $(ARCHIVEDIR)
	tar zcvf $(ARCHIVEDIR).tar.gz $(ARCHIVEDIR)
	rm -rf $(ARCHIVEDIR)

compil: 
	gcc src/fa.o src/testfa.o -o testfa 