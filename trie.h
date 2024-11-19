#ifndef TRIE_H
#define TRIE_H

#define NUM_KEYS 10

typedef struct TrieNode {

    /* struct que guarda o vetor de ponteiros para os proximos nodos*/
    struct TrieNode *children[NUM_KEYS]; 

    /* ponteiro para a chave guardada no nodo */
    char *word;

    /* ponteiro para um proximo nodo no caso de ter uma lista encadeada na folha (caso #) */
    struct TrieNode *next;

} TrieNode;

/* cria e inicializa uma nova Trie, retorna um ponteiro para o nodo criado */
TrieNode *createTrieNode();

/* Recebe uma sequencia numerica numeric_sequence e insere a palavra word no caminho correspondente a sequencia  */
void insertWord(TrieNode *root, const char *word, const char *numeric_sequence);

/* Busca uma sequência numerica na arvore e retorna a palavra encontrada. A funcao tambem considera os pulos (quantidade de #) caso a palavra estela contida numa lista encadeada*/
char *searchWord(TrieNode *root, const char *numeric_sequence, int skip_count);

/* funcao para liberar a memoria de uma arvore Trie */
void freeTrie(TrieNode *root);

#endif
