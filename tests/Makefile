CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
SRC= $(wildcard ../SRC/*.cc)
OBJ= $(SRC:.cc=.o)
TST= $(wildcard *.cc)
OBJ_TEST = $(filter-out ../SRC/main.o, $(OBJ)) $(TST:.cc=.o)

testcase : $(OBJ_TEST) 
	$(CC) $(CCFLAGS) $(OBJ_TEST)  -o $@ $(LIBFLAGS)

%.o: %.cc
	$(CC) $(CCFLAGS) -I../ -o $@ -c $<

clean :
	rm -f $(OBJ_TEST) testcase
