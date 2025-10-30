#include <stdio.h>

// ======================================================
// XADREZ.C — Simulação de movimentos das peças de xadrez
// Autor: João Victor Scarpim Freitas
// ======================================================
// Peças simuladas:
//  - Torre   → Movimento reto (recursão)
//  - Bispo   → Movimento diagonal (recursão + loops aninhados)
//  - Rainha  → Movimento completo (recursão)
//  - Cavalo  → Movimento em “L” (loops aninhados complexos com break e continue)
// ======================================================

// -------------------------------
// Função recursiva: Torre
// -------------------------------
// Move 5 casas para a direita.
// Usa recursividade no lugar do loop for.
void moverTorre(int casas) {
    if (casas == 0)
        return;
    printf("Direita\n");
    moverTorre(casas - 1);
}

// -------------------------------
// Função recursiva + loops aninhados: Bispo
// -------------------------------
// Move 5 casas na diagonal (cima + direita).
// Loop externo: movimento vertical
// Loop interno: movimento horizontal
void moverBispo(int casasVerticais, int casasHorizontais) {
    if (casasVerticais == 0 || casasHorizontais == 0)
        return;

    // Loop aninhado simula diagonal (cima e direita)
    for (int i = 0; i < casasVerticais; i++) {
        for (int j = 0; j < casasHorizontais; j++) {
            if (i == j) {
                printf("Cima, Direita\n");
            }
        }
    }

    moverBispo(casasVerticais - 1, casasHorizontais - 1);
}

// -------------------------------
// Função recursiva: Rainha
// -------------------------------
// Move 8 casas para a esquerda.
void moverRainha(int casas) {
    if (casas == 0)
        return;
    printf("Esquerda\n");
    moverRainha(casas - 1);
}

// -------------------------------
// Função: Cavalo
// -------------------------------
// Move em “L” (duas casas para cima, uma para a direita)
// Usa loops aninhados complexos com múltiplas variáveis
// e controle de fluxo (continue e break)
void moverCavalo() {
    int movimentosVerticais = 2;
    int movimentosHorizontais = 1;

    printf("Movimento do Cavalo:\n");

    // Loop externo (for) → controla o movimento vertical
    for (int i = 1, j = 1; i <= movimentosVerticais; i++, j++) {
        printf("Cima\n");

        // Controle de fluxo: pula a iteração se ainda não chegou ao fim do movimento vertical
        if (i < movimentosVerticais) {
            continue;
        }

        // Loop interno (while) → movimento horizontal
        int k = 0;
        while (k < movimentosHorizontais) {
            printf("Direita\n");
            k++;

            // Controle de fluxo: encerra o loop após a última casa
            if (k == movimentosHorizontais) {
                break;
            }
        }
    }
}

// ======================================================
// Função principal (main)
// ======================================================
int main() {
    // Variáveis para definir as distâncias de cada peça
    int casasTorre = 5;
    int casasBispo = 5;
    int casasRainha = 8;

    // ------------------------------
    // Movimento da Torre (Recursão)
    // ------------------------------
    printf("Movimento da Torre:\n");
    moverTorre(casasTorre);
    printf("\n");

    // ------------------------------
    // Movimento do Bispo (Recursão + Loops Aninhados)
    // ------------------------------
    printf("Movimento do Bispo:\n");
    moverBispo(casasBispo, casasBispo);
    printf("\n");

    // ------------------------------
    // Movimento da Rainha (Recursão)
    // ------------------------------
    printf("Movimento da Rainha:\n");
    moverRainha(casasRainha);
    printf("\n");

    // ------------------------------
    // Movimento do Cavalo (Loops Complexos)
    // ------------------------------
    moverCavalo();

    // Finaliza o programa
    return 0;
}
