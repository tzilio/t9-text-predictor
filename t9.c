#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

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
    sequence[strlen(word)] = '\0';
}

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
    if (argc < 2) {
        fprintf(stderr, "Uso: %s dicionario.txt < consulta.txt > saida.txt\n", argv[0]);
        return 1;
    }

    TrieNode *root = createTrieNode();
    loadDictionary(root, argv[1]);

    char input[51];
    char last_sequence[51] = "";
    int skip_count = 0;

    while (scanf("%50s", input) == 1) {
        if (strcmp(input, "0") == 0) break;

        int length = strlen(input);
        int is_valid = 1;
        for (int i = 0; i < length; i++) {
            if ((input[i] < '2' || input[i] > '9') && input[i] != '#') {
                is_valid = 0;
                break;
            }
        }

        if (!is_valid) {
            printf("entrada invalida\n");
            continue;
        }

        skip_count = 0;
        while (length > 0 && input[length - 1] == '#') {
            skip_count++;
            input[--length] = '\0';
        }

        if (length > 0) {
            strcpy(last_sequence, input);
        }

        char *result = searchWord(root, last_sequence, skip_count);
        if (result) {
            printf("%s\n", result);
        } else {
            printf("palavra nao encontrada\n");
        }
    }

    freeTrie(root);
    return 0;
}


