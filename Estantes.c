
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>

#define MAX_ITENS 50
#define MAX_PRATELEIRAS 10
#define MAX_ESTANTES 10


typedef struct{
  char nome[100]; 
} Item;

typedef struct{
    char nome[50];
    Item itens[MAX_ITENS];
    int qtdItens;
} Prateleira;

typedef struct{
    char nome[50];
    Prateleira prateleiras[MAX_PRATELEIRAS];
    int qtdPrateleiras;
} Estante;

Estante estantes[MAX_ESTANTES];
int qtdEstantes = 0;

void toLowerString(char *str) {
  for(int i = 0; str[i]; i++) {
    str[i] = tolower((unsigned char)str[i]);
  }
}

void setColor(int color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void limparTela() {
    limparBuffer();    
    system("cls || clear"); 
}


void adicionarEstante(){
    setColor(12);
    printf("====================\n");

    if(qtdEstantes >= MAX_ESTANTES) {
        printf("Quantidade máxima de estantes atingida!\n");
        limparBuffer();
        return;
    }

    setColor(6);
    printf("Nome da Nova Estante: ");
    setColor(7);
    limparBuffer();
    fgets(estantes[qtdEstantes].nome, 50, stdin);
    strtok(estantes[qtdEstantes].nome, "\n");
    estantes[qtdEstantes].qtdPrateleiras = 0;
    qtdEstantes++;
    setColor(2);
    printf("Estante adicionada com sucesso!(PRESSIONE ENTER)\n");
    setColor(7);
}


void adicionarPrateleira(){
    setColor(12);
    printf("====================\n");

    if (qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada!\n");
        limparBuffer();
        return;
    }

    setColor(6);
    printf("Escolha a estante (1 a %d): \n", qtdEstantes);
    setColor(7);
    for (int i=0; i<qtdEstantes; i++) {
        setColor(1);
        printf("%d.", i+1 );
        setColor(7);
        printf(" %s\n",estantes[i].nome);
    }

    int idx;
    scanf("%d", &idx);
    idx = idx - 1; 
    if(idx<0 || idx >= qtdEstantes) {
        printf("Estante inválida!\n");
        return;
    }

    Estante *e = &estantes[idx];
    if (e->qtdPrateleiras >= MAX_PRATELEIRAS) {
        printf("Número máximo de prateleiras atingido!\n");
        return;
    }
    setColor(6);
    printf("Nome da nova prateleira: ");
    setColor(7);
    limparBuffer();
    fgets(e->prateleiras[e->qtdPrateleiras].nome, 50, stdin);
    strtok(e->prateleiras[e->qtdPrateleiras].nome, "\n");
    e->prateleiras[e->qtdPrateleiras].qtdItens = 0;
    e->qtdPrateleiras++;
    setColor(2);
    printf("Prateleira Adicionada Com Sucesso!(PRESSIONE ENTER)\n");
    setColor(7);
}


void adicionarItem(){
    setColor(12);
    printf("====================\n");

    if(qtdEstantes == 0){
        printf("Nenhuma estante cadastrada.\n");
        limparBuffer();
        return;
    }

    setColor(6);
    printf("Escolha a estante:\n");
    for (int i=0; i<qtdEstantes; i++){
        setColor(1);
        printf("%d.", i+1);
        setColor(7);
        printf(" %s\n", estantes[i].nome);
    }

    int eidx;
    scanf("%d", &eidx); getchar();
    eidx = eidx - 1; 

    if (eidx<0 || eidx>= qtdEstantes) {
        printf("Estante inválida!\n");
        limparBuffer();
        return;
    }

    Estante *e = &estantes[eidx];
    if (e->qtdPrateleiras == 0) {
        printf("Nenhuma prateleira nessa estante.\n");
        return;
    }

    setColor(6);
    printf("Escolha a prateleira:\n");
    for (int i=0; i<e->qtdPrateleiras; i++){
        setColor(1);
        printf("%d.", i+1);
        setColor(7);
        printf(" %s\n", e->prateleiras[i].nome);
    }

    int pidx;
    scanf("%d", &pidx); getchar();
    pidx = pidx - 1; 

    if(pidx<0 || pidx>=e->qtdPrateleiras) {
        printf("Prateleira inválida!\n");
        
        return;
    }

    Prateleira *p = &e->prateleiras[pidx];
    if (p->qtdItens >= MAX_ITENS) {
        printf("Prateleira cheia!\n");
        
        return;
    }

    setColor(6); 
    printf("Nome do item: ");
    setColor(7);
    fgets(p->itens[p->qtdItens].nome, 100, stdin);
    strtok(p->itens[p->qtdItens].nome, "\n");
    p->qtdItens++;
    setColor(2);
    printf("Item adicionado com sucesso!(PRESSIONE ENTER)\n");
    setColor(7);
}


void buscarItem() {

    if (qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada.\n");
        limparBuffer();
        return;
    }

    char nome[100];
    setColor(6);
    printf("Digite o nome do item a buscar: ");
    setColor(7);
    limparBuffer();
    fgets(nome, 100, stdin);
    strtok(nome, "\n");

    char itemNomeLower[100];
    char buscaLower[100];

    for (int i = 0; i<qtdEstantes; i++) {
        for (int j=0; j<estantes[i].qtdPrateleiras; j++) {
            for (int k=0; k<estantes[i].prateleiras[j].qtdItens; k++) {

              strcpy(itemNomeLower, estantes[i].prateleiras[j].itens[k].nome);
              strcpy(buscaLower, nome);

              toLowerString(itemNomeLower);
              toLowerString(buscaLower);

              if(strcmp(itemNomeLower, buscaLower) == 0) {
                    setColor(6);
                    printf("\nItem encontrado: ");
                    setColor(7);
                    printf("%s\n", nome);
                    setColor(6);
                    printf("Estante: ");
                    setColor(7);
                    printf("%d ", i+1);
                    setColor(6);
                    printf("| Prateleira: ");
                    setColor(7);
                    printf(" %d", j+1);
                    printf("\nPressione Enter para continuar...");
                    return;
                }
            }
        }
    }
    printf("Item não encontrado!\n");
}


void listarGrade() {
    if(qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada\n");
        limparBuffer();
        return;
    }
    for (int i= 0; i<qtdEstantes; i++){
        printf("\nEstante %d: %s\n", i+1, estantes[i].nome);
        for (int j=0; j<estantes[i].qtdPrateleiras; j++) {
            printf("  Prateleira %d: %s\n", j+1, estantes[i].prateleiras[j].nome);
            for(int k=0; k<estantes[i].prateleiras[j].qtdItens; k++){
                printf("    - %s\n", estantes[i].prateleiras[j].itens[k].nome);
            }
        }
    }

    printf("\nPressione Enter para continuar...");
    limparBuffer();
}


void salvarGrade() {
    FILE *arquivo = fopen("grade.dat", "wb");
    if (!arquivo) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }
    fwrite(&qtdEstantes, sizeof(int), 1, arquivo);
    fwrite(estantes, sizeof(Estante), qtdEstantes, arquivo);
    fclose(arquivo);
}

void carregarGrade() {
    FILE *arquivo = fopen("grade.dat", "rb");
    if(!arquivo) return;
    fread(&qtdEstantes, sizeof(int), 1, arquivo);
    fread(estantes, sizeof(Estante), qtdEstantes, arquivo);
    fclose(arquivo);
}


void exportarGradeTxt() {
    FILE *arquivo = fopen("grade.txt", "w");
    if (!arquivo) {
        printf("Erro ao criar o arquivo grade.txt!\n");
        return;
    }
    for (int i = 0; i < qtdEstantes; i++) {
        fprintf(arquivo, "Estante %d: %s\n", i+1, estantes[i].nome);
        for (int j = 0; j < estantes[i].qtdPrateleiras; j++) {
            fprintf(arquivo, "  Prateleira %d: %s\n", j+1, estantes[i].prateleiras[j].nome);
            for (int k = 0; k < estantes[i].prateleiras[j].qtdItens; k++) {
                fprintf(arquivo, "    - %s\n", estantes[i].prateleiras[j].itens[k].nome);
            } 
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
    printf("Grade exportada com sucesso para grade.txt!\n");
}


int main() {
    carregarGrade();
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;
    do {
        setColor(4);
        printf("\n===MENU DE ORGANIZAÇÃO===\n");
        setColor(14);
        printf("\n1. Adicionar Estante || ");
        printf("2. Adicionar Prateleira || ");
        printf("3. Adicionar Item || ");
        printf("4. Buscar Item || ");
        printf("5. Lista Completa\n");
        printf("0. Sair(Salvar Txt)\n");
        setColor(6);
        printf("\nEscolha Uma Opção: ");
        setColor(7);

        scanf("%d", &opcao);
        switch(opcao) {
            case 1: adicionarEstante(); salvarGrade(); limparTela(); break;
            case 2: adicionarPrateleira(); salvarGrade(); limparTela(); break;
            case 3: adicionarItem(); salvarGrade(); limparTela(); break;
            case 4: buscarItem(); limparTela(); break;
            case 5: listarGrade(); limparTela(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    exportarGradeTxt();
    system("pause");
    return 0;
}
