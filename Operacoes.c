#include "Operacoes.h"


// IMPRIME ******************
void ImprimeDicionario(Node* dicionario)
{
    char chave[1001];
	int ePrimeiraPalavra = 1;

	printf("{");

	ImprimiSubArvore(dicionario, chave, 0, &ePrimeiraPalavra);

	printf("}\n");
}

void ImprimiSubArvore(Node* raiz, char* chaveAtual, int index, int* ePrimeiraPalavra)
{
	if (raiz->conteudo != NULL)
	{
		chaveAtual[index] = '\0';
		
		if (*ePrimeiraPalavra)
		{
			ImprimePar(chaveAtual, raiz->conteudo);

			*ePrimeiraPalavra = 0;
		}
		else
			ImprimeParComVirgula(chaveAtual, raiz->conteudo);
	}
	
	int i = 0;
    for (i = 0; i < FILHOS_NODE; ++i) {
        if (raiz->proximo[i] != NULL)
		{
			chaveAtual[index] = i + 'a';
			
			ImprimiSubArvore(raiz->proximo[i], chaveAtual, index+1, ePrimeiraPalavra);
		}
    }
}

void ImprimeParComVirgula (char* chave, char* conteudo)
{
	printf(", ");
	
	ImprimePar(chave, conteudo);
}

void ImprimePar(char* chave, char* conteudo)
{
	printf("\"%s\":\"%s\"", chave, conteudo);
}


// INSERE *******************
InsereResultado InsereDicionario(Node* subArvore, char* chave, char* conteudo)
{
	// Final da chave, adiciona ou sobreescreve conteudo
	if (!*chave)
	{		
		InsereResultado resultado = Inserido;
		
		if (subArvore->conteudo)
		{
			resultado = Sobreescrito;
			
			// Apaga o conteudo do no atual
			free(subArvore->conteudo);
			subArvore->conteudo = NULL;
		}
		
		subArvore->conteudo = AlocaECopiaconteudo(conteudo);
		
		return resultado;
	}
	
	int index = *chave - 'a';	
	if (!subArvore->proximo[index])
		subArvore->proximo[index] = AlocaEInicializaNode();
	
	return InsereDicionario(subArvore->proximo[index], ++chave, conteudo);
}


// BUSCA ********************
char* BuscaChave(Node* subArvore, char* chave)
{
	if (!*chave)
		return subArvore->conteudo;
	
	int index = *chave - 'a';
	if (subArvore->proximo[index])
		return BuscaChave(subArvore->proximo[index], ++chave);
	
	return NULL;
}


// REMOVE *******************
RemoveResultado RemovePar(Node* dicionario, char* chave)
{
	char* conteudo = BuscaChave(dicionario, chave);
	
	if (!conteudo)
		return NaoEncontrado;
	
	RemoveSubArvore(dicionario, chave);
	
	return Removido;
}

int RemoveSubArvore(Node* subArvore, char* chave)
{
	if (!*chave)
	{
		free(subArvore->conteudo);
		subArvore->conteudo = NULL;
		
		return NodeEstaVazio(subArvore);
	}
	
	int index = *chave - 'a';
	int oFilhoEVazio = RemoveSubArvore(subArvore->proximo[index], ++chave);
		
	if (oFilhoEVazio)
	{		
		free(subArvore->proximo[index]);
		subArvore->proximo[index] = NULL;
		
		// Retorna se eu sou um node vazio
		return NodeEstaVazio(subArvore);
	}
	
	// Caso o filho nao seja vazio nao pode deletar mais nenhum dos pais no caminho de volta
	return 0;
}


// SALVA ********************
void SalvaDicionarioEmDisco(Node* dicionario, char* nomeArquivo)
{	
	FILE* fp = fopen(nomeArquivo, "w+");
	
	char chaveBuffer[1001];
	
	SalvaParesNoDisco(dicionario, fp, chaveBuffer, 0);
	
	fclose(fp);
}

void SalvaParesNoDisco(Node* subArvore, FILE* fp, char* chaveAtual, int index)
{
	if (subArvore->conteudo)
	{
		chaveAtual[index] = '\0';
		
		fprintf(fp, "%s %s\n", chaveAtual, subArvore->conteudo);
	}
	
	int i = 0;
	for (i = 0; i < FILHOS_NODE; i++)
	{
		if (subArvore->proximo[i])
		{
			chaveAtual[index] = i + 'a';
			SalvaParesNoDisco(subArvore->proximo[i], fp, chaveAtual, index + 1);
		}
	}
}


// CARREGA ******************
CarregaResultado CarregaDicionario(Node* dicionario, char* nomeArquivo)
{
	FILE* fp = fopen(nomeArquivo, "r");
	
	if (!fp)
		return ArquivoNaoEncontrado;
	
	char chave[1001];
	char conteudo[1001];
	
	while (!feof(fp))
	{
		int numeroDeLeituras = fscanf(fp, "%s %s", chave, conteudo);
		
		if (numeroDeLeituras != 2)
			break;
		
		InsereDicionario(dicionario, chave, conteudo);
	}
	
	fclose(fp);
	
	return Carregado;
}

// LIBERA MEMORIA ***********
void LiberaDicionario(Node* raiz)
{
	// Caminha ate a folha mais da esquerda
	int i = 0;
	for (i = 0; i < FILHOS_NODE; i++)
		if (raiz->proximo[i])
		{
			LiberaDicionario(raiz->proximo[i]);
			
			// Nesse momento o conteudo do filho já foi deletado, apenas deleta o no do filho
			free(raiz->proximo[i]);
			raiz->proximo[i] = NULL;
		}
		
	
	// Volta limpando
	if (raiz->conteudo)
	{
		free(raiz->conteudo);
		raiz->conteudo = NULL;
	}
}


// PREFIXO ******************
void Prefixo(Node* subArvore, char* prefixo, int pos)
{
	if (!prefixo[pos])
	{
		ImprimeDicionarioComPrefixo(subArvore, prefixo, pos);
		
		return;
	}
	
	int index = prefixo[pos] - 'a';
	if (subArvore->proximo[index])
		Prefixo(subArvore->proximo[index], prefixo, pos + 1);
	else
		ImprimiDicionarioVazio();
}

void ImprimeDicionarioComPrefixo(Node* dicionario, char* prefixo, int pos)
{
	int ePrimeiraPalavra = 1;

	printf("{");

	ImprimiSubArvore(dicionario, prefixo, pos, &ePrimeiraPalavra);

	printf("}\n");
}

void ImprimiDicionarioVazio()
{
	printf ("{}\n");
}