#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

// Criação de um novo nó
TrieNode *createTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    for (int i = 0; i < 10; i++) {
        node->children[i] = NULL;
    }
    node->word = NULL;
    node->next = NULL;
    return node;
}

// Inserção de uma palavra
void insertWord(TrieNode *root, const char *word, const char *numeric_sequence) {
    TrieNode *current = root;
    for (int i = 0; numeric_sequence[i] != '\0'; i++) {
        int index = numeric_sequence[i] - '0';
        if (!current->children[index]) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }

    if (current->word) {
        TrieNode *newNode = createTrieNode();
        newNode->word = strdup(word);
        newNode->next = current->next;
        current->next = newNode;
    } else {
        current->word = strdup(word);
    }
}

// Busca por palavra usando a sequência
char *searchWord(TrieNode *root, const char *numeric_sequence, int skip_count) {
    TrieNode *current = root;
    for (int i = 0; numeric_sequence[i] != '\0'; i++) {
        int index = numeric_sequence[i] - '0';
        if (!current->children[index]) {
            return "palavra nao encontrada";
        }
        current = current->children[index];
    }
    while (skip_count-- > 0 && current) {
        current = current->next;
    }
    return current && current->word ? current->word : "palavra nao encontrada";
}

// Liberação da memória da Trie
void freeTrie(TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < 10; i++) {
        freeTrie(root->children[i]);
    }
    free(root->word);
    freeTrie(root->next);
    free(root);
}
