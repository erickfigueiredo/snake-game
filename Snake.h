#ifndef SNAKE_H
#define SNAKE_H

#include "Screen.h"

class Snake;

class Node{
    // Declaramos Snake como friend de Node
    friend class Snake;
    public:
        int getRow() {return nRow;}
        int getCol() {return nCol;}
        
    private:
        // Construtor
        Node(int r, int c): nRow(r), nCol(c), prev(nullptr), next(nullptr){}

        // Membros de dados
        int nRow, nCol;
        Node *prev, *next;
};

class Snake{
    public:
        // Para abstrair o iterador, vamos utilizar typedef
        typedef Node *iterator;

        // Construtores
        Snake(int tam);
        Snake(const Snake &other);

        // Destrutor
        ~Snake();

        // Getter
        int getLength() const;
        
        // operador
        Snake &operator=(const Snake &other);

        void draw(Screen &s, int state) const;
        void move(int dr, int dc, bool eating);

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

#endif //! SNAKE_H