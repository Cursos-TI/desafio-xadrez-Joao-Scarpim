#include <stdio.h>

/* Tamanho do tabuleiro */
#define LIN 10
#define COL 10

/* Valores usados no tabuleiro */
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define NAVIO_HABILIDADE 8

int main() {

    /* ----------------------------
       1) Inicialização do tabuleiro
       ---------------------------- */
    int tabuleiro[LIN][COL];
    for (int linha = 0; linha < LIN; linha++) {
        for (int coluna = 0; coluna < COL; coluna++) {
            tabuleiro[linha][coluna] = AGUA;  // água inicialmente
        }
    }

    /* ----------------------------
       2) Definição dos navios (tamanho = 3)
       ---------------------------- */
    const int TAM_NAVIO = 3;

    // Navio 1: horizontal (linha 1, coluna 1)
    int navio1_linha = 1, navio1_coluna = 1;
    int navio1_orientacao = 0; // 0 = horizontal, 1 = vertical, 2 = diagonal_down_right, 3 = diagonal_up_right

    // Navio 2: vertical (linha 4, coluna 6)
    int navio2_linha = 4, navio2_coluna = 6;
    int navio2_orientacao = 1;

    // Navio 3: diagonal down-right (linha 7, coluna 0)
    int navio3_linha = 7, navio3_coluna = 0;
    int navio3_orientacao = 2;

    // Navio 4: diagonal up-right (linha 2, coluna 7)
    int navio4_linha = 2, navio4_coluna = 7;
    int navio4_orientacao = 3;

    // Macro para verificar se posição está dentro do tabuleiro
    #define POSICAO_VALIDA(r,c) ((r) >= 0 && (r) < LIN && (c) >= 0 && (c) < COL)

    // Função para testar se um navio pode ser colocado
    int pode_colocar_navio(int start_linha, int start_coluna, int orientacao) {
        int linha = start_linha;
        int coluna = start_coluna;

        for (int k = 0; k < TAM_NAVIO; k++) {
            if (!POSICAO_VALIDA(linha, coluna)) return 0; // fora do tabuleiro
            if (tabuleiro[linha][coluna] != AGUA) return 0; // posição já ocupada

            // Avança para a próxima posição
            if (orientacao == 0) coluna++;            // horizontal
            else if (orientacao == 1) linha++;       // vertical
            else if (orientacao == 2) { linha++; coluna++; } // diagonal down-right
            else if (orientacao == 3) { linha--; coluna++; } // diagonal up-right
            else return 0;
        }
        return 1; // pode colocar
    }

    // Função para posicionar o navio (assume que já foi validado)
    void colocar_navio(int start_linha, int start_coluna, int orientacao) {
        int linha = start_linha;
        int coluna = start_coluna;

        for (int k = 0; k < TAM_NAVIO; k++) {
            tabuleiro[linha][coluna] = NAVIO;

            if (orientacao == 0) coluna++;
            else if (orientacao == 1) linha++;
            else if (orientacao == 2) { linha++; coluna++; }
            else if (orientacao == 3) { linha--; coluna++; }
        }
    }

    // Coloca os 4 navios
    if (pode_colocar_navio(navio1_linha, navio1_coluna, navio1_orientacao))
        colocar_navio(navio1_linha, navio1_coluna, navio1_orientacao);
    else { printf("Erro: não foi possível posicionar Navio 1\n"); return 1; }

    if (pode_colocar_navio(navio2_linha, navio2_coluna, navio2_orientacao))
        colocar_navio(navio2_linha, navio2_coluna, navio2_orientacao);
    else { printf("Erro: não foi possível posicionar Navio 2\n"); return 1; }

    if (pode_colocar_navio(navio3_linha, navio3_coluna, navio3_orientacao))
        colocar_navio(navio3_linha, navio3_coluna, navio3_orientacao);
    else { printf("Erro: não foi possível posicionar Navio 3\n"); return 1; }

    if (pode_colocar_navio(navio4_linha, navio4_coluna, navio4_orientacao))
        colocar_navio(navio4_linha, navio4_coluna, navio4_orientacao);
    else { printf("Erro: não foi possível posicionar Navio 4\n"); return 1; }

    /* ----------------------------
       3) Construção das matrizes de habilidade (5x5)
       ---------------------------- */
    const int TAM_HABILIDADE = 5;
    int meio = TAM_HABILIDADE / 2;

    int habilidade_cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidade_cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidade_octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa todas as matrizes com 0
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++) {
            habilidade_cone[linha][coluna] = 0;
            habilidade_cruz[linha][coluna] = 0;
            habilidade_octaedro[linha][coluna] = 0;
        }
    }

    // ---- Cone: topo no centro, expande para baixo ----
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        int alcance = linha; // largura do cone na linha atual
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++) {
            if (coluna >= (meio - alcance) && coluna <= (meio + alcance))
                habilidade_cone[linha][coluna] = 1;
        }
    }

    // ---- Cruz: linha e coluna do centro ----
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++) {
            if (linha == meio || coluna == meio)
                habilidade_cruz[linha][coluna] = 1;
        }
    }

    // ---- Octaedro: losango central ----
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++) {
            int distancia = (linha > meio ? linha - meio : meio - linha) +
                            (coluna > meio ? coluna - meio : meio - coluna);
            if (distancia <= meio)
                habilidade_octaedro[linha][coluna] = 1;
        }
    }

    /* ----------------------------
       4) Pontos de origem das habilidades no tabuleiro
       ---------------------------- */
    int origem_cone_linha = 2, origem_cone_coluna = 2;
    int origem_cruz_linha = 5, origem_cruz_coluna = 5;
    int origem_octaedro_linha = 1, origem_octaedro_coluna = 7;

    /* ----------------------------
       5) Sobreposição das habilidades
       ---------------------------- */
    void aplicar_habilidade(int hmat[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
        for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
            for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++) {
                if (hmat[linha][coluna] == 1) {
                    int board_linha = origem_linha + (linha - meio);
                    int board_coluna = origem_coluna + (coluna - meio);

                    if (!POSICAO_VALIDA(board_linha, board_coluna))
                        continue;

                    if (tabuleiro[board_linha][board_coluna] == AGUA)
                        tabuleiro[board_linha][board_coluna] = HABILIDADE;
                    else if (tabuleiro[board_linha][board_coluna] == NAVIO)
                        tabuleiro[board_linha][board_coluna] = NAVIO_HABILIDADE;
                }
            }
        }
    }

    aplicar_habilidade(habilidade_cone, origem_cone_linha, origem_cone_coluna);
    aplicar_habilidade(habilidade_cruz, origem_cruz_linha, origem_cruz_coluna);
    aplicar_habilidade(habilidade_octaedro, origem_octaedro_linha, origem_octaedro_coluna);

    /* ----------------------------
       6) Exibir tabuleiro final
       ---------------------------- */
    printf("\nTABULEIRO FINAL (LINHAS x COLUNAS)\n");
    printf("Legenda: 0=Agua  3=Navio  5=Area Habilidade  8=Navio+Area\n\n");

    // Cabeçalho das colunas
    printf("    ");
    for (int coluna = 0; coluna < COL; coluna++)
        printf("%2d ", coluna);
    printf("\n");

    // Linha separadora
    printf("    ");
    for (int coluna = 0; coluna < COL; coluna++) printf("---");
    printf("\n");

    for (int linha = 0; linha < LIN; linha++) {
        printf("%2d |", linha);
        for (int coluna = 0; coluna < COL; coluna++) {
            printf(" %d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    /* ----------------------------
       7) Exibir matrizes de habilidade (opcional)
       ---------------------------- */
    printf("\nMATRIZ HABILIDADE - CONE (1 = afeta):\n");
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++)
            printf("%d ", habilidade_cone[linha][coluna]);
        printf("\n");
    }

    printf("\nMATRIZ HABILIDADE - CRUZ (1 = afeta):\n");
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++)
            printf("%d ", habilidade_cruz[linha][coluna]);
        printf("\n");
    }

    printf("\nMATRIZ HABILIDADE - OCTAEDRO (1 = afeta):\n");
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        for (int coluna = 0; coluna < TAM_HABILIDADE; coluna++)
            printf("%d ", habilidade_octaedro[linha][coluna]);
        printf("\n");
    }

    printf("\nFim do programa.\n");
    return 0;
}
