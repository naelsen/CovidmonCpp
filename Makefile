CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
SRC = $(wildcard SRC/*.cc)
OBJ = $(SRC:.cc=.o)
EXEC = jeu

all: $(EXEC)

$(EXEC): $(OBJ)
	g++ $(CCFLAGS) -o SRC/Serveur.o -c SRC/Serveur.cpp
	g++ $(CCFLAGS) -o SRC/main_serveur.o -c SRC/main_serveur.cpp
	$(CC) SRC/Serveur.o SRC/main_serveur.o -o serveur -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
	$(CC) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

%.o : %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

play:
	./$(EXEC)

clean:
	# Car serveur est un cpp et pas cc donc il est pas compyer dans les .o
	rm -f $(OBJ) SRC/Serveur.o SRC/main_serveur.o $(EXEC) serveur