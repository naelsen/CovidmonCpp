CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
SRC = $(wildcard SRC/*.cc)
TST_DIR = tests/
OBJ = $(SRC:.cc=.o)
LIB = libgames.a
EXEC = jeu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) SRC/main_serveur.cpp  SRC/Serveur.o -o serveur $(LIBFLAGS)
	ar -cr $(LIB) $(OBJ)
	$(CC) $(LIB) -o $@ $(LIBFLAGS)

%.o : %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

play:
	./$(EXEC)

testcase : 
	cd $(TST_DIR) ;  make
	./tests/testcase

clean:
	rm -f $(OBJ) SRC/Serveur.o SRC/main_serveur.o $(EXEC) serveur $(LIB)