#include <stdio.h>

int escolher_estante(int qtdEstantes, Estante *estantes) {
    if (qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada.\n");
        return -1;
    }
    printf("Escolha a estante (ou 0 para cancelar):\n");
    for (int i = 0; i < qtdEstantes; i++) {
        printf("%d. %s\n", i + 1, estantes[i].nome);
    }
    int idx;
    if (scanf("%d", &idx) != 1) { limparBuffer(); return -1; }
    limparBuffer();
    if (idx == 0) return -1;
    idx = idx - 1;
    if (idx < 0 || idx >= qtdEstantes) {
        printf("Estante inválida!\n");
        return -1;
    }
    return idx;
}