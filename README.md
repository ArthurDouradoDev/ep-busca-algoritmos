# EP - Busca em Arquivos de Texto (AED 1)

Este projeto implementa um sistema de indexação e busca de palavras em arquivos de texto, utilizando Listas Ligadas e Árvores Binárias de Busca (ABB).

## Estado Atual do Projeto

O projeto já possui as seguintes funcionalidades implementadas (`main.c` e estrutural):

1.  **Carregamento e Persistência**: O arquivo de texto é lido inteiramente para a memória (`todas_as_linhas`), permitindo acesso rápido ao conteúdo original das linhas sem precisar reler o arquivo do disco. As linhas são limpas de caracteres de quebra de linha.
2.  **Sanitização de Texto**: Implementada a função `limpa_palavra`, que:
    *   Remove pontuações (.,!?- etc).
    *   Converte tudo para minúsculas.
    *   Mantém dígitos.
    *   Exemplo: "Casa," vira "casa".
3.  **Tokenização**: O texto é quebrado em palavras (tokens) que alimentam o índice.
4.  **Interface de Linha de Comando (CLI)**: Loop interativo que aceita os comandos:
    *   `busca <termo>`: Procura uma palavra no índice e retorna as linhas onde ela aparece.
    *   `fim`: Encerra o programa.
5.  **Estrutura de Dados (`estruturas.h`)**: Definições de `NoLinha` e `NoIndice` unificadas para uso em Listas e Árvores.

### O que Falta Fazer (Próximos Passos)

Os arquivos complementares (`stubs.c` ou novos arquivos como `lista.c` e `arvore.c`) precisam ter suas funções implementadas. Atualmente, elas são apenas "stubs" (funções vazias) em `stubs.c`.

Colaboradores devem implementar:
*   `insere_lista` / `busca_lista`
*   `insere_arvore` / `busca_arvore`

## Como Compilar

Para compilar o projeto completo (atualmente usando os stubs):

```bash
gcc main.c stubs.c -o ep.exe
```

Para verificar o funcionamento da função de limpeza de texto separadamente:

```bash
gcc verificar_limpeza.c -o verificar.exe
./verificar
```

## Como Executar

O programa espera dois argumentos: o nome do arquivo de texto e o tipo de índice (`lista` ou `arvore`).

Exemplo:
```bash
./ep texto.txt lista
```
ou
```bash
./ep texto.txt arvore
```

### Interação

Após iniciar, o programa carregará o arquivo e ficará aguardando comandos:

```text
> busca casa
Existem 3 ocorrências da palavra 'casa' nas seguintes linhas:
00010: Onde fica a casa?
00015: A Casa é bonita.
00020: Eu vou para casa.

> fim
```