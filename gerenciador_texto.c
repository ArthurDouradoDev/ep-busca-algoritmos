#include <malloc.h>
#include <ctype.h>
#include <string.h>
// Declaração global ou na main
char **todas_as_linhas = NULL;
int total_linhas = 0;
int capacidade_linhas = 1000;

// Na função de leitura:
todas_as_linhas = malloc(capacidade_linhas * sizeof(char*));

while (fgets(buffer, TAMANHO_BUFFER, arquivo)) {
    // 1. Remove o \n do final, se tiver
    buffer[strcspn(buffer, "\n")] = 0;

    // 2. Verifica se precisa aumentar o vetor
    if (total_linhas >= capacidade_linhas) {
        capacidade_linhas *= 2;
        todas_as_linhas = realloc(todas_as_linhas, capacidade_linhas * sizeof(char*));
    }

    // 3. CRUCIAL: Aloca memória para ESSA linha específica e copia
    // Se você fizer apenas 'todas_as_linhas[i] = buffer', vai dar errado!
    todas_as_linhas[total_linhas] = strdup(buffer); // strdup faz malloc+strcpy automático
    
    total_linhas++;
}

// Função que transforma "Atenção!" em "atencao" (ou apenas "atencao" sem acento se for simples)
// O enunciado geralmente pede apenas tolower e remoção de pontuação simples.
void limpa_palavra(char *raw) {
    int i = 0, j = 0;
    while (raw[i]) {
        if (isalpha(raw[i])) {
            raw[j++] = tolower(raw[i]); // Mantém apenas letras e minúsculas
        }
        // Se quiser manter hífen como letra, adicione a condição aqui.
        // Mas o enunciado diz para separar hífens, então hífens viram separadores no strtok/strsep
        i++;
    }
    raw[j] = '\0'; // Fecha a string nova
}