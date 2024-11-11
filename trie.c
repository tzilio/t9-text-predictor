#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

// Função para criar um novo nó da Trie
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

// Função para inserir uma palavra na Trie usando a sequência numérica associada
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

    // Verifica se o nó já contém uma palavra (ou seja, conflito de sequência)
    while (current->word) {
        // Se já existe uma palavra, criamos um novo nó no índice 9 (representando '#')
        if (!current->children[9]) {
            current->children[9] = createTrieNode();
        }
        current = current->children[9];
    }

    // Armazena a palavra no nó disponível
    current->word = strdup(word);
    //printf("Palavra inserida: %s com sequência %s\n", word, numeric_sequence);  // Depuração
}

// Função para buscar uma palavra com base na sequência numérica e "pular" palavras na lista
char *searchWord(TrieNode *root, const char *numeric_sequence, int skip_count) {
    TrieNode *current = root;
    int length = strlen(numeric_sequence);

    // Navega pela sequência numérica
    for (int i = 0; i < length; i++) {
        if (numeric_sequence[i] == '#') {
            // Caso encontre um '#' dentro da sequência, deve ignorá-lo
            continue;
        }
        
        int index = numeric_sequence[i] - '0';
        if (index < 2 || index > 9 || !current->children[index]) {
            //printf("Sequência %s não encontrada no nível %d\n", numeric_sequence, i);  // Depuração
            return NULL; // Caminho não encontrado
        }
        current = current->children[index];
    }

    // Avança na "lista encadeada" representada pelos nós com índice '#'
    for (int i = 0; i < skip_count && current; i++) {
        if (!current->children[9]) {
            //printf("Sem mais alternativas para %s após %d pulos\n", numeric_sequence, i);  // Depuração
            return NULL; // Sem mais alternativas para a sequência
        }
        current = current->children[9];
    }

    if (current && current->word) {
        //printf("Palavra encontrada: %s com sequência %s e pulos %d\n", current->word, numeric_sequence, skip_count);  // Depuração
        //printf("%s", current->word);
        return current->word;
    } else {
        printf("palavra nao encontrada");
        //printf("Nenhuma palavra encontrada para %s com pulos %d\n", numeric_sequence, skip_count);  // Depuração
        return NULL;
    }
}


// Função para liberar toda a memória da Trie
void freeTrie(TrieNode *root) {
    if (!root) return;

    // Libera os nós filhos
    for (int i = 0; i < NUM_KEYS; i++) {
        freeTrie(root->children[i]);
    }

    // Libera a palavra, se existir
    if (root->word) {
        free(root->word);
    }

    // Libera o próprio nó
    free(root);
}
