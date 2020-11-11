/*
    Desenvolvido por: @erickfigueiredo
    Data: 04/11/2020
    Disciplina: Estrutura de Dados
    Professor: Salles Vianna
*/

#include "game.h"

Game::~Game(){}

const Screen& Game::getScreen() const{
    // Retorna uma referência constante da tela
    return scr;
}

int Game::getNumFood() const{
    // Retorna o número de comidas no mapa
    return nFood;
}

bool Game::step(int dr, int dc){
    // Desenha a cobra na tela
    snk.draw(scr, 1);

    // Verifica a validade do movimento
    if(lstDRow == -2){
        lstDRow = dr;
        lstDCol = dc;
    }else{
        // Se não for válido, repete o anterior 
        if(dr == -lstDRow && dc == -lstDCol){
            dr = lstDRow;
            dc = lstDCol;
        }
    }

    int auxRow = snk.end()->getRow()+dr;
    int auxCol = snk.end()->getCol()+dc;

    // Escolhe a ação de acordo com o próximo pixel, calculado a partir do movimento da cabeça
    switch(scr.get(auxRow, auxCol)){
        case 0:
            scr.set(snk.begin()->getRow(), snk.begin()->getCol(), 0);
            snk.move(auxRow, auxCol, false);
            break;
        case 1:
        case 2:
            // Snake exerceu um movimento inválido
            return false;
        case 3:
            snk.move(auxRow, auxCol, true);
            break;
    }

    for(int i = 0; i < 10; i++){
        // Se houver comida
        if(food[i].ativo){
            // Decrementa o tempo ativo
            food[i].time--;

            // Se o tempo estiver chegado ao fim elimina a comida
            if(food[i].time == 0 || (food[i].row == auxRow && food[i].col == auxCol))
                food[i].ativo = false;
        }
    }
    
    return true;
}

void Game::addFood(int r, int c, int ttl){
    // Verifica se a coordenada no mapa está vazia
    if(scr.get(r, c) == 0)
        // Se estive, procura o slot vazio mais próximo
        for(int i = 0; i < 10; i++){
            if(!food[i].ativo){
                // Torna o slot ativo
                food[i].ativo = true;

                // Atribui os valores
                food[i].row = r;
                food[i].col = c;
                food[i].time = ttl;
                
                // Incrementa o número de Food
                nFood++;

                //Desenha a comida na tela
                scr.set(r, c, 3);
                
                //Termina a busca
                break;
            }
        }
}

// --- FIM