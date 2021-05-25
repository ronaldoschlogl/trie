#ifndef OPERACOES_H_INCLUDED
#define OPERACOES_H_INCLUDED

#include "Dicionario.h"

// OPERACOES ****************

// IMPRIME ******************
// Uma camada antes de realmente iniciar a impressao de maneira recursiva, 
// inserindo as chaves, alocando string na pilha e printando as barras iniciais
void ImprimeDicionario(Node* dicionario);

// Metodo que vai de fato efetuar a impressao, desce na arvore incrementando a index de maneira recursiva procurando por nos que tenham um conteudo
// index: inseri \0, adiciona e sobrepoe caracteres na chave atual, necessario pelo fator de recursividade
// ePrimeiraPalavra: simula um conteudo booleano para diferenciar o primeiro print, que nao possui virgula, do resto
void ImprimiSubArvore(Node* raiz, char* chaveAtual, int index, int* ePrimeiraPalavra);

// Para satisfazer os requisitos de formato de impressao
void ImprimeParComVirgula (char* chave, char* conteudo);
void ImprimePar(char* chave, char* conteudo);


// INSERE *******************
typedef enum 
{
	Inserido,
	Sobreescrito
}InsereResultado;

// desce recursivamente na arvore incrementando o ponteiro da chave e criando os filhos nao existentes no caminho
// Ao chegar no final da chave (\0) cria ou sobreescreve o conteudo no node.
InsereResultado InsereDicionario(Node* subArvore, char* chave, char* conteudo);


// BUSCA ********************
// desce recursivamente na arvore incrementando o ponteiro da chave
// Caso alguma letra no caminho nao tenha filho, retorna NULL
// Caso chegue no final da palavra retorna o conteudo
char* BuscaChave(Node* subArvore, char* chave);


// REMOVE *******************
typedef enum
{
	Removido,
	NaoEncontrado
}RemoveResultado;

// Camada usada para direcionar para outros metodos, gera uma arvore limpa apos o 
// Verifica se o no existe chamando BuscaChave()
// Caso a chave exista directiona para RemoveSubArvore()
RemoveResultado RemovePar(Node* dicionario, char* chave);

// desce arvore recursivamente procurando pela chave (tem a garantia de q ela exista, pois o RemovePar() garante isso)
// Remove o node e sobe removendo todos os correspondentes nos vazios no caminho de volta
int RemoveSubArvore(Node* subArvore, char* chave);


// SALVA ********************
// Camada que abre o arquivo, inicializa uma chave na pilha e directioca para SalvaParesNoDisco()
void SalvaDicionarioEmDisco(Node* dicionario, char* nomeArquivo);

// desce na arvore recursivamente pela esquerda, alterando a chaveAtual usando o indice
// Quando encontra um no com conteudo, insere o \0 na chave e insere o par no arquivo
void SalvaParesNoDisco(Node* subArvore, FILE* fp, char* chaveAtual, int index);


// CARREGA ******************
typedef enum
{
	ArquivoNaoEncontrado,
	Carregado
}CarregaResultado;

// Nao ficou especificado no trabalho oq fazer caso o arquivo nao exista no disco, tratei usando o enum acima
// Passa pelo arquivo lendo os pares que foram salvos em linhas e adicionando eles por meio do InsereDicionario()
CarregaResultado CarregaDicionario(Node* dicionario, char* nomeArquivo);


// LIBERA MEMORIA ***********
// desce na arvore recursivamente pela esquerda subindo e liberando os nos
void LiberaDicionario(Node* raiz);


// PREFIXO ******************
// desce ate encontrar a subArvore cuja letra atual da chave representa a ultima letra do prefixo, passando a mesma para ImprimeDicionarioComPrefixo()
// Caso a palavra nao exista no dicionario, retorna nulo para ImprimeDicionarioVazio();
void Prefixo(Node* subArvore, char* prefixo, int index);

// Muito semelhante ao ImprimeDicionario(), mas o index vem do Prefixo() indicando o tamanho da chave passada como prefixo
// Tambem vem do prefixo a subArvore letra atual representa a ultima letra do prefixo, agora apenas redireciona para ImprimiSubArvore() 
// com a subArvore correta
void ImprimeDicionarioComPrefixo(Node* dicionario, char* prefixo, int index);

// Quando o prefixo nao consegue descer ate a ultima letra do prefixo
void ImprimiDicionarioVazio();

#endif