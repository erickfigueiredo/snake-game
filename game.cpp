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

//PRECISA TRATAR A DIREÇÃO
bool Game::step(int dr, int dc){
    // Verifica se está indo na posição contrária
    if(!snk.isValid(dr, dc)){
        // Se estiver, inverte a direção para que possa realizar um movimento válido
        dr *= -1;
        dc *= -1;
    }

    // Flag para indicar a existência de comida na coordenada
    bool haveFood = false;

    for(int i = 0; i < 10; i++){
        // Se houver comida
        if(food[i].ativo){
            // Decrementa o tempo ativo
            food[i].time--;

            // Se o tempo estiver chegado ao fim elimina a comida
            if(food[i].time == 0){
                food[i].ativo = false;
            
            // Se as coordenadas de movimento correspondem à da comida, elimina a comida e a Flaf fica TRUE
            }else if(food[i].row == dr && food[i].col == dc){
                haveFood = true;
                food[i].ativo = false;
            }
        }

        //Falta terminar
    }

    const int PIXEL = scr.get(dr, dc);
    
    switch(PIXEL){
        // Movimento em direção a um pixel vazio
        case 0:
            snk.move(dr, dc, haveFood);
            break;
        // Se a coordenada apontar para uma parede ou para a própria Snake
        case 1:
        case 2:
            return false;
        
        // Movimento em direção à comida
        case 3:
            snk.move(dr, dc, haveFood);
            break;
    }
    // Se retorna true, indica que a situação do pixel permitiu um movimento válido
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
                
                //Termina a busca
                break;
            }
        }
}