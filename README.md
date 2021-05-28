# Arvore Trie em C
O trabalho consiste na implementação em C de um programa que manipula um dicionário (conjunto de pares
<chave, conteúdo>) de chaves do tipo string e conteúdos do tipo string, usando como estrutura base uma
árvore de prefixos (trie).
<br>
Com um dicionário inicialmente vazio, o programa deve ler e processar uma sequência de comandos do
usuário. Cada comando pode ser:
<br>
-> + chave conteudo: insere o par <chave,conteudo>, e imprime [chave "chave" inserida]. Se a
chave já existe no dicionário, este comando deve sobrescrever seu conteúdo com conteudo, e imprimir
a mensagem [chave "chave" sobreescrita];
<br>
-> - chave: remove o par referente à chave chave, e imprime [chave "chave" removida]. Se a chave
não estiver no dicionário, imprima [chave "chave" nao encontrada];
<br>
-> ? chave: busca chave. Se a chave estiver no dicionário, imprima seu par no formato "chave": "conteudo".
Caso contrário, imprima [chave "chave" nao encontrada];
<br>
-> p: imprime todo o dicionário, em uma única linha, no formato JSON:
{"chave1":"conteudo1", "chave2":"conteudo2", ..., "chaveN":"conteudoN"};
<br>
-> w arq: salva o dicionário em disco, no arquivo arq,
e imprime a mensagem [arquivo arq salvo];
<br>
-> l arq: descarta o dicionário atualmente em memória, e carrega o dicionário salvo anteriormente no
arquivo arq, imprimindo a mensagem [arquivo arq carregado];
<br>
-> F: libera toda a memória alocada e termina a execução do programa.
