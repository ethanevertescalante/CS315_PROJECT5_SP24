
game.x:  main.o getChar.o ScreenDS.o Worm.o
	g++ -ggdb -o game.x main.o getChar.o ScreenDS.o Worm.o -lcurses -ltermcap

main.o: main.cpp
	g++ -c -ggdb main.cpp -o main.o

getChar.o: getChar.cpp 
	g++ -c -ggdb getChar.cpp -o getChar.o

ScreenDS.o: ScreenDS.cpp
	g++ -c -ggdb ScreenDS.cpp -o ScreenDS.o

Worm.o: Worm.cpp
	g++ -c -ggdb Worm.cpp -o Worm.o

clean:
	/bin/rm -f game.x main.o getChar.o ScreenDS.o screen.o Worm.o *~
