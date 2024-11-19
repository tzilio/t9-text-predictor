#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode* createTrieNode() {
    TrieNode *node = (TrieNode*) malloc(sizeof(TrieNode));
    if (!node) {
        fprintf(stderr, "Erro ao alocar memória para novo nó da trie.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 10; i++) {
        node->children[i] = NULL;
    }
    node->word = NULL;
    node->next = NULL;
    return node;
}

void insertWord(TrieNode *root, const char *word, const char *numeric) {
    TrieNode *current = root;
    for (int i = 0; numeric[i] != '\0'; i++) {
        int digit = numeric[i] - '0';   /* gera o indice para saber qual no acessar para seguir percorrendo a arvore*/
        if (digit < 0 || digit > 9) {
            fprintf(stderr, "Sequência numérica inválida: %s\n", numeric);
            return;
        }
        if (current->children[digit] == NULL) {
            current->children[digit] = createTrieNode();
        }
        current = current->children[digit];
    }
    
    /* checa se o nodo ja esta ocupado por outra palavra, nesse caso inicia uma lista ligada */
    if (current->word == NULL) {
        current->word = strdup(word);
        if (!current->word) {
            fprintf(stderr, "Erro ao alocar memória para a palavra.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        TrieNode *temp = current;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = createTrieNode();
        temp->next->word = strdup(word);
        if (!temp->next->word) {
            fprintf(stderr, "Erro ao alocar memória para a palavra.\n");
            exit(EXIT_FAILURE);
        }
    }
}

char* searchWord(TrieNode *root, const char *numeric, int occurrence) {
    TrieNode *current = root;
    for (int i = 0; numeric[i] != '\0'; i++) {
        int digit = numeric[i] - '0';  /* converte o texto para indice inteiro usado para saber qual nodo acessar para continuar percorrendo a arvore */
        if (digit < 0 || digit > 9) {
            return NULL;
        }
        if (current->children[digit] == NULL) {
            return NULL;
        }
        current = current->children[digit];
    }
    // Navega na lista encadeada para a ocorrência desejada
    while (current != NULL && occurrence > 0) {
        current = current->next;
        occurrence--;
    }
    if (current != NULL && current->word != NULL) {
        return current->word;
    }
    return NULL;
}

void freeTrie(TrieNode *root) {
    if (root == NULL) return;

    for (int i = 0; i < 10; i++) {
        freeTrie(root->children[i]);
    }

    // Libera a lista encadeada associada ao nó atual
    TrieNode *current = root->next;
    while (current != NULL) {
        TrieNode *temp = current;
        current = current->next;
        if (temp->word) {
            free(temp->word);
        }
        free(temp);
    }

    if (root->word) {
        free(root->word);
    }

    free(root);
}
