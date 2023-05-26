PREF=./code/

all: compile link run

compile:
	g++ -c $(PREF)code.cpp -ID:\code\libs\c++\SFML-2.5.1\include

link:
	g++ -LD:\code\libs\c++\SFML-2.5.1\lib code.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main

run:
	./app.exe
	del -f code.o