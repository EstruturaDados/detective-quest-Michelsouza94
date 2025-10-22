#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct Sala
// Representa um cômodo da mansão com nome e ponteiros para filhos esquerdo e direito.
typedef struct Sala {
    char nome[50];          // Nome do cômodo
    struct Sala* esquerda;  // Ponteiro para o cômodo à esquerda
    struct Sala* direita;   // Ponteiro para o cômodo à direita
} Sala;

// Função criarSala: cria, de forma dinâmica, uma sala com nome.
// Aloca memória para uma nova sala e inicializa seus campos.
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função explorarSalas: permite a navegação do jogador pela árvore.
// Começa na raiz e permite escolher esquerda (e) ou direita (d) até um nó-folha ou sair (s).
void explorarSalas(Sala* raiz) {
    Sala* atual = raiz;
    char opcao;
    
    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansao escolhendo caminhos.\n\n");
    
    while (1) {
        // Exibe o cômodo atual
        printf("Voce esta em: %s\n", atual->nome);
        
        // Verifica se é um nó-folha (sem filhos)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Voce chegou ao fim da exploracao! Este comodo nao tem mais caminhos.\n");
            break;
        }
        
        // Exibe opções disponíveis
        printf("Opcoes:\n");
        if (atual->esquerda != NULL) {
            printf("  [E] Ir para a esquerda (%s)\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("  [D] Ir para a direita (%s)\n", atual->direita->nome);
        }
        printf("  [S] Sair da exploracao\n");
        printf("Escolha uma opcao: ");
        
        scanf(" %c", &opcao);  // Lê a opção (espaço antes para ignorar quebras de linha)
        
        // Processa a escolha
        if ((opcao == 'E' || opcao == 'e') && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if ((opcao == 'D' || opcao == 'd') && atual->direita != NULL) {
            atual = atual->direita;
        } else if (opcao == 'S' || opcao == 's') {
            printf("Exploracao encerrada pelo jogador.\n");
            break;
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
        printf("\n");
    }
}

// Função main: monta o mapa inicial e dá início à exploração.
// Cria a árvore binária manualmente e chama explorarSalas().
int main() {
    // Criação da árvore binária representando o mapa da mansão
    Sala* hall = criarSala("Hall de entrada");
    hall->esquerda = criarSala("Sala de estar");
    hall->direita = criarSala("Cozinha");
    
    hall->esquerda->esquerda = criarSala("Jardim");
    hall->esquerda->direita = criarSala("Escritorio");
    
    hall->direita->esquerda = criarSala("Banheiro");
    hall->direita->direita = criarSala("Quarto");
    
    // Inicia a exploração
    explorarSalas(hall);
    
    // Liberação de memória (opcional para simplicidade, mas boa prática)
    // Como é um programa simples, podemos omitir para nível novato, mas incluído para completude
    free(hall->esquerda->esquerda);
    free(hall->esquerda->direita);
    free(hall->esquerda);
    free(hall->direita->esquerda);
    free(hall->direita->direita);
    free(hall->direita);
    free(hall);
    
    return 0;
}