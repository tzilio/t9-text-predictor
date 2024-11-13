// trie.c

#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para criar um novo nó da trie
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

// Função para inserir uma palavra na trie
void insertWord(TrieNode *root, const char *word, const char *numeric) {
    TrieNode *current = root;
    for (int i = 0; numeric[i] != '\0'; i++) {
        int digit = numeric[i] - '0';
        if (digit < 0 || digit > 9) {
            fprintf(stderr, "Sequência numérica inválida: %s\n", numeric);
            return;
        }
        if (current->children[digit] == NULL) {
            current->children[digit] = createTrieNode();
        }
        current = current->children[digit];
    }
    // Verifica se já existe uma palavra armazenada neste nó
    if (current->word == NULL) {
        current->word = strdup(word);
        if (!current->word) {
            fprintf(stderr, "Erro ao alocar memória para a palavra.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // Adiciona a nova palavra na lista encadeada usando 'next'
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

// Função para buscar uma palavra na trie com base na sequência numérica e na ocorrência de '#'
char* searchWord(TrieNode *root, const char *numeric, int occurrence) {
    TrieNode *current = root;
    for (int i = 0; numeric[i] != '\0'; i++) {
        int digit = numeric[i] - '0';
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

// Função para liberar a memória da trie
void freeTrie(TrieNode *root) {
    if (root == NULL) return;
    for (int i = 0; i < 10; i++) {
        freeTrie(root->children[i]);
    }
    if (root->word) {
        free(root->word);
    }
    free(root);
}
