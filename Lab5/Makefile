#C compiler
CCOMP = gcc

#C linker
LOADER = gcc
OPENMP = -fopenmp
# optymalization options
#OPT = -O3

# localization of header files
#INC = -I./folder_name
INC = -I./inc

# libraries
#LIB = -L../folder name -lrt
LIB = -L./lib $(OPENMP)

# dependancies and commands
lab5: lab5.o
	$(LOADER) lab5.o -o lab5 $(LIB)

# how to obtain a file myprogram.o
lab5.o: lab5.c
	$(CCOMP) -c lab5.c $(INC) $(OPENMP)



clean:
	rm -f *.o
