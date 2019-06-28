#include <iostream>
#include <fstream>
#include "Trie.h"
using  namespace std;

DicEntry parseDicEntry(ifstream &fin){
    DicEntry result{};

    char newCh;
    result.posicao = (int)fin.tellg() - 1;
    result.comprimento = 1; //ja foi lido o '['
    while((newCh = fin.get()) != ']' && !fin.eof()){
        result.key += newCh;
        result.comprimento++;
    }

    while (!fin.eof() && (newCh = fin.get()) != '\n' || (fin.get() == '\n' && fin.get() != '[')){
        result.comprimento++;
    }
    result.comprimento++;

    if (!fin.eof()) {
        fin.seekg(-1, fin.cur);
    }

    return result;

}

int main()
{
    ifstream fin;
    string filename;
    string word;

    cin >> filename;  // entrada
    fin.open(filename, ios::in);

    struct TrieNode *root = getNode();

    char ch;
    while (!fin.eof() ) {
        fin.get(ch);
        if (ch=='['){
            DicEntry dicEntry = parseDicEntry(fin);
            insert(root, dicEntry);
        }
    }



    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
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














    // Pra cada palavra da entrada, executar o código a seguir:






}