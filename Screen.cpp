/*
    Desenvolvido por: @erickfigueiredo
    Data: 04/11/2020
    Disciplina: Estrutura de Dados
    Professor: Salles Vianna
*/

#include "Screen.h"

Screen::Screen(int h, int w){
    height = h;
    width = w;

    // Aloca a memória necessária para representar a tela do game
    dataHeight = new int[width](); // O () ao final da alocação aciona o construtor padrão para as posições alocadas
    data = new int *[width];

    for(int i = 0; i < width; i++)
        data[i] = new int[0];
}

Screen::Screen(const Screen &other){
    // Chama o operador de atribuição
    *this = other;
}

Screen::~Screen(){
    //Desaloca a memória necessária para representar a tela do game
    for(int i = 0; i < width; i++)
        delete[] data[i];

    delete []data;
    delete []dataHeight;
}

int Screen::getWidth() const{
    //retorna o comprimento da tela
    return width;
}

int Screen::getHeight() const{
    //Retorna a altura da tela
    return height;
}

int Screen::get(int r, int c) const{
    //Verifica se as coordenada está dentro dos limites da tela, caso negativo, retorna WALL
    if(c < width && r < height && r >= 0 && c >= 0){

        //Caso a coordenada esteja dentro dos limites da tela verifica o estado do pixel

        //Se em dataHeight o valor da coluna for ZERO, ou row for maior que o pixel mais alto da coluna retorna EMPTY
        if(dataHeight[c] == 0 || r > dataHeight[c]-1)
            return Screen::EMPTY;
        
        //Senão o valor está alocado em data e pode ser retornado com o acesso à posição de memória
        switch(data[c][r]){
            case 0: 
                return Screen::EMPTY;
            case 2: 
                return Screen::SNAKE;
            case 3: 
                return Screen::FOOD;
        }
    }

    return Screen::WALL;
}

void Screen::set(int r, int c, int val){
     //Se o valor for EMPTY e a posição não tiver sido alocada, não faz nada
    if((val == Screen::EMPTY) && (dataHeight[c] == 0 || r > dataHeight[c]-1))
        return;

    //Se a posição estiver dentro do espaço já alocado
    if(r < dataHeight[c]){
        //Se a posição a ser inserida for a do topo e o valor for zero, precisará diminuir o espaço alocado
        if(dataHeight[c]-1 == r && val == Screen::EMPTY){
            //verifica se há um novo topo após retirar o elemento que estava lá
            int newTop = -1;

            for(int i = 0; i < r; i++)
                if(data[c][i] != Screen::EMPTY)
                    newTop = i;

            //Se tiver alguma posição não vazia vamos realocar até ela
            if(newTop != -1){
                //Copia os elementos até o novo topo
                int *copyLine = new int[newTop+1];

                for(int i = 0; i < newTop+1; i++)
                    copyLine[i] = data[c][i];
                
                //Deleta as linhas da coluna data[c]
                delete []data[c];

                //Retorna os elementos para coluna de Screen
                data[c] = copyLine;
            
            //Se o novo topo for igual a -1, signifca que todos os outros elementos da linha depois do retirado são vazios
            }else{
                //Deleta as linhas da coluna data[c]
                delete []data[c];

                data[c] = new int[0];
            }
            //Atualiza dataHeight
            dataHeight[c] = newTop + 1;
        }else{
            data[c][r] = val;
        }
    //Se a posição a ser inserida for maior que o último valor alocado, realiza uma realocação
    }else{
        //Faz a copia de todas as linhas da coluna
        int *copyLine = data[c];

        //Aloca as novas linhas da coluna
        data[c] = new int [r+1]();

        //Copia os valores novamente
        for(int i = 0; i < dataHeight[c]; i++)
            data[c][i] = copyLine[i];

        //Deleta a copia
        delete []copyLine;

        //Adiciona o novo valor
        data[c][r] = val;

        //Atualiza o valor de dataHeight
        dataHeight[c] = r+1;
    }
}

Screen &Screen::operator=(const Screen &other){
    // Autoatribuição retorna o próprio objeto
    if(this == &other)
        return *this;

    // Deleta o objeto atual
    for(int i = 0; i < width; i++)
        delete[] data[i];

    delete []data;
    delete []dataHeight;

    // Faz a cópia de other para this
    height = other.getHeight();
    width = other.getWidth();

    //Aloca a memória necessária para representar a tela do game
    dataHeight = new int[width](); // O () ao final da alocação aciona o construtor padrão para as posições alocadas
    data = new int *[width];

    for(int i = 0; i < width; i++){
        dataHeight[i] = other.dataHeight[i];
        data[i] = new int[dataHeight[i]];
        
        for(int j = 0; j < dataHeight[i]; j++)
            data[i][j] = other.data[i][j];
    }

    return *this;
}

// --- FIM