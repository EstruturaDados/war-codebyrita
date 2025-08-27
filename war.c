// ============================================================================
// Desafio WAR Estruturado — NÍVEL NOVATO (com CONFIRMAÇÃO/EDIÇÃO)
// Objetivo:
//   - struct Territorio
//   - vetor estático com 5 elementos
//   - I/O segura (fgets/scanf)
//   - Preview + etapa para EDITAR itens antes de confirmar
//
// Compilar:
//   gcc -Wall -Wextra -std=c11 -O2 -o war war.c
//   ./war
// ============================================================================

#include <stdio.h>
#include <string.h>   // strcspn

#define NUM_TERRITORIOS 5
#define TAM_NOME 64
#define TAM_COR  32

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int  tropas;
} Territorio;

/* ---------- Utilitários de I/O ---------- */
static void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}

static void lerLinha(const char *prompt, char *dest, size_t tam) {
    printf("%s", prompt);
    if (fgets(dest, (int)tam, stdin)) {
        dest[strcspn(dest, "\n")] = '\0';
    } else {
        dest[0] = '\0';
    }
}

static int lerIntFaixa(const char *prompt, int min, int max) {
    int x;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%d", &x) == 1 && x >= min && x <= max) {
            limparEntrada();
            return x;
        }
        limparEntrada();
        printf("  Valor inválido. Digite um inteiro entre %d e %d.\n", min, max);
    }
}

static char lerOpcaoSN(const char *prompt) {
    for (;;) {
        printf("%s", prompt);
        int ch = getchar();
        limparEntrada();
        if (ch == 's' || ch == 'S' || ch == 'n' || ch == 'N') return (char)ch;
        printf("  Responda com S ou N.\n");
    }
}

/* ---------- Exibição ---------- */
static void imprimirMapa(const Territorio mapa[], int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %-20s | Cor: %-10s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================================\n");
}

/* ---------- Edição ---------- */
static void editarTerritorio(Territorio *t) {
    printf("\n--- Editar Território ---\n");
    lerLinha("Novo nome (deixe vazio para manter): ", t->nome, sizeof(t->nome));
    if (t->nome[0] == '\0') { /* se vazio, perguntar de novo o atual para manter */
        printf("Nome mantido.\n");
    }

    char novaCor[TAM_COR];
    lerLinha("Nova cor (deixe vazio para manter): ", novaCor, sizeof(novaCor));
    if (novaCor[0] != '\0') {
        strncpy(t->cor, novaCor, sizeof(t->cor));
        t->cor[sizeof(t->cor)-1] = '\0';
    } else {
        printf("Cor mantida.\n");
    }

    printf("Tropas atuais: %d\n", t->tropas);
    char resp = lerOpcaoSN("Deseja alterar o número de tropas? (S/N): ");
    if (resp == 's' || resp == 'S') {
        t->tropas = lerIntFaixa("Novo número de tropas: ", 0, 999);
    } else {
        printf("Tropas mantidas.\n");
    }
}

/* ---------- Programa principal ---------- */
int main(void) {
    Territorio mapa[NUM_TERRITORIOS];

    /* Cadastro inicial */
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\n--- Cadastro do Território %d/%d ---\n", i + 1, NUM_TERRITORIOS);
        lerLinha("Nome do território: ", mapa[i].nome, sizeof(mapa[i].nome));
        lerLinha("Cor do exército   : ", mapa[i].cor,  sizeof(mapa[i].cor));
        mapa[i].tropas = lerIntFaixa("Número de tropas   : ", 0, 999);
    }

    /* Etapa de confirmação/edição */
    for (;;) {
        imprimirMapa(mapa, NUM_TERRITORIOS);
        char resp = lerOpcaoSN("Confirmar esses dados? (S = confirmar / N = editar): ");
        if (resp == 's' || resp == 'S') break;  // segue para a impressão final

        // Escolher índice para editar
        int idx = lerIntFaixa("Qual território deseja editar? (1..5): ", 1, NUM_TERRITORIOS) - 1;
        editarTerritorio(&mapa[idx]);
        // volta ao topo do laço para reexibir o preview e perguntar novamente
    }

    /* Exibição final confirmada */
    printf("\n✅ Dados confirmados!\n");
    imprimirMapa(mapa, NUM_TERRITORIOS);
    return 0;
}
