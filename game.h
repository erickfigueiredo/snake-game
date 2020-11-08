#ifndef GAME_H
#define GAME_H

#include "screen.h"
#include "snake.h"

// Struct para armazenar os dados de Food
struct Food{
    int row, col, time;
    bool ativo = false;
};

class Game{
    public:
        // Construtores
        Game(int h, int w, int tam): snk(tam), scr(h, w){}

        //Destrutor
        ~Game();

        // Getters
        const Screen& getScreen() const;
        int getNumFood() const;

        // Métodos de manipulação de GAME
        bool step(int dr, int dc);
        void addFood(int r, int c, int ttl);

    private:
        Snake snk;
        Screen scr;
        Food food[10];
        int nFood = 0;
};

#endif //! GAME_H