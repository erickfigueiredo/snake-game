#ifndef SCREEN_H
#define SCREEN_H

class Screen {
    public:
        // Construtores
        Screen(int h, int w);
        Screen(const Screen &other);

        // Destrutor
        ~Screen();

        // Getters
        int getWidth() const;
        int getHeight() const;
        int get(int r, int c) const;

        // Setters
        void set(int r, int c, int val);

        // Operador
        Screen &operator =(const Screen &other);

        int const EMPTY = 0, WALL = 1, SNAKE = 2, FOOD = 3;
    private:
        int height, width;
        int **data = NULL, *dataHeight = NULL;
};

#endif //! SCREEN_H