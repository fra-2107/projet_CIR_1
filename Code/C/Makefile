CC = gcc -Wall
EXEC = trajectoireAstre
MAIN = main.c
SRC = vecteur.c ecriture.c planet.c
OBJ = $(SRC:.c=.o) 
LIB = libAstre.a
HEADER = trajectoireAstre.h

all: $(EXEC)

$(EXEC): $(LIB) $(MAIN:.c=.o)
	$(CC) -o $@ $(MAIN:.c=.o) $(LIB) -lm

main.o: $(MAIN) $(HEADER)
	$(CC) -c $(MAIN) 

$(OBJ): $(SRC)
	$(CC) -c $(SRC) 

$(LIB): $(OBJ)
	ar rv $(LIB) $(OBJ)

clean:
	rm $(OBJ)

cleanAll:
	rm $(OBJ) main.o $(EXEC) $(LIB)