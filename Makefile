
game.x:  main.o getChar.o
	g++ -ggdb -o game.x main.o getChar.o -lcurses -ltermcap

main.o: main.cpp
	g++ -c -ggdb main.cpp -o main.o

getChar.o: getChar.cpp 
	gcc -c -ggdb getChar.cpp -o getChar.o

clean:
	/bin/rm -f game.x main.o getChar.o *~
