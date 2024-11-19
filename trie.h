#ifndef TRIE_H
#define TRIE_H

#define NUM_KEYS 9

typedef struct TrieNode {
    char *word; /* ponteiro para a chave guardada no nodo */
    struct TrieNode *children[NUM_KEYS]; /* struct que guarda o vetor de ponteiros para os proximos nodos*/
} TrieNode;

/* cria e inicializa uma nova Trie, retorna um ponteiro para o nodo criado */
TrieNode *createTrieNode();

/* Recebe uma sequencia numerica numeric_sequence e insere a palavra word no caminho correspondente a sequencia  */
void insertWord(TrieNode *root, const char *word, const char *numeric);

/* Busca uma sequência numerica na arvore e retorna a palavra encontrada. A funcao tambem considera os pulos (quantidade de #) caso a palavra esteja contida numa lista ligada*/
char *searchWord(TrieNode *root, const char *numeric, int occurrence);

/* funcao para liberar a memoria de uma arvore Trie */
void freeTrie(TrieNode *root);

#endif
