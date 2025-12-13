#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

// Função copiada de main.c para verificação
void limpa_palavra(char *palavra) {
    char *src = palavra;
    char *dst = palavra;
    
    while (*src) {
        if (isalpha((unsigned char)*src) || isdigit((unsigned char)*src)) {
            *dst = tolower((unsigned char)*src);
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

void teste(char *entrada, char *esperado) {
    char buffer[100];
    strcpy(buffer, entrada);
    limpa_palavra(buffer);
    printf("Entrada: '%s' -> Saida: '%s' ... ", entrada, buffer);
    if (strcmp(buffer, esperado) == 0) {
        printf("OK\n");
    } else {
        printf("FALHOU (Esperado: '%s')\n", esperado);
    }
}

int main() {
    printf("=== Verificacao da Funcao limpa_palavra ===\n\n");

    teste("Casa", "casa");
    teste("CASA", "casa");
    teste("Casa,", "casa");
    teste("(Ola)", "ola");
    teste("Texto123", "texto123");
    teste("!!!", "");
    teste("  Space  ", "space");
    teste("Maçã", "ma"); // Nota: isalpha padrão não trata acentos multi-byte UTF-8 corretamente sem locale, mas o código atual usa char simples. Verificaremos o comportamento padrão.
    
    printf("\n=== Fim dos testes ===\n");
    return 0;
}
