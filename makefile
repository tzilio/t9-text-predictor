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

clean:
	rm -f *.o $(TARGET)
