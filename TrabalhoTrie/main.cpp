#include <iostream>
#include <fstream>
#include "Trie.h"
using  namespace std;

DicEntry parseDicEntry(ifstream &fin){ // classe para tratar a leitura do arquivo .dic
    DicEntry result{};

    char newCh; // cria-se uma variável para armazenar o caracter à ser comparado em busca das tags de abertura da palavra
    result.posicao = (int)fin.tellg() - 1; // armazena a posição de início da palavra
    result.comprimento = 1; //armazena o comprimento da palavra, assumindo-se que ja foi lido o '[', que é a tag de abertura
    while((newCh = fin.get()) != ']' && !fin.eof()){ // laço que avalia caracteres um a um até que a tag seja fechada, identificando a palavra
        result.key += newCh;
        result.comprimento++;
    }

    while (!fin.eof() && (newCh = fin.get()) != '\n' || (fin.get() == '\n' && fin.get() != '[')){ // laço que avalia o fim da linha, ignorando falsos fechamentos e aberturas de tag, e popula o comprimento.
        result.comprimento++;
    }
    result.comprimento++;

    if (!fin.eof()) { // chegando ao vim do arquivo, interrompe a verificação.
        fin.seekg(-1, fin.cur);
    }

    return result;

}

int main() 
{
    ifstream fin;
    string filename; // variavel para receber o nome do arquivo
    string word; // variável para receber a palavra à ser verificada

    cin >> filename;  // entrada do programa
    fin.open(filename, ios::in); //abre o arquivo

    struct TrieNode *root = getNode(); // cria um nodo com raiz vazia para iniciar a árvore Trie

    char ch; // armazena-se o caracter a verificar 
    while (!fin.eof() ) { // EITA CARAI ESSE LAÇO EU NÃO MANJEI
        fin.get(ch);
        if (ch=='['){
            DicEntry dicEntry = parseDicEntry(fin);
            insert(root, dicEntry);
        }
    }



    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word; // 
        if (word.compare("0") == 0) { 
            break;
        }
        SearchResult *result = search(root, word); // cria um ponteiro na raiz pro resultado das buscas de cada palavra
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