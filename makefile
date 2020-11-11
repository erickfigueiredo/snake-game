All: Snake.o Game.o Screen.o jogoSnake.o
	g++ Snake.o Game.o Screen.o jogoSnake.o -o teste

Screen.o: Screen.h Screen.cpp
	g++ Screen.h Screen.cpp -c

Snake.o: Screen.h Snake.h Snake.cpp
	g++ Snake.cpp -cpp

Game.o: Screen.h Snake.h Game.h Game.cpp
	g++ Game.cpp -c

jogoSnake.o: Game.h jogoSnake.cpp
	g++ jogoSnake.cpp -c