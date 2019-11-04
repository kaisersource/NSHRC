#C compiler
CCOMP = gcc

#C linker
LOADER = gcc

# optymalization options
OPT = -O3

# localization of header files
#INC = -I./folder_name
INC = -I./inc

# libraries
#LIB = -L../folder name -lrt
LIB = -L./lib -ltmeas -fopenmp

# dependancies and commands
main: lab5_2.o
	$(LOADER) $(OPT) lab5_2.o -o lab5_2 $(LIB)

# how to obtain a file myprogram.o
main.o: lab5_2.c
	$(CCOMP) -c $(OPT) lab5_2.c $(INC)

tmeas.o: tmeas.c
	$(CCOMP) -c $(OPT) tmeas.c $(INC) -fopenmp

clean:
	rm -f *.o
