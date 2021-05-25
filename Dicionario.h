#ifndef DICIONARIO_H_INCLUDED
#define DICIONARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h> // strcpy 

#define FILHOS_NODE 26 // cada folha tem numero de letras do alfabeto de filhos
#define ARQUIVO_EXTENSAO ".saida\0"

typedef struct Node{
    char* conteudo;

    struct Node* proximo[FILHOS_NODE];
}Node;

Node* AlocaEInicializaNode();

char* AlocaECopiaconteudo(char* conteudo);

// Verifica se o no esta vazio ou nao. Um no vazio ? um no que nao possui conteudo e nenhum filho
// 0: NAO esta vazio
// 1: Esta vazio
int NodeEstaVazio(Node* node);

#endif