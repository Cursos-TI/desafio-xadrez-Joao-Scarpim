#include <stdio.h>

int main() {
    // ===== TORRE =====
    // A Torre move-se em linha reta (horizontal ou vertical)
    // Aqui vamos simular 5 movimentos para a direita usando um laço for
    int movimentoTorre = 5;

    printf("=== Movimento da Torre ===\n");
    for (int i = 1; i <= movimentoTorre; i++) {
        printf("Direita (%d)\n", i);
    }

    // ===== BISPO =====
    // O Bispo move-se na diagonal
    // Vamos simular 5 movimentos na diagonal superior direita usando um while
    int movimentoBispo = 5;
    int i = 1;

    printf("\n=== Movimento do Bispo ===\n");
    while (i <= movimentoBispo) {
        printf("Cima, Direita (%d)\n", i);
        i++;
    }

    // ===== RAINHA =====
    // A Rainha pode mover-se em todas as direções
    // Vamos simular 8 movimentos para a esquerda usando um do-while
    int movimentoRainha = 8;
    int j = 1;

    printf("\n=== Movimento da Rainha ===\n");
    do {
        printf("Esquerda (%d)\n", j);
        j++;
    } while (j <= movimentoRainha);

    return 0;
}
