// ============================================================================
// Desafio WAR Estruturado — NÍVEL NOVATO
// Objetivo deste nível:
//   - Definir uma struct Territorio (nome, cor do exército, número de tropas)
//   - Armazenar 5 territórios em um vetor ESTÁTICO
//   - Ler dados via terminal (fgets/scanf) e exibir o “mapa” organizado
//
// Como compilar no Codespaces:
//   gcc -Wall -Wextra -std=c11 -O2 -o war war.c
//   ./war
// ============================================================================

#include <stdio.h>    // printf, scanf
#include <string.h>   // strcspn (para remover '\n' do fgets)

// --------------------------- PASSO 1: Constantes -----------------------------
//  números "mágicos" centralizados em #defines para facilitar manutenção.
#define NUM_TERRITORIOS 5
#define TAM_NOME 64   // tamanho máximo do nome do território (inclui '\0')
#define TAM_COR  32   // tamanho máximo do nome da cor (inclui '\0')

// ----------------------- PASSO 2: Definir a STRUCT ---------------------------
// A struct agrupa dados que pertencem ao MESMO conceito (um território do WAR).
typedef struct {
    char nome[TAM_NOME];  // ex.: "Alasca"
    char cor[TAM_COR];    // ex.: "Verde", "Vermelho", "Azul"
    int  tropas;          // ex.: 12
} Territorio;

// --------------- PASSO 3: Utilitários de Entrada/Saída (I/O) ----------------
// Quando usamos scanf("%d", ...), o '\n' que o usuário digita fica no buffer.
// Esta função descarta tudo até o próximo '\n' para não "pular" leituras.
static void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}

// Lê uma linha de texto com fgets e remove o '\n' final, se existir.
static void lerLinha(const char *prompt, char *dest, size_t tam) {
    printf("%s", prompt);
    if (fgets(dest, (int)tam, stdin)) {
        // strcspn encontra a primeira ocorrência de '\n' e retorna o índice.
        dest[strcspn(dest, "\n")] = '\0';
    } else {
        // fallback de segurança (evita lixo na string em caso de erro)
        dest[0] = '\0';
    }
}

// Lê um inteiro dentro de [min..max], repetindo até estar válido.
static int lerIntFaixa(const char *prompt, int min, int max) {
    int x;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%d", &x) == 1 && x >= min && x <= max) {
            limparEntrada();   // consome o '\n' remanescente
            return x;
        }
        limparEntrada();
        printf("  Valor inválido. Digite um inteiro entre %d e %d.\n", min, max);
    }
}

// ----------------------- PASSO 4: Impressão do “Mapa” ------------------------
// Separar a formatação em uma função ajuda a manter o main limpo e didático.
static void imprimirMapa(const Territorio mapa[], int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        // %-20s e %-10s alinham as colunas à esquerda, melhorando a leitura
        printf("%d) Nome: %-20s | Cor: %-10s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================================\n");
}

// ----------------------------- PASSO 5: main --------------------------------
//   1) Declarar o vetor estático com 5 territórios
//   2) Preencher cada território lendo do usuário (nome, cor, tropas)
//   3) Exibir o mapa formatado
int main(void) {
    Territorio mapa[NUM_TERRITORIOS];  // vetor ESTÁTICO, tamanho fixo = 5

    // Cadastro dos 5 territórios
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\n--- Cadastro do Território %d/%d ---\n", i + 1, NUM_TERRITORIOS);

        // Nome do território (aceita espaços, por isso usamos fgets via lerLinha)
        lerLinha("Nome do território: ", mapa[i].nome, sizeof(mapa[i].nome));

        // Cor do exército dominante (livre: "Verde", "Azul", etc.)
        lerLinha("Cor do exército   : ", mapa[i].cor, sizeof(mapa[i].cor));

        // Número de tropas (validado). Aqui definimos uma faixa didática (0..999).
        mapa[i].tropas = lerIntFaixa("Número de tropas   : ", 0, 999);
    }

    // Exibição organizada do mapa após o cadastro
    imprimirMapa(mapa, NUM_TERRITORIOS);

    return 0;
}
