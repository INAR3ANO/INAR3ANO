#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Paulo Tivane e Marcelo Tesai
struct Movimento {
    bool esquerda, direita, para_cima, para_baixo;
};
typedef struct Movimento Movimento;

struct Lista;
struct Arvore;

struct Lista {
    struct Arvore * valor;
    struct Lista * proximo;
};
typedef struct Lista Lista;

struct Arvore {
    int tabuleiro[3][3];
    struct Arvore * pai;
    Lista * ancestrais;
    Lista * descendentes;
};
typedef struct Arvore Arvore;

void adicionar_final(Lista ** lista, Lista * novo) {
    novo->proximo = NULL;
    if (*lista) {
        Lista *ultimo = *lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novo;
    } else {
        *lista = novo;
    }
}

void empilhar(Lista ** lista, Lista * novo) {
    adicionar_final(lista, novo);
}

Lista * remover_inicio(Lista ** lista) {
    if (*lista) {
        Lista *elemento = *lista;
        *lista = (*lista)->proximo;
        elemento->proximo = NULL;
        return elemento;
    }
    return NULL;
}

Lista * desempilhar(Lista ** lista) {
    return remover_inicio(lista);
}

Lista * criar_no_lista(Arvore * valor) {
    Lista *novo = malloc(sizeof(Lista));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

void mostrar_matriz(const int matriz[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void copiar_matriz(int destino[3][3], const int origem[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            destino[i][j] = origem[i][j];
}

Arvore * criar_no_arvore(const int matriz[3][3]) {
    Arvore *novo = malloc(sizeof(Arvore));
    novo->pai = NULL;
    novo->descendentes = novo->ancestrais = NULL;
    copiar_matriz(novo->tabuleiro, matriz);
    return novo;
}

bool verificar_igualdade_matriz(const int matriz_a[3][3], const int matriz_b[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz_a[i][j] != matriz_b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool verificar_existencia(Lista * lista, int matriz[3][3]) {
    for (Lista * i = lista; i; i = i->proximo)
        if (verificar_igualdade_matriz(i->valor->tabuleiro, matriz))
            return true;
    return false;
}

bool teste_de_objetivo(Arvore * no) {
    if (!no)
        return false;
    static const int solucao[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    return verificar_igualdade_matriz(no->tabuleiro, solucao);
}

void encontrar_espaco_vazio(const int matriz[3][3], int * linha, int * coluna) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] == 0) {
                *linha = i;
                *coluna = j;
            }
        }
    }
}

void mostrar_movimentos(Movimento movimento) {
    printf("Movimentos: ");
    if (movimento.esquerda) printf("esquerda ");
    if (movimento.direita) printf("direita ");
    if (movimento.para_cima) printf("para cima ");
    if (movimento.para_baixo) printf("para baixo ");
}

Movimento calcular_movimento(int linha, int coluna) {
    Movimento mov = {
        .esquerda = coluna > 0,
        .direita = coluna < 2,
        .para_cima = linha > 0,
        .para_baixo = linha < 2
    };
    return mov;
}

Arvore * criar_no_movimentando(const int matriz[3][3], int origem_linha, int origem_coluna, int destino_linha, int destino_coluna) {
    int nova_matriz[3][3];
    copiar_matriz(nova_matriz, matriz);
    int aux = nova_matriz[origem_linha][origem_coluna];
    nova_matriz[origem_linha][origem_coluna] = nova_matriz[destino_linha][destino_coluna];
    nova_matriz[destino_linha][destino_coluna] = aux;
    return criar_no_arvore(nova_matriz);
}

Lista * gerar_matrizes(const int matriz[3][3], Movimento movimentos, int linha, int coluna) {
    Lista * descendentes = NULL;
    if (movimentos.esquerda)
        adicionar_final(&descendentes, criar_no_lista(criar_no_movimentando(matriz, linha, coluna, linha, coluna - 1)));
    if (movimentos.direita)
        adicionar_final(&descendentes, criar_no_lista(criar_no_movimentando(matriz, linha, coluna, linha, coluna + 1)));
    if (movimentos.para_cima)
        adicionar_final(&descendentes, criar_no_lista(criar_no_movimentando(matriz, linha, coluna, linha - 1, coluna)));
    if (movimentos.para_baixo)
        adicionar_final(&descendentes, criar_no_lista(criar_no_movimentando(matriz, linha, coluna, linha + 1, coluna)));
    return descendentes;
}

Lista * modelo_de_transicao(Arvore * no) {
    int linha, coluna;
    encontrar_espaco_vazio(no->tabuleiro, &linha, &coluna);
    Movimento movimentos = calcular_movimento(linha, coluna);
    Lista * lista = gerar_matrizes(no->tabuleiro, movimentos, linha, coluna), * lista_final = NULL;
    Lista * no_atual;
    while ((no_atual = remover_inicio(&lista))) {
        if (!verificar_existencia(no->ancestrais, no_atual->valor->tabuleiro)) {
            adicionar_final(&lista_final, no_atual);
        } else {
            free(no_atual);
        }
    }
    return lista_final;
}

void criar_caminho_tabuleiros(Arvore * no) {
    Arvore * original = no;
    while (no->pai) {
        no = no->pai;
        empilhar(&original->ancestrais, criar_no_lista(no));
    }
}

Arvore * buscar_solucao(Arvore * no, bool * solucao, int contador, int limite) {
    if (teste_de_objetivo(no)) {
        criar_caminho_tabuleiros(no);
        printf("Solucao encontrada\n");
        *solucao = true;
        return no;
    } else if (!(*solucao) && contador < limite) {
        Arvore * solucao_atual;
        criar_caminho_tabuleiros(no);
        no->descendentes = modelo_de_transicao(no);
        for (Lista * i = no->descendentes; i; i = i->proximo) {
            i->valor->pai = no;
            solucao_atual = buscar_solucao(i->valor, solucao, contador + 1, limite);
            if (solucao_atual)
                return solucao_atual;
        }
    }
    return NULL;
}

void mostrar_caminho(Arvore * no) {
    int c = 0;
    for (Lista * i = no->ancestrais; i; i = i->proximo) {
        c++;
        printf(".\n");
        mostrar_matriz(i->valor->tabuleiro);
    }
    printf("\n%d", c);
}

int main() {
    int tabuleiro[3][3] = {
        {1, 0, 3},
        {4, 5, 6},
        {7, 2, 8}
    };
    bool solucao_encontrada = false;
    Arvore * no = criar_no_arvore(tabuleiro);
    Arvore * solucao = buscar_solucao(no, &solucao_encontrada, 0, 10); // Increased the search limit
    printf("\n");
    mostrar_caminho(solucao);
    printf("\n");
    mostrar_matriz(solucao->tabuleiro);
    return 0;
}
