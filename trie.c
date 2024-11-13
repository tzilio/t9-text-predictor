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

// Inserir palavra usando seq numérica
void insertWord(TrieNode *root, const char *word, const char *numeric_sequence) {
    TrieNode *current = root;
    int length = strlen(numeric_sequence);

    for (int i = 0; i < length; i++) {
        int index = numeric_sequence[i] - '0'; // Converte caractere para índice numérico
        if (!current->children[index]) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }

    // verifica se há conflito de sequencia
    while (current->word) {
        // se existe, cria um novo nó no índice 9 ('#')
        if (!current->children[9]) {
            current->children[9] = createTrieNode();
        }
        current = current->children[9];
    }

    current->word = strdup(word);
    //printf("Palavra inserida: %s com sequência %s\n", word, numeric_sequence); TESTE
}

// buscar palavra pela seq numérica ou "pular" palavras na lista
char *searchWord(TrieNode *root, const char *numeric_sequence, int skip_count) {
    TrieNode *current = root;
    int length = strlen(numeric_sequence);

    for (int i = 0; i < length; i++) {
        if (numeric_sequence[i] == '#') {
            continue; // ignora "#"
        }
        
        int index = numeric_sequence[i] - '0';
        if (index < 2 || index > 9 || !current->children[index]) {
            //printf("Sequência %s não encontrada no nível %d\n", numeric_sequence, i);  // TESTE
            return NULL;
        }
        current = current->children[index];
    }

    for (int i = 0; i < skip_count && current; i++) {
        if (!current->children[9]) {
            //printf("Sem mais alternativas para %s após %d pulos\n", numeric_sequence, i);  // TESTE
            return NULL;
        }
        current = current->children[9];
    }

    if (current && current->word) {
        //printf("Palavra encontrada: %s com sequência %s e pulos %d\n", current->word, numeric_sequence, skip_count);  // TESTE
        //printf("%s", current->word);
        return current->word;
    } else {
        printf("palavra nao encontrada");
        //printf("Nenhuma palavra encontrada para %s com pulos %d\n", numeric_sequence, skip_count);  // TESTE
        return NULL;
    }
}


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
