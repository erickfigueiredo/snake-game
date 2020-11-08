/*
    Desenvolvido por: @erickfigueiredo
    Data: 04/11/2020
    Disciplina: Estrutura de Dados
    Professor: Salles Vianna
*/

#include "snake.h"

Snake::Snake(int tam){
    // Recebe o tamanho de Snake e cria "tam" nodos para representar a cobra
    for(int i = 0; i < tam; i++)
        pushBack(0, i);
}

void Snake::pushBack(int row, int col){
    // Verifica se Snake está inicialmente vazia
    if(firstNode == NULL) { 
		firstNode = lastNode = new Node(row, col);
	} else {
        /* Cria um nodo após o lastNode e torna este último nodo criado o novo lastNode, com seu prev 
        apontando para o antigo LastNode */
		lastNode->next = new Node(row, col);
		lastNode->next->prev = lastNode;
		lastNode = lastNode->next;
	}
}

Snake::~Snake(){
    // Método para desalocar a memória alocada para os nodos
    destroy();
}

void Snake::destroy() {
    // Sobrecarga do método destroy() para desalocação recursiva de memória
	destroy(firstNode);
}

void Snake::destroy(iterator current) {
    // Caso base: caso o iterator tenha chegado até o último nodo, retorna 
	if(current == NULL) 
        return;

    /* Passo recursivo: Chama o metodo destroy para o próximo nodo, após passar pelo caso base as 
    iterações da penúltima, para a primeira vão deletando a memória alocada */
	destroy(current->next);
	delete current;
}

int Snake::getLength() const {
    // Chamamos a sobrecarga do método para 
    return getLength(firstNode);
}

int Snake::getLength(iterator current) const{
    // Se passou do último nodo retorna
    if(current == NULL)
        return;
    
    // Retorna 1, contabilizando o nodo atual somado à próxima iteração
    return 1 + getLength(current->next);
}

void Snake::draw(Screen &s, int state) const {
    iterator it = firstNode;
    // Percorre todas os nodos setando as posições na tela
    while(it){
        s.set(it->nRow, it->nCol, state);
        it = it->next;
    }       
}

void Snake::move(int dr, int dc, bool eating){
    // A construção da estrutura de Snake teve início na calda
    if(eating){
        // Se está comendo apenas adiciona um novo nodo na posição em que se moveu
        pushBack(dr + lastNode->nRow, dc + lastNode->nCol);
    }else{
        // Senão precisa mover toda a cobra, move o último elemento da calda para a cabeça

        // Torna o primeiro elemento da lista o último
        lastNode->next = firstNode;
        lastNode->next->prev = lastNode;
        lastNode = lastNode->next;

        //Torna o segundo elemento da lista o primeiro
        firstNode = lastNode->next;
        firstNode->prev = NULL;
        lastNode->next = NULL;

        lastNode->prev->nRow += dr;
        lastNode->prev->nCol += dc;
    }
}

bool Snake::isValid(int dr, int dc) const{
    //Se a direção na linha for igual a ZERO
    if(dr == 0)
        // Verifica um movimento da esquerda para direita e se a cobra mantem esse movimento
        if(lastNode->nCol - lastNode->prev->nCol > 0 && dc > 0)
            return true;
    else
        // Verifica um movimento da direita para esquerda e se a cobra mantem esse movimento
        if(lastNode->nCol - lastNode->prev->nCol < 0 && dc < 0)
            return true;

    return false;
}

Snake::iterator Snake::begin() const {
    // Retorna o primeiro nodo de Snake
    return firstNode;
}

Snake::iterator Snake::end() const {
    // Retorna o último nodo de Snake
    return lastNode;
}

Snake::iterator Snake::next(iterator current) {
    // Retorna o endereço do próximo nodo com relação ao atual
    return current->next;
}

Snake::iterator Snake::prev(iterator current) {
     // Retorna o endereço do nodo anterior ao atual
    return current->prev;
}