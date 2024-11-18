#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

TrieNode *createTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    if (node) {
        for (int i = 0; i < NUM_KEYS; i++) {
            node->children[i] = NULL;
        }
        node->word = NULL;
        node->next = NULL;
    }
    return node;
}


void insertWord(TrieNode *root, const char *word, const char *numeric_sequence) {
    TrieNode *current = root;
    int length = strlen(numeric_sequence);

    for (int i = 0; i < length; i++) {
        int index = numeric_sequence[i] - '0'; /* gera o indice para saber qual no acessar para seguir percorrendo a arvore*/
        if (!current->children[index]) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }

    /* checa se o nodo ja esta ocupado por outra palavra, nesse caso inicia uma lista ligada no indice 9 (#)  */
    while (current->word) {
        if (!current->children[9]) {
            current->children[9] = createTrieNode();
        }
        current = current->children[9];
    }

    current->word = strdup(word);
    //printf("Palavra inserida: %s com sequência %s\n", word, numeric_sequence); TESTE
}

char *searchWord(TrieNode *root, const char *numeric_sequence, int skip_count) {
    TrieNode *current = root;
    int length = strlen(numeric_sequence);

    /* percorre a arvore descendo nos niveis ate o fim do tamanho da string da sequencia numerica */
    for (int i = 0; i < length; i++) {
        if (numeric_sequence[i] == '#') {
            continue; // ignora "#"
        }
        
        int index = numeric_sequence[i] - '0'; /* converte o texto para indice inteiro usado para saber qual nodo acessar para continuar percorrendo a arvore */
        if (index < 2 || index > 9 || !current->children[index]) {
            //printf("Sequência %s não encontrada no nível %d\n", numeric_sequence, i);  // TESTE
            return NULL; /* retorna null em caso de entrada invalida */
        }
        current = current->children[index];
    }

    /* chega no final da sequencia numerica e comeca a iterar pela quantidade de pulos na lista ligada */
    for (int i = 0; i < skip_count && current; i++) {
        if (!current->children[9]) {
            //printf("Sem mais alternativas para %s após %d pulos\n", numeric_sequence, i);  // TESTE
            return NULL; /* retorna nulo quando tenta acessar uma posicao nula de memoria */
        }
        current = current->children[9];
    }

    /* checa se o nodo e a palavra existem antes de acessar essa posicao de memoria e retorna o valor */
    if (current && current->word) {
        return current->word;
    } else {
        printf("palavra nao encontrada");
        //printf("Nenhuma palavra encontrada para %s com pulos %d\n", numeric_sequence, skip_count);  // TESTE
        return NULL;
    }
}


/* percorre e libera recursivamente a memoria alocara na arvore Trie */
void freeTrie(TrieNode *root) {
    if (!root) return;

    for (int i = 0; i < NUM_KEYS; i++) {
        freeTrie(root->children[i]);
    }

    if (root->word) {
        free(root->word);
    }

    free(root);
}
