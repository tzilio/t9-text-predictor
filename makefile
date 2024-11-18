CC = gcc
CFLAGS = -Wall -g
TARGET = t9

all: $(TARGET)

$(TARGET): t9.o trie.o
	$(CC) $(CFLAGS) -o $(TARGET) t9.o trie.o

t9.o: t9.c trie.h
	$(CC) $(CFLAGS) -c t9.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

teste: $(TARGET)
	./$(TARGET) mini_dicionario.txt < teste.txt > saida.txt

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) mini_dicionario.txt < teste.txt > saida_valgrind.txt

clean:
	rm -f *.o $(TARGET)
