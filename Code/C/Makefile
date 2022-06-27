CC = gcc -Wall
EXEC = trajectoireAstre
REP = Fonctions/
MAIN = $(REP)main.c
SRC = $(REP)vecteur.c $(REP)file.c $(REP)planet.c $(REP)point.c
OBJ = $(SRC:.c=.o) 
LIB = $(REP)libAstre.a
HEADER = $(REP)trajectoireAstre.h

all: $(EXEC)

$(EXEC): $(LIB) $(MAIN:.c=.o)
	$(CC) -o $@ $(MAIN:.c=.o) $(LIB) -lm

main.o: $(MAIN) $(HEADER)
	$(CC) -c $(MAIN) 

$(OBJ): $(SRC)
	$(CC) -c $(SRC) 

$(LIB): $(OBJ)
	mv *.o $(REP)
	ar rv $(LIB) $(OBJ)

clean:
	rm $(REP)$(OBJ)

cleanAll:
	rm $(OBJ) $(REP)main.o $(EXEC) $(LIB)
