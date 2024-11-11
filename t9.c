#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

// Função para traduzir uma palavra em uma sequência T9
void translateToT9(const char *word, char *sequence) {
    const char *map = "22233344455566677778889999";
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            sequence[i] = map[word[i] - 'a'];
        } else {
            sequence[i] = '\0';
            break;
        }
    }
}

// Carrega o dicionário e constrói a trie
void loadDictionary(TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo do dicionário.\n");
        exit(1);
    }
    char word[51], sequence[51];
    while (fscanf(file, "%50s", word) == 1) {
        translateToT9(word, sequence);
        insertWord(root, word, sequence);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s dicionario.txt < consulta.txt > saida.txt\n", argv[0]);
        return 1;
    }

    TrieNode *root = createTrieNode();
    loadDictionary(root, argv[1]);

    char input[51];
    int skip_count = 0;
    while (scanf("%50s", input) == 1) {
        if (strcmp(input, "0") == 0) break;
        if (input[0] == '#') {
            skip_count++;
        } else {
            printf("%s\n", searchWord(root, input, skip_count));
            skip_count = 0;
        }
    }

    freeTrie(root);
    return 0;
}
