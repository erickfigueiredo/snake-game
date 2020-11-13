All: Screen.o Snake.o Game.o jogoSnakeAvaliaComandos.o
		g++ Screen.o Snake.o Game.o jogoSnakeAvaliaComandos.o -o jogo

Screen.o: Screen.h Screen.cpp 
		g++ Screen.cpp -c

Snake.o: Screen.h Snake.h Snake.cpp
		g++ Snake.cpp -c

Game.o: Screen.h Snake.h Game.h Game.cpp 
		g++ Game.cpp -c

jogoSnakeAvaliaComandos.o: Game.h jogoSnakeAvaliaComandos.cpp
		g++ jogoSnakeAvaliaComandos.cpp -c
