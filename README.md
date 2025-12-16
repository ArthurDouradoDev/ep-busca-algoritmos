# EP - Indexador e Buscador de Texto (AED 1)

Este projeto implementa um sistema robusto para indexação e busca de palavras em arquivos de texto. O objetivo principal é comparar a performance entre duas estruturas de dados clássicas: **Listas Ligadas** e **Árvores Binárias de Busca (ABB)**.

## 🚀 Funcionalidades Implementadas

O projeto está **completo** e funcional, contando com:

1.  **Carregamento Otimizado**: O arquivo de texto é carregado completamente para a memória no início, permitindo acesso instantâneo às linhas originais durante a busca sem I/O de disco adicional.
2.  **Tratamento dos Textos**: As palavras são tratadas antes da indexação:
    *   Remoção de pontuações (`.,!?-:;` etc).
    *   Conversão para minúsculas (case-insensitive).
    *   Preservação de caracteres acentuados.
3.  **Métricas de Performance**:
    *   **Contador de Comparações**: Monitora a eficiência da construção do índice e da busca.
    *   **Estatísticas da Estrutura**: Exibe o total de palavras únicas cadastradas e, no caso da árvore, a sua altura máxima.
4.  **Interface de Usuário**: Interface de linha de comando amigável com suporte a UTF-8 (acentuação correta no Windows).

## 🛠️ Como Compilar

O projeto é dividido em módulos. Para compilar, utilize o GCC:

```bash
gcc main.c lista.c arvore.c -o ep.exe
```

Isso gerará o executável `ep.exe`.

## 💻 Como Executar

O programa deve ser executado via terminal, recebendo dois argumentos obrigatórios:

1.  **Nome do arquivo**: O caminho para o arquivo de texto a ser lido (ex: `basic.txt`, `long.txt`).
2.  **Tipo de Índice**: A estrutura de dados a ser utilizada (`lista` ou `arvore`).

### Exemplos:

**Modo Lista Ligada:**
```bash
./ep.exe long.txt lista
```

**Modo Árvore Binária:**
```bash
./ep.exe long.txt arvore
```

---

## 🔍 Comandos da Interface

Após o carregamento, o programa exibirá estatísticas iniciais e aguardará comandos (`>`).

| Comando | Descrição | Exemplo |
| :--- | :--- | :--- |
| `busca <palavra>` | Procura a palavra no índice e lista as linhas onde ela ocorre. Exibe também o nº de comparações feitas. | `busca frankenstein` |
| `fim` | Encerra a execução do programa. | `fim` |

**Exemplo de Saída:**
```text
> busca algorithm
Existem 4 ocorrências da palavra 'algorithm' na(s) seguinte(s) linha(s):
00001: Informally, an algorithm is any well-defined computational procedure that takes
00003: as output. An algorithm is thus a sequence of computational steps that transform
...
Numero de comparacoes: 3
```

## 📊 Comparação de Performance (Resultados Obtidos)

Os experimentos realizados com textos de diferentes tamanhos (`basic`, `medium`, `long`) demonstraram claramente a diferença de complexidade teórica entre as estruturas.

**Destaque (Arquivo Grande - ~7.500 palavras únicas):**

| Estrutura | Custo de Construção (Comparações) | Busca Palavra Inexistente (*) |
| :--- | :--- | :--- |
| **Lista Ligada** (O(N)) | **326.258.238** (326 Milhões) | ~7.414 comparações |
| **Árvore BST** (O(log N))| **885.075** (0.8 Milhões) | ~11-15 comparações |

**(*)** A busca de palavra inexistente força o **Pior Caso**, percorrendo toda a estrutura (ou até a folha). A Árvore foi massivamente superior, transformando uma busca linear de 7 mil passos em apenas 15 passos.

## 📂 Estrutura do Código

*   **`main.c`**: Ponto de entrada. Gerencia o carregamento do arquivo, loop de comandos e exibição de resultados.
*   **`estruturas.h`**: Cabeçalho unificado definindo `NoIndice` e protótipos das funções.
*   **`lista.c`**: Implementação das funções de manipulação da Lista Ligada (`insere`, `busca`, `conta`).
*   **`arvore.c`**: Implementação das funções de manipulação da Árvore Binária (`insere`, `busca`, `altura`, `conta`).

## 📁 Arquivos Adicionais e Scripts

*   **`esqueleto_EP.c`**: Arquivo de template original fornecido para o exercício.
*   **`basic.txt` / `medium.txt` / `long.txt`**: Conjuntos de dados utilizados para os testes de performance.
    *   `basic.txt`: Pequeno trecho em inglês (introdução a algoritmos).
    *   `medium.txt`: Artigo médio em português.
    *   `long.txt`: O texto completo do livro *Frankenstein* (em inglês) do Project Gutenberg.
*   **`run_experiments.bat`**: Script de automação (Windows Batch) criado para executar a bateria de testes e gerar o relatório `results.txt`.
*   **`input_commands.txt`**: Arquivo contendo a sequência automatizada de comandos de busca (ex: busca por "Frankenstein", "algorithm", "Google") usada pelo script.

---
*Projeto desenvolvido para a disciplina de Algoritmos e Estruturas de Dados 1 da USP - 2o Semestre de 2025.*