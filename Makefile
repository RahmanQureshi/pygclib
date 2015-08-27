CC = i686-pc-mingw32-gcc
INCL = ./include
SRC = source/tester.c
LL = ./lib/ -lgclibo -lgclib
DLL = source/dll

all: tester

tester: tester.exe

tester.exe: source/tester.c
	mkdir -p bin
	$(CC) source/tester.c -I$(INCL) -L$(LL) -o bin/tester.exe
	cp $(DLL)/* bin