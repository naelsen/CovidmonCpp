CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
SRC = $(wildcard SRC/*.cc)
TST_DIR = tests/
OBJ = $(SRC:.cc=.o)
OBJ_EXEC = $(filter-out SRC/main_serveur.o SRC/Serveur.o , $(OBJ))
LIB = libgames.a
EXEC = jeu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) SRC/main_serveur.cc  SRC/Serveur.o -o serveur $(LIBFLAGS)
	ar -cr $(LIB) $(OBJ_EXEC)
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
cleantest:
	cd $(TST_DIR) ; make clean
distclean : clean cleantest