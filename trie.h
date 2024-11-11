#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct TrieNode {
    struct TrieNode *children[10];
    char *word;  // Palavra armazenada, se houver
    struct TrieNode *next;  // Lista encadeada para palavras com a mesma sequência de teclas
} TrieNode;

// Funções principais
TrieNode *createTrieNode();
void insertWord(TrieNode *root, const char *word, const char *numeric_sequence);
char *searchWord(TrieNode *root, const char *numeric_sequence, int skip_count);
void freeTrie(TrieNode *root);

#endif
