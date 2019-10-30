#C compiler
CCOMP = gcc

#C linker
LOADER = gcc

# optymalization options
OPT = -O3

# localization of header files
INC = -I ./inc

# libraries
LIB = -L./lib -ltmeas -pthread
#-lrt

# dependancies and commands
myprogram: thread2.o
	$(LOADER) $(OPT) thread2.o -o thread $(LIB)

# how to obtain a file myprogram.o
myprogram.o: thread2.c
	$(CCOMP) -c $(OPT) thread2.c $(INC)

tmeas.o: tmeas.c tmeas.h thread1.c
	$(CCOMP) -c $(OPT) thread2.c $(INC)

clean:
	rm -f *.o
