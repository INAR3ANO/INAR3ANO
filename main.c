#include <stdio.h>
#include <stdlib.h>
// Estrutura de um no da arvore
struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
};

// Funcaoo para criar um novo no
struct No* criarNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}
// Funcaoo principal
int main() {
    // Raiz da �rvore
    struct No* raiz = NULL;

    // Adiciona os 20 elementos 
    struct No* novoNo1 = criarNo(1);
    struct No* novoNo2 = criarNo(2);
    struct No* novoNo3 = criarNo(3);
    struct No* novoNo4 = criarNo(4);
    struct No* novoNo5 = criarNo(5);
    struct No* novoNo6 = criarNo(6);
    struct No* novoNo7 = criarNo(7);
    struct No* novoNo8 = criarNo(8);
    struct No* novoNo9 = criarNo(9);
    struct No* novoNo10 = criarNo(10);
    struct No* novoNo11 = criarNo(11);
    struct No* novoNo12 = criarNo(12);
    struct No* novoNo13 = criarNo(13);
    struct No* novoNo14 = criarNo(14);
    struct No* novoNo15 = criarNo(15);
    struct No* novoNo16 = criarNo(16);
    struct No* novoNo17 = criarNo(17);
    struct No* novoNo18 = criarNo(18);
    struct No* novoNo19 = criarNo(19);
    struct No* novoNo20 = criarNo(20);

    // Adicionando os novos nos a arvore
    raiz = novoNo1;
    novoNo1->esquerda = novoNo2;
    novoNo1->direita = novoNo3;
    novoNo2->esquerda = novoNo4;
    novoNo2->direita = novoNo5;
    novoNo3->esquerda = novoNo6;
    novoNo3->direita = novoNo7;
    novoNo4->esquerda = novoNo8;
    novoNo4->direita = novoNo9;
    novoNo5->esquerda = novoNo10;
    novoNo5->direita = novoNo11;
    novoNo6->esquerda = novoNo12;
    novoNo6->direita = novoNo13;
    novoNo7->esquerda = novoNo14;
    novoNo7->direita = novoNo15;
    novoNo8->esquerda = novoNo16;
    novoNo8->direita = novoNo17;
    novoNo9->esquerda = novoNo18;
    novoNo9->direita = novoNo19;
    novoNo10->esquerda = novoNo20;



    int profundidade = 0;
    imprimirArvorePorProfundidade(raiz, profundidade);

    return 0;
}

// Funcaoo para imprimir a arvore por profundidade
void imprimirArvorePorProfundidade(struct No* no, int profundidade) {
    if (no != NULL) {
        // Imprime o na na profundidade atual
        printf("%d (%d)\n", no->valor, profundidade);

        // Imprime os nos da subarvore esquerda na profundidade + 1
        imprimirArvorePorProfundidade(no->esquerda, profundidade + 1);

        // Imprime os nos da subarvore direita na profundidade + 1
        imprimirArvorePorProfundidade(no->direita, profundidade + 1);
    }
}
// Funcaoo para imprimir a arvore por largura
void imprimirArvorePorLargura(struct No* raiz) {
    if (raiz == NULL) {
        return;
    }

    struct No* fila[20];
    int inicio = 0;
    int fim = 0;
    fila[fim++] = raiz;

    while (inicio < fim) {
        struct No* no = fila[inicio++];
        printf("%d ", no->valor);

        if (no->esquerda != NULL) {
            fila[fim++] = no->esquerda;
        }

        if (no->direita != NULL) {
            fila[fim++] = no->direita;
        }
    }
}// Funcaoo para buscar por profundidade um no com valor x, encontrando os varios caminhos para ele, e empilhando de forma repetida os elementos deste caminho nos devidos n�s.
void buscarPorProfundidade(struct No* raiz, int valor, struct No* anterior, struct No* pilha[], int topo) {
    if (raiz == NULL) {
        return;
    }

    pilha[++topo] = raiz;

    if (raiz->valor == valor) {
        // Encontramos o no com valor x
        printf("Os caminhos para o no com valor %d sao: \n", valor);
        while (topo >= 0) {
            printf("%d ", pilha[topo--]->valor);
        }
        printf("\n");
    } else {
        buscarPorProfundidade(raiz->esquerda, valor, raiz, pilha, topo);
        buscarPorProfundidade(raiz->direita, valor, raiz, pilha, topo);
    }
}


