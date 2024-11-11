#ifndef TRIE_H
#define TRIE_H

#define NUM_KEYS 10

typedef struct TrieNode {
    struct TrieNode *children[NUM_KEYS];
    char *word;
    struct TrieNode *next;
} TrieNode;

TrieNode *createTrieNode();
void insertWord(TrieNode *root, const char *word, const char *numeric_sequence);
char *searchWord(TrieNode *root, const char *numeric_sequence, int skip_count);
void freeTrie(TrieNode *root);

#endif
