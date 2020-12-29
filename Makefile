CC = g++
CCFLAGS = -Wall -Werror -std=c++17 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
SRC = $(wildcard SRC/*.cc)
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

clean:
	# Car serveur est un cpp et pas cc donc il est pas compyer dans les .o
	rm -f $(OBJ) SRC/Serveur.o SRC/main_serveur.o $(EXEC) serveur $(LIB)