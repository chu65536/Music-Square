PREF=./code/
CC=g++
SRC=$(wildcard $(PREF)*.cpp)
OBJ=$(patsubst $(PREF)%.cpp, %.o, $(SRC))

all: compile link run

compile:
	$(CC) -c $(SRC) -ID:\code\libs\c++\SFML-2.5.1\include

link:
	$(CC) -LD:\code\libs\c++\SFML-2.5.1\lib $(OBJ) -o app.exe -lmingw32 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main

run:
	del -f *.o
	./app.exe