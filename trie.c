#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode* createTrieNode() {
    TrieNode *node = malloc(sizeof(TrieNode));
    if (!node) {
        fprintf(stderr, "Erro ao alocar memória para um nó da Trie.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 9; i++) { // 0-7 para '2-9', 8 para '#'
        node->children[i] = NULL;
    }
    node->word = NULL;
    return node;
}

// obter o índice correspondente ao caractere
int getIndex(char c) {
    if (c >= '2' && c <= '9') {
        return c - '2'; 
    } else if (c == '#') {
        return 8;
    } else {
        return -1;
    }
}

void insertWord(TrieNode *root, const char *word, const char *numeric) {
    TrieNode *current = root;

    for (int i = 0; numeric[i] != '\0'; i++) {
        int index = getIndex(numeric[i]);
        if (index == -1) {
            fprintf(stderr, "Sequência inválida: %s\n", numeric);
            return;
        }

        if (current->children[index] == NULL) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }

    if (current->word == NULL) {
        current->word = strdup(word);
        if (!current->word) {
            fprintf(stderr, "Erro ao alocar memória para a palavra.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // Encadeamento usando índice para '#'
        if (current->children[8] == NULL) {
            current->children[8] = createTrieNode();
            current->children[8]->word = strdup(word);
            if (!current->children[8]->word) {
                fprintf(stderr, "Erro ao alocar memória para a palavra.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            TrieNode *temp = current->children[8];
            while (temp->children[8] != NULL) {
                temp = temp->children[8];
            }
            temp->children[8] = createTrieNode();
            temp->children[8]->word = strdup(word);
            if (!temp->children[8]->word) {
                fprintf(stderr, "Erro ao alocar memória para a palavra.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char* searchWord(TrieNode *root, const char *numeric, int occurrence) {
    TrieNode *current = root;

    for (int i = 0; numeric[i] != '\0'; i++) {
        int index = getIndex(numeric[i]);
        if (index == -1) {
            fprintf(stderr, "Entrada inválida\n");
            return NULL;
        }
        if (current->children[index] == NULL) return NULL;
        current = current->children[index];
    }

    int count = 1;
    if (current->word == NULL) return NULL;

    if (occurrence == 1) return current->word;

    TrieNode *temp = current->children[8];
    while (temp != NULL && count < occurrence) {
        if (temp->word != NULL) {
            count++;
            if (count == occurrence) return temp->word;
        }
        temp = temp->children[8];
    }

    return NULL;
}

void freeTrie(TrieNode *node) {
    if (node == NULL) return;

    for (int i = 0; i < 9; i++) {
        if (node->children[i] != NULL) {
            freeTrie(node->children[i]);
        }
    }

    if (node->word != NULL) {
        free(node->word);
    }
    free(node);
}
