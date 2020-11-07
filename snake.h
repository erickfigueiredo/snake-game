#ifndef SNAKE_H
#define SNAKE_H

#include "screen.h"

class Snake;
class Node{
    // Declaramos Snake como friend de 
    friend class Snake;
    private:
        // Construtor
        Node(int r, int c): nRow(r), nCol(c), next(NULL), prev(Null){}

        // Membros de dados
        int nRow, nCol;
        Node *next, *prev;
};

class Snake{
    public:
        // Para abstrair o iterador, vamos utilizar typedef
        typedef Node *iterator;

        // Construtor
        Snake(int tam);

        // Destrutor
        ~Snake();

        // Getter
        int getLength() const;
        

        void draw(Screen &s, int state) const;
        void move(int dr, int dc, bool eating); //Precisa ter complexidade O(1)

        // Métodos de manipulação da Lista Snake
        void pushBack(int row, int col);                                                     
        iterator begin() const;
        iterator end() const;

        iterator  next(iterator current);
        iterator  prev(iterator current);

    private:
        int getLength(iterator current) const;
        void destroy();
        void destroy(iterator current);
        
        Node *firstNode, *lastNode;
};

#endif