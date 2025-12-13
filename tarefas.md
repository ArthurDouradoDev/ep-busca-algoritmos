Tarefa 1: Criar e Distribuir o "Contrato" (estruturas.h)
Esta é a tarefa de bloqueio. Seus colegas não podem trabalhar sem isso.

Criar o arquivo: Crie um arquivo chamado estruturas.h.

Definir as Structs: Insira as definições de NoLinha e NoIndice (conforme mostrei na resposta anterior).

Compartilhar: Envie este arquivo para o grupo imediatamente.

Objetivo: Garantir que todos usem os mesmos nomes de variáveis (prox, esq, dir, palavra) para evitar erros de compilação quando juntarem tudo.

Tarefa 2: Carregar o Texto na Memória (Persistência)
O problema do esqueleto original é que ele apaga a linha lida. Você precisa consertar isso.

Criar Armazenamento: No main.c (ou módulo separado), declare um ponteiro duplo char **todas_as_linhas e variáveis para total_linhas e capacidade_maxima.

Inicializar: Faça um malloc inicial para, digamos, 1000 ponteiros de char.

Loop de Leitura: Dentro do loop que lê o arquivo (fgets):

Remova o caractere \n do final da string lida.

Verifique se o vetor está cheio. Se estiver, use realloc para dobrar o tamanho.

Duplicação: Use strdup() (ou malloc + strcpy) para copiar a linha do buffer temporário para o seu vetor todas_as_linhas[i].

Objetivo: Ao final da leitura, você deve ser capaz de imprimir todas_as_linhas[50] e ver o texto original da linha 51.

Tarefa 3: Implementar o Sanitizador de Strings
O índice não pode ter "Casa," e "casa" como palavras diferentes.

Criar Função Auxiliar: Implemente void limpa_palavra(char *palavra).

Lógica de Limpeza:

Percorra a string caractere por caractere.

Se for letra maiúscula -> converte para minúscula (tolower).

Se for pontuação (vírgula, ponto, exclamação) -> remove (move os caracteres seguintes para trás ou ignora na cópia).

Mantenha apenas caracteres alfanuméricos.

Objetivo: Transformar entradas sujas como "(Hello!)" na string limpa "hello".

Tarefa 4: O Loop de Tokenização (Alimentar o Índice)
Agora você conecta a leitura (Tarefa 2) com as funções dos seus colegas.

Loop Principal: Logo após ler e salvar a linha na memória (dentro do loop de leitura da Tarefa 2):

Crie uma cópia temporária da linha (para não destruir a original que você salvou).

Use strsep ou strtok nesta cópia para quebrar a frase em palavras (tokens).

Processamento:

Para cada token extraído, chame sua função limpa_palavra.

Se a palavra não estiver vazia, chame a função de inserção adequada (insere_lista ou insere_arvore) passando a palavra e o número da linha atual.

Nota: Você precisará declarar os protótipos dessas funções (insere_...) no topo do seu arquivo, mesmo que elas ainda não estejam prontas (isso se chama forward declaration), para seu código compilar.

Tarefa 5: Interface de Usuário (CLI) e Busca
A parte visível do EP.

Loop Interativo: Crie um while(1) após o arquivo ser totalmente lido e o índice criado.

Comandos:

Leia uma string do usuário.

Se for "fim", dê break no loop e encerre.

Se for "busca", leia a próxima string (o termo a ser buscado).

Executar Busca:

Limpe o termo de busca (aplique limpa_palavra nele também).

Chame a função de busca dos seus colegas.

Se retornar NULL: Imprima "Palavra nao encontrada".

Se retornar um Nó:

Imprima o total de ocorrências.

Percorra a lista ligada de linhas (NoLinha) que está dentro desse Nó.

Para cada número de linha encontrado, vá no seu vetor todas_as_linhas e imprima o texto correspondente formatado (ex: 00123: Conteúdo da linha...).