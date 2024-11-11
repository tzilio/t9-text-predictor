# T9 Predictive Text Implementation

## Descrição

Este projeto implementa um sistema de texto preditivo T9 utilizando uma estrutura de dados trie em C. A trie é construída a partir de palavras contidas em um arquivo de dicionário (`dicionario.txt`). Cada palavra é convertida em uma sequência de teclas T9 (números de `2` a `9`), que é usada como chave na trie. O programa lê consultas numéricas de um arquivo (`consulta.txt`) e retorna as palavras correspondentes, permitindo alternar entre palavras com a mesma sequência através do caractere `#`.

## Estrutura de Arquivos

- **t9.c**: Programa principal que gerencia a entrada e saída e utiliza as funções da trie.
- **trie.c**: Implementação das funções de manipulação da estrutura de dados trie.
- **trie.h**: Arquivo de cabeçalho para a trie, contendo definições de tipos e declarações de funções.
- **dicionario.txt**: Arquivo com uma lista de palavras para construção da trie (exemplo incluído no repositório).
- **consulta.txt**: Arquivo com as consultas numéricas que o programa deve processar (exemplo incluído no repositório).
- **Makefile**: Arquivo para facilitar a compilação e limpeza do projeto.
- **README.md**: Documento explicativo do projeto (este arquivo).

## Requisitos

- Compilador GCC para C.
- `make` para facilitar a compilação.
- Sistema operacional Unix/Linux para compatibilidade com o Makefile.

## Instruções de Compilação e Execução

### Compilação

Para compilar o programa, use o comando:

```bash
make
```

Isso irá compilar os arquivos `t9.c` e `trie.c`, gerando o executável `t9`.

### Execução

Para executar o programa, utilize o comando abaixo, onde `dicionario.txt` é o arquivo de dicionário e `consulta.txt` é o arquivo de consultas:

```bash
./t9 dicionario.txt < consulta.txt > saida.txt
```

Esse comando direciona a saída do programa para o arquivo `saida.txt`.

### Limpeza

Para limpar os arquivos objeto e o executável gerados pela compilação, utilize:

```bash
make clean
```

## Formato dos Arquivos de Entrada

### dicionario.txt

O arquivo `dicionario.txt` deve conter uma lista de palavras, uma por linha, para serem usadas na construção da trie. Exemplo:

```plaintext
rocks
socks
sock
rock
pock
jello
book
cool
```

### consulta.txt

O arquivo `consulta.txt` deve conter sequências numéricas para consulta, com números de `2` a `9` e `#` para alternar entre palavras de mesma sequência. O valor `0` encerra as consultas. Exemplo:

```plaintext
76257
#
53556
#
76257#
76257##
7625
##
0
```

## Estrutura de Dados e Funções

A trie é construída para armazenar palavras com base em sequências T9. As principais funções são:

- **createTrieNode()**: Cria um novo nó na trie.
- **insertWord()**: Insere uma palavra na trie com sua sequência numérica.
- **searchWord()**: Realiza a busca de uma palavra com base na sequência e no número de alternâncias (`#`).
- **freeTrie()**: Libera a memória alocada para a trie.

## Exemplo de Uso

Com `dicionario.txt` e `consulta.txt` preenchidos conforme os exemplos acima, execute o programa para obter os resultados em `saida.txt`. Cada linha da saída corresponderá a uma palavra encontrada ou a uma mensagem de erro, como `"palavra nao encontrada"` para consultas inválidas.

## Observações

- O código foi projetado para lidar com arquivos grandes, mas durante o desenvolvimento é recomendável testar com arquivos pequenos para verificar a construção correta da trie.
- Use `valgrind` para verificar possíveis vazamentos de memória, especialmente ao lidar com alocação dinâmica.

## Autor

Este projeto foi desenvolvido por:

Eduardo Faria Kruger e 
Thiago Zilio Assunção;

como parte de um exercício prático para o curso de Algoritmos e Estruturas de Dados III. CI1057 - UFPR.


