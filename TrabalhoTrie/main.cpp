// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado
// Revision by Álvaro Certo

#include <iostream>
#include <fstream>
#include "Trie.h"
using namespace std;

// Método para tratar a leitura do arquivo .dic
DicEntry parseDicEntry(ifstream &fin) {
    DicEntry result{};

    // cria-se uma variável para armazenar o caracter a ser comparado em busca das tags de abertura da palavra
    char newCh;
    // armazena a posição de início da palavra
    result.posicao = (int)fin.tellg() - 1;
    //armazena o comprimento da palavra, assumindo-se que ja foi lido o '[', que é a tag de abertura
    result.comprimento = 1;
    // laço que avalia caracteres um a um até que a tag seja fechada, identificando a palavra
    while ((newCh = fin.get()) != ']' && !fin.eof()) {
        result.key += newCh;
        result.comprimento++;
    }

    // laço que avalia o fim da linha, ignorando falsos fechamentos e aberturas de tag, e popula o comprimento.
    while (!fin.eof() && (newCh = fin.get()) != '\n' || (fin.get() == '\n' && fin.get() != '[')) {
        result.comprimento++;
    }
    result.comprimento++;

    /* este recurso é utilizado para o ifstream voltar uma posição no arquivo, pois foi realizada uma
     * verificação para evitar falsos fechamentos e aberturas de tag, mas o método deve ser capaz de verificar
     * a abertura da próxima palavra corretamente e também quando o arquivo terminou
     */
    if (!fin.eof()) {
        fin.seekg(-1, fin.cur);
    }

    return result;
}

int main() {
    ifstream fin;
    // variável para receber o nome do arquivo
    string filename;
    // variável para receber a palavra a ser verificada
    string word;

    cout << "digite o nome do arquivo" << endl;

    // entrada do programa
    cin >> filename;
    //abre o arquivo
    fin.open(filename, ios::in);

    struct TrieNode *root = getNode(); // cria um nodo com raiz vazia para iniciar a árvore Trie

    // armazena-se o caracter a verificar
    char ch;
    // Enquanto não chegar o fim do arquivo, obtém o próximo caractere e verifica se é uma abertura de palavra
    while (!fin.eof() ) {
        fin.get(ch);
        // se for uma abertura de palavra, chama o método específico para fazer o parse da palavra
        if (ch=='[') {
            DicEntry dicEntry = parseDicEntry(fin);

            /* Após o método "parseDicEntry" verificar a palavra, a posição de início da linha e
             * a quantidade de caracteres, passa esses dados para o método insert da classe Trie
             */
            insert(root, dicEntry);
        }
    }

    // leitura das palavras ate' encontrar "0"
    while (1) {
        cin >> word; // 
        // se a entrada for o caractere "0", pára a execução do programa e o main retorna 0
        if (word.compare("0") == 0) {
            break;
        }
        /* Instancia um objeto do tipo SearchResult que vai armazenar o resultado da busca pela
         * palavra da entrada na árvore montada com o dicionário
         */
        SearchResult *result = search(root, word);
        switch (result->resultadoStatus) {
            case IS_NOT_PREFIX:
                cout << "is not prefix" << endl;
                break;
            case IS_PREFIX:
                cout << "is prefix" << endl;
                break;
            case IS_KEY:
                cout << result->nodo->posicao << " " << result->nodo->comprimento << endl;
                break;
        }
    }
    return 0;
}
