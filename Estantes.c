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
    printf("Nome da Nova Estante (0 para cancelar): ");
    setColor(7);
    limparBuffer();
    fgets(estantes[qtdEstantes].nome, 50, stdin);
    strtok(estantes[qtdEstantes].nome, "\n");

    if (strcmp(estantes[qtdEstantes].nome, "0") == 0) {
    printf("Operação cancelada.\n");
    return;
    }

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
    printf("Escolha a estante (1 a %d) ou 0 para cancelar: \n", qtdEstantes);
    setColor(7);
    for (int i=0; i<qtdEstantes; i++) {
        setColor(1);
        printf("%d.", i+1 );
        setColor(7);
        printf(" %s\n",estantes[i].nome);
    }

    int idx;
    if (scanf("%d", &idx) != 1) {
        limparBuffer();
        printf("Entrada inválida!\n");
        return;
    }

    if (idx == 0) {
        printf("Operação cancelada.\n");
        limparBuffer();
        return;
    }

    idx -= 1;

    Estante *e = &estantes[idx];
    if (e->qtdPrateleiras >= MAX_PRATELEIRAS) {
        printf("Número máximo de prateleiras atingido!\n");
        return;
    }
    setColor(6);
    printf("Nome da nova prateleira (0 para cancelar): ");
    setColor(7);
    limparBuffer();

    fgets(e->prateleiras[e->qtdPrateleiras].nome, 50, stdin);
    strtok(e->prateleiras[e->qtdPrateleiras].nome, "\n");

    if (strcmp(e->prateleiras[e->qtdPrateleiras].nome, "0") == 0) {
        printf("Operação cancelada.\n");
        return;
    }

    e->prateleiras[e->qtdPrateleiras].qtdItens = 0;
    e->qtdPrateleiras++;

    setColor(2);
    printf("Prateleira Adicionada Com Sucesso!(PRESSIONE ENTER)\n");
    setColor(7);
}


void adicionarItem() {
    setColor(12);
    printf("====================\n");

    if (qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada.\n");
        limparBuffer();
        return;
    }

    setColor(6);
    printf("Escolha a estante (1 a %d) ou 0 para cancelar:\n", qtdEstantes);
    setColor(7);

    for (int i = 0; i < qtdEstantes; i++) {
        setColor(1);
        printf("%d.", i + 1);
        setColor(7);
        printf(" %s\n", estantes[i].nome);
    }

    int eidx;
    if (scanf("%d", &eidx) != 1) {
        limparBuffer();
        printf("Entrada inválida!\n");
        return;
    }
    limparBuffer();

    if (eidx == 0) {
        printf("Operação cancelada.\n");
        return;
    }

    eidx -= 1;
    if (eidx < 0 || eidx >= qtdEstantes) {
        printf("Estante inválida!\n");
        return;
    }

    Estante *e = &estantes[eidx];

    if (e->qtdPrateleiras == 0) {
        printf("Nenhuma prateleira nessa estante.\n");
        return;
    }

    setColor(6);
    printf("Escolha a prateleira (1 a %d) ou 0 para cancelar:\n", e->qtdPrateleiras);
    setColor(7);

    for (int i = 0; i < e->qtdPrateleiras; i++) {
        setColor(1);
        printf("%d.", i + 1);
        setColor(7);
        printf(" %s\n", e->prateleiras[i].nome);
    }

    int pidx;
    if (scanf("%d", &pidx) != 1) {
        limparBuffer();
        printf("Entrada inválida!\n");
        return;
    }
    limparBuffer();

    if (pidx == 0) {
        printf("Operação cancelada.\n");
        return;
    }

    pidx -= 1;
    if (pidx < 0 || pidx >= e->qtdPrateleiras) {
        printf("Prateleira inválida!\n");
        return;
    }

    Prateleira *p = &e->prateleiras[pidx];

    if (p->qtdItens >= MAX_ITENS) {
        printf("Prateleira cheia!\n");
        return;
    }


    setColor(6);
    printf("Nome do item (digite 0 para cancelar): ");
    setColor(7);


    if (fgets(p->itens[p->qtdItens].nome, sizeof(p->itens[p->qtdItens].nome), stdin) == NULL) {
        printf("Erro de leitura!\n");
        return;
    }

    

    p->itens[p->qtdItens].nome[strcspn(p->itens[p->qtdItens].nome, "\n")] = '\0';

    if (strcmp(p->itens[p->qtdItens].nome, "0") == 0) {
        printf("Operação cancelada.\n");
        return;
    }
    
    p->qtdItens++;

    setColor(2);
    printf("Item adicionado com sucesso! (PRESSIONE ENTER)\n");
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
                    printf("%d. %s ", i+1, estantes[i].nome);
                    setColor(6);
                    printf("| Prateleira: ");
                    setColor(7);
                    printf(" %d. %s", j+1, estantes[i].prateleiras[j].nome);
                    printf("\nPressione Enter para continuar...");
                    return;
                }
            }
        }
    }
    printf("Item não encontrado!\n");
}

void listarEstanteEspecifica() {
    if (qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada.\n");
        return;
    }
    setColor(6);
    printf("Escolha a estante (1 a %d):\n", qtdEstantes);
    for (int i = 0; i < qtdEstantes; i++) {
        setColor(1);
        printf("%d. ", i + 1);
        setColor(7);
        printf("%s\n", estantes[i].nome);
    }

    int opc;
    scanf("%d", &opc);
    limparBuffer();
    opc--;

    if (opc < 0 || opc >= qtdEstantes) {
        printf("Estante inválida!\n");
        return;
    }

    Estante *e = &estantes[opc];
    setColor(6);
    printf("\n===== ESTANTE: %s =====\n", e->nome);
    setColor(7);
    if (e->qtdPrateleiras == 0) {
        printf("Nenhuma prateleira nesta estante.\n");
        return;
    }

    for (int j = 0; j < e->qtdPrateleiras; j++) {
        Prateleira *p = &e->prateleiras[j];

        setColor(6);
        printf("\n--- Prateleira: %s ---\n", p->nome);
        setColor(7);

        if (p->qtdItens == 0) {
            printf("Nenhum item nesta prateleira.\n");
        } else {
            for (int k = 0; k < p->qtdItens; k++) {
                setColor(1);
                printf("%d. ", k + 1);
                setColor(7);
                printf("%s\n", p->itens[k].nome);
            }
        }
    }
}

void listarPrateleiraEspecifica() {
    if (qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada.\n");
        return;
    }
    setColor(6);
    printf("Escolha a estante (1 a %d):\n", qtdEstantes);
    for (int i = 0; i < qtdEstantes; i++) {
        setColor(1);
        printf("%d.", i+1);
        setColor(7);
        printf(" %s\n", estantes[i].nome);
    }

    int estOpc;
    scanf("%d", &estOpc);
    limparBuffer();
    estOpc--;

    if (estOpc < 0 || estOpc >= qtdEstantes) {
        printf("Estante inválida!\n");
        return;
    }

    Estante *e = &estantes[estOpc];

    if (e->qtdPrateleiras == 0) {
        printf("Nenhuma prateleira nesta estante.\n");
        return;
    }
    setColor(6);
    printf("\nEscolha a prateleira (1 a %d):\n", e->qtdPrateleiras);
    for (int j = 0; j < e->qtdPrateleiras; j++) {
        setColor(1);
        printf("%d. ", j + 1);
        setColor(7);
        printf("%s\n", e->prateleiras[j].nome);
    }

    int prOpc;
    scanf("%d", &prOpc);
    limparBuffer();
    prOpc--;

    if (prOpc < 0 || prOpc >= e->qtdPrateleiras) {
        printf("Prateleira inválida!\n");
        return;
    }

    Prateleira *p = &e->prateleiras[prOpc];

    setColor(6);
    printf("\n   ===== ESTANTE: %s =====\n", e->nome);
    printf("===== PRATELEIRA: %s =====\n", p->nome);
    setColor(7);

    if (p->qtdItens == 0) {
        printf("Nenhum item nesta prateleira.\n");
        return;
    }

    for (int k = 0; k < p->qtdItens; k++) {
        setColor(1);
        printf("%d.", k + 1);
        setColor(7);
        printf(" %s\n", p->itens[k].nome);
    }
}

void listarGrade() {
    if(qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada\n");
        limparBuffer();
        return;
    }
    for (int i= 0; i<qtdEstantes; i++){
        setColor(6);
        printf("\nEstante %d:", i+1);
        setColor(7);
        printf(" %s\n", estantes[i].nome);
        for (int j=0; j<estantes[i].qtdPrateleiras; j++) {
            setColor(6);
            printf("  Prateleira %d:", j+1);
            setColor(7);
            printf(" %s\n", estantes[i].prateleiras[j].nome);
            for(int k=0; k<estantes[i].prateleiras[j].qtdItens; k++){
                setColor(6);
                printf("    -");
                setColor(7);
                printf(" %s\n", estantes[i].prateleiras[j].itens[k].nome);
            }
        }
    }

    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

void listar() {
    setColor(6);
    printf("Que tipo de listagem você gostaria?\n");
    setColor(1);
    printf("1.");
    setColor(7);
    printf(" Lista Completa\n");
    setColor(1);
    printf("2.");
    setColor(7);
    printf(" Listar Apenas uma Estante\n");
    setColor(1);
    printf("3.");
    setColor(7);
    printf(" Listar Apenas uma Prateleira\n");

    int opc;
    scanf("%d", &opc);

    switch(opc){

        case 1: listarGrade(); break;
        case 2: listarEstanteEspecifica(); break;
        case 3: listarPrateleiraEspecifica(); break;
    
    }
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

int selecionar_estante() {
    
    if (qtdEstantes == 0) {
        printf("Nenhuma estante cadastrada.\n");
        return -1;
    }
    setColor(6);
    printf("Escolha a estante (ou 0 para cancelar): \n");
    for (int i = 0; i < qtdEstantes; i++) {
        setColor(1);
        printf("%d. ", i+1);
        setColor(7);
        printf("%s\n", estantes[i].nome);
    }
    int idx;
    if (scanf("%d", &idx) != 1) { limparBuffer(); return -1;}
    limparBuffer();
    if(idx == 0) return -1;
    idx = idx - 1;
    if (idx < 0 || idx >= qtdEstantes) {
        printf("Estante inválida!\n");
        return -1;
    }
    return idx;
}

int selecionar_prateleira(Estante *e) {
    if (e-> qtdPrateleiras == 0) {
        printf("Nenhuma prateleira nesta estante.\n");
        return -1;
    }
    setColor(6);
    printf("Escolha a prateleira (ou 0 para cancelar): \n");
    for (int i = 0; i < e->qtdPrateleiras; i++) {
        setColor(1);
        printf("%d. ", i+1);
        setColor(7);
        printf("%s\n", e->prateleiras[i].nome);
    }
    int idx;
    if(scanf("%d", &idx) != 1) { limparBuffer(); return -1; }
    limparBuffer();
    if (idx == 0) return -1;
    idx = idx - 1;
    if (idx < 0 || idx >= e->qtdPrateleiras) {
        printf("Prateleira inválida!\n");
        return -1;
    }
    return idx;
}

int selecionar_item(Prateleira *p) {
    if (p->qtdItens == 0) {
        printf("Nenhum item nesta prateleira.\n");
        return -1;
    }
    setColor(6);
    printf("Escolha o item (ou 0 para cancelar): \n");
    for (int i = 0; i < p ->qtdItens; i++) {
        setColor(1);
        printf("%d. ", i + 1);
        setColor(7);
        printf("%s\n", p->itens[i].nome);
    }
    int idx;
     if(scanf("%d", &idx) != 1) {limparBuffer(); return -1; }
     limparBuffer();
     if (idx == 0) return -1;
     idx = idx - 1;
     if (idx <  0 || idx >= p->qtdItens) {
        printf("Item inválido!\n");
        return -1;
     }
     
     return idx;
}

int confirmacao(const char *msg) {
    char resp[8];
    printf("%s (s/n): ", msg);
    if(fgets(resp, sizeof(resp), stdin) == NULL) return 0;
    if (resp[0] == 's' || resp[0] == 'S') return 1;
    return 0;
}

int excluir() {
    int opcao;

    setColor(14);
    printf("\nO que deseja excluir?\n");
    printf("1. Item\n");
    printf("2. Prateleira\n");
    printf("3. Estante\n");
    printf("0. Voltar\n");
    setColor(7);

    printf("Escolha: ");
    if (scanf("%d", &opcao) != 1) {limparBuffer(); return 0;}
    limparBuffer();

    switch(opcao) {
        case 1:  {
            int eidx = selecionar_estante();
            if (eidx == -1) return 0;
            Estante *e = &estantes [eidx];

            int pidx = selecionar_prateleira(e);
            if (pidx == - 1) return 0;
            Prateleira *p = &e->prateleiras[pidx];

            int iidx = selecionar_item(p);
            if( iidx == -1 ) return 0;
            
            setColor(6);
            printf("Você vai excluir o item:");
            setColor(7);
            printf(" %s\n", p-> itens[iidx].nome);
            if (!confirmacao("Confirmar exclusão do item?")) {
                printf("Exclusão cancelada.\n");
                return 0;
            }

            for (int i = iidx; i <  p ->qtdItens - 1; i++) {
                p->itens[i] = p->itens[i + 1];
            }
            p-> qtdItens--;
            printf("Item excluído com sucesso!\n");
            return 1; }

        case 2: {
            int eidx =  selecionar_estante();
            if (eidx == -1) return 0;
            Estante *e = &estantes[eidx];

            int pidx = selecionar_prateleira(e);
            if (pidx == -1) return 0;

            printf("Você vai excluir a prateleira: %s\n", e->prateleiras[pidx].nome);
            if (!confirmacao("Confirmar exclusão da prateleira (todos os itens serão removidos)?")) {
                printf("Exclusão cancelada.\n");
                return 0;
            }

            for (int i = pidx; i < e->qtdPrateleiras - 1; i++) {
                e->prateleiras[i] = e->prateleiras[i + 1];
            }
            e->qtdPrateleiras--;
            printf("Prateleira excluída com sucesso!\n");
            return 1; }
        
        case 3: {
           int eidx = selecionar_estante();
            if (eidx == -1) return 0;

            printf("Você vai excluir a estante: %s\n", estantes[eidx].nome);
            if (!confirmacao("Confirmar exclusão da estante (todas as prateleiras e itens serão removidos)?")) {
                printf("Exclusão cancelada.\n");
                return 0;
            }

            for (int i = eidx; i < qtdEstantes - 1; i++) {
                estantes[i] = estantes[i + 1];
            }
            qtdEstantes--;
            printf("Estante excluída com sucesso!\n");
            return 1; 
        }

        case 0: return 0;

        default: 
            printf("Opção inválida!\n");
            return 0;
    }


}   

int moverItem() {
    printf("\n=== MOVER ITEM ===\n");

    int eOrig = selecionar_estante();
    if (eOrig == -1) return 0;
    Estante *origE = &estantes[eOrig];

   
    int pOrig = selecionar_prateleira(origE);
    if (pOrig == -1) return 0;
    Prateleira *origP = &origE->prateleiras[pOrig];

    printf("\nSelecione o item a mover:\n");
    int iOrig = selecionar_item(origP);
    if(iOrig == -1) return 0;

    Item itemMovido = origP->itens[iOrig];

    setColor(6);
    printf("\nItem selecionado:");
    setColor(7);
    printf(" %s\n", itemMovido.nome);

    if(!confirmacao("Confirmar mover este item?"))
        return 0;
    
    printf("\nSelecione a estante de DESTINO:\n");
    int eDest = selecionar_estante();
    if (eDest == -1) return 0;
    Estante *destE = &estantes[eDest];

    printf("\nSelecione a prateleira de DESTINO:\n");
    int pDest = selecionar_prateleira(destE);
    if (pDest == -1) return 0;
    Prateleira *destP = &destE->prateleiras[pDest];

    if (destP->qtdItens >= MAX_ITENS) {
        printf("A prateleira de destino está cheia!\n");
        return 0;
    }

    destP->itens[destP->qtdItens] = itemMovido;
    destP->qtdItens++;

    for (int i = iOrig; i < origP->qtdItens -1; i++) {
        origP->itens[i] = origP->itens[i + 1];
    }

    origP->qtdItens--;

    printf("\nItem movido com sucesso!\n");

    return 1;
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
        printf("5. Excluir || ");
        printf("6. Mover Item ||");
        // printf("7. Lista Completa || ");
        // printf("8. Listar uma Estante || ");
        // printf("9. Listar uma prateleira ||");
        printf("7. Listar || ");
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
            case 5: excluir(); salvarGrade(); limparTela(); break;
            case 6: moverItem(); salvarGrade(); limparTela(); break;
            // case 7: listarGrade(); limparTela(); break;
            // case 8: listarEstanteEspecifica(); limparTela(); break;
            // case 9: listarPrateleiraEspecifica(); limparTela(); break;
            case 7: listar(); limparTela(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    exportarGradeTxt();
    system("pause");
    return 0;
}
