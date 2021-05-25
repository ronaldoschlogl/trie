#include "Dicionario.h"

Node* AlocaEInicializaNode()
{
	Node* node = (Node*)malloc(sizeof(Node));
	
	node->conteudo = NULL;
	
	int i = 0;
	for (i = 0; i < FILHOS_NODE; i++)
		node->proximo[i] = NULL;
	
	return node;
}

char* AlocaECopiaconteudo(char* conteudo)
{
	char* conteudoAlocado = (char*)malloc(strlen(conteudo)+1);
	strcpy(conteudoAlocado, conteudo);
	
	return conteudoAlocado;
}

int NodeEstaVazio(Node* node)
{
	if (node->conteudo)
		return 0;
	
	int i = 0;
	for (i = 0; i < FILHOS_NODE; i++)
		if (node->proximo[i])
			return 0;
		
	return 1;
}
