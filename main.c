#include <stdio.h>

#include "Dicionario.h"
#include "Operacoes.h"

int main() {
    char operador;
	char chave[1001];
	char conteudo[1001];
	
	Node* dicionario = AlocaEInicializaNode();

	char* nomeArquivoComExtensao;
	char* lugarDoPrimeiroPonto; // para corrigir entrada do arquivo de load e save

    while (1)
	{
		scanf("%c ", &operador);

        switch (operador) {
            case '+':				
				scanf("%s", chave);
				scanf("%s", conteudo); 
				
				InsereResultado resultadoInsercao = InsereDicionario(dicionario, chave, conteudo);
				
				if (resultadoInsercao == Inserido)
					printf ("[chave \"%s\" inserida]\n", chave);
				else
					printf ("[chave \"%s\" sobreescrita]\n", chave);
				
                break;

            case '-':
				scanf("%s", chave);
				
				RemoveResultado resultadoRemove = RemovePar(dicionario, chave);
				
				if (resultadoRemove == NaoEncontrado)
					printf ("[chave \"%s\" nao encontrada]\n", chave);
				else
					printf ("[chave \"%s\" removida]\n", chave);
				
                break;

            case '?':
				scanf("%s", chave);
				
				char* conteudo = BuscaChave(dicionario, chave);
				
				if (!conteudo)
					printf ("[chave \"%s\" nao encontrada]\n", chave);
				else
					printf ("\"%s\": \"%s\"\n", chave, conteudo);
				
                break;

            case 'p':
				ImprimeDicionario(dicionario);
                break;

            case 'w':				
				scanf("%s", chave); // nesse momento chave representa o nome do arquivo
				
				// remove qualquer extensao inserida pelo usuario
				// No exemplo do pdf, insere "churras.dic", remove o ".dic" e insere a extensao ".saida"
				lugarDoPrimeiroPonto = strstr(chave, ".");
				if (lugarDoPrimeiroPonto)
					*lugarDoPrimeiroPonto = '\0';
				
				nomeArquivoComExtensao = strcat(chave, ARQUIVO_EXTENSAO);
				
				SalvaDicionarioEmDisco(dicionario, nomeArquivoComExtensao);
				
				printf("[arquivo %s salvo]\n", chave);
				
                break;

            case 'l':
				scanf("%s", chave); // nesse momento chave representa o nome do arquivo
				
				// remove qualquer extensao inserida pelo usuario
				// No exemplo do pdf, insere "churras.dic", remove o ".dic" e insere a extensao ".saida"
				lugarDoPrimeiroPonto = strstr(chave, ".");
				if (lugarDoPrimeiroPonto)
					*lugarDoPrimeiroPonto = '\0';
				
				nomeArquivoComExtensao = strcat(chave, ARQUIVO_EXTENSAO);
				
				LiberaDicionario(dicionario);
				
				CarregaResultado carregaResultado = CarregaDicionario(dicionario, nomeArquivoComExtensao);
				
				if (carregaResultado == Carregado)
					printf("[arquivo %s carregado]\n", chave);
				else
					printf("[arquivo %s nao encontrado]\n", chave); // TODO: perguntar
				
                break;

            case 'F':
				LiberaDicionario(dicionario);
				
				free (dicionario);
				
                return 0;

            case 'P':
				scanf("%s", chave);
				
				Prefixo(dicionario, chave, 0);
				
                break;
        }
    }

    return 0;
}
