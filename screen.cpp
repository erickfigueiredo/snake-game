/*
    Desenvolvido por: @erickfigueiredo
    Data: 04/11/2020
    Disciplina: Estrutura de Dados
    Professor: Salles Vianna
*/

#include "screen.h"

Screen::Screen(int h, int w){
    height = h;
    width = w;

    //Aloca a memória necessária para representar a tela do game
    dataHeight = new int[width];
    data = new int *[width];

    for(int i = 0; i < width; i++){
        dataHeight[i] = 0;
        data[i] = new int[0];
    }
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
    //Verifica se as coordenada está fora dos limites da tela, caso afirmativo, returna WALL
    if(c >= width || r >= height || r < 0 || c < 0)
        return WALL;

    //Caso a coordenada esteja dentro dos limites da tela verifica o estado do pixel

    //Se em dataHeight o valor da coluna for ZERO, ou row for maior que o pixel mais alto da coluna retorna EMPTY
    if(dataHeight[c] == 0 || r > dataHeight[c]-1)
        return EMPTY;
    
    //Senão o valor está alocado em data e pode ser retornado com o acesso à posição de memória
    switch(data[c][r]){
        case 0: return EMPTY;
        case 2: return SNAKE;
        case 3: return FOOD;
    }
}

void Screen::set(int r, int c, int val){
     //Se o valor for EMPTY e a posição não tiver sido alocada, não faz nada
    if((val == EMPTY) && (dataHeight[c] == 0 || r > dataHeight[c]-1))
        return;

    //Se a posição estiver dentro do espaço já alocado
    if(dataHeight[c]-1 <= r){
        //Se a posição a ser inserida for a do topo e o valor for zero, precisará diminuir o espaço alocado
        if(dataHeight[c]-1 == r && val == EMPTY){
            //verifica se há um novo topo após retirar o elemento que estava lá
            int newTop = -1;

            for(int i = 0; i < r; i++)
                if(i !=EMPTY)
                    newTop = i;

            //Se tiver alguma posição não vazia vamos realozar até ela
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
        data[c] = new int [r+1];

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