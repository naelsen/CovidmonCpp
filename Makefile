CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
SRC = $(wildcard SRC/*.cc)
OBJ = $(SRC:.cc=.o)
EXEC = prog

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) serveur.cc -o serveur -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
	$(CC) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

%.o : %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

play:
	./$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)