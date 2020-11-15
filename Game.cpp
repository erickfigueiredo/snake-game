/*
    Desenvolvido por: @erickfigueiredo
    Data: 04/11/2020
    Disciplina: Estrutura de Dados
    Professor: Salles Vianna
*/

#include "Game.h"

Game::Game(int h, int w, int tam) : scr(h, w), snk(tam){
    // Desenha a cobra na tela
    snk.draw(scr, 2);
}

const Screen& Game::getScreen() const{
    // Retorna uma referência constante da tela
    return scr;
}

int Game::getNumFood() const{
    // Retorna o número de comidas no mapa
    return nFood;
}

bool Game::step(int dr, int dc){
    
    // Verifica a validade do movimento
    if(lastMRow == -2){
        lastMRow = dr;
        lastMCol = dc;
    }else{
        //Indica que o movimento anterior e o atual foram na vertical
        if(dr && lastMRow){
            // Se diferirem repete o anterior
            if(dr != lastMRow)
                dr = lastMRow;
        
        // Indica que o movimento anterior e o atual foram na horizontal
        }else if(dc && lastMCol){
            // Se diferirem repete o anterior 
            if(dc != lastMCol)
                dc = lastMCol;
        
        // Significa que o movimento anterior e o atual não estão no mesmo sentido
        }else{
            lastMRow = dr;
            lastMCol = dc;
        }
    }

    int auxRow = snk.end()->getRow()+dr;
    int auxCol = snk.end()->getCol()+dc;

    for(int i = 0; i < 10; i++){
        // Se houver comida
        if(food[i].ativo){
            // Se o tempo estiver chegado ao fim elimina a comida
            if(food[i].time == 0){
                food[i].ativo = false;
                scr.set(food[i].row, food[i].col, 0);
            }else if(food[i].row == auxRow && food[i].col == auxCol){
                food[i].ativo = false;
            }
            // Decrementa o tempo ativo
            food[i].time--;
        }
    }

    // Escolhe a ação de acordo com o próximo pixel, calculado a partir do movimento da cabeça
    switch(scr.get(auxRow, auxCol)){
        case 0:
            scr.set(snk.begin()->getRow(), snk.begin()->getCol(), 0);
            snk.move(dr, dc, false);
            break;
        case 1:
        case 2:
            // Snake exerceu um movimento inválido
            return false;
        case 3:
            scr.set(snk.begin()->getRow(), snk.begin()->getCol(), 0);
            snk.move(dr, dc, true);
            //Define a posição que estava a comida como EMPTY
            scr.set(auxRow, auxCol, 0);
            break;
    }

    snk.draw(scr, 2);

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

//! FIM