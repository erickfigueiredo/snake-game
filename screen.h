#ifndef SCREEN_H
#define SCREEN_H

class Screen {
    public:
        //construtor
        Screen(int h, int w);
        
        //Destrutor
        ~Screen();

        //Getters
        int getWidth() const;
        int getHeight() const;
        int get(int r, int c) const;

        //Setters
        void set(int r, int c, int val);

        int const EMPTY = 0, WALL = 1, SNAKE = 2, FOOD = 3;
    private:
        int height, width;
        int **data = NULL, *dataHeight = NULL;
};

#endif //! Fim de SCREEN_H