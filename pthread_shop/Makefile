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
LIB = -L./lib -ltmeas -lpthread

# dependancies and commands
main: shop.o
	$(LOADER) $(OPT) shop.o -o shop $(LIB)

# how to obtain a file myprogram.o
main.o: shop.c
	$(CCOMP) -c $(OPT) shop.c $(INC)

tmeas.o: tmeas.c 
	$(CCOMP) -c $(OPT) tmeas.c $(INC)

clean:
	rm -f *.o
