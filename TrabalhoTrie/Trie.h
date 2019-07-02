// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado
// Revision by Álvaro Certo

#ifndef TRABALHOTRIE_TRIE_H
#define TRABALHOTRIE_TRIE_H

// C++ implementation of search and insert
// operations on Trie
#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;
const int IS_NOT_PREFIX = 0;
const int IS_PREFIX = 1;
const int IS_KEY = 2;

// Declaração do struct de entrada de dicionário
struct DicEntry {
    string key;
    long posicao;
    long comprimento;
};

// trie node
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];

    // Adicionadas as informações que serão necessárias para a identificação
    // de cada entrada do dicionário e o comprimento da linha
    unsigned long posicao;
    unsigned long comprimento;
};

// Returns new trie node (initialized to NULLs)
// Posição e comprimento inicializados com 0
struct TrieNode *getNode(void) {
    struct TrieNode *pNode =  new TrieNode;

    pNode->posicao = 0;
    pNode->comprimento = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

/* Se a key não estiver presente na trie, insere na árvore;
 * Se for um prefixo, a posição e comprimento possuirão o valor 0;
 * se for palavra o valor será a posição no dicionário e o
 * comprimento da linha;
 */
void insert(struct TrieNode *root, DicEntry dicEntry) {
    struct TrieNode *pCrawl = root;
    int index;
    for (int i = 0; i < dicEntry.key.length(); i++) {
        index = dicEntry.key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // Marca o fim de palavra com a posição no dicionário e o comprimento da linha,
    // recebidos pelo parser pelo tipo DicEntry
    pCrawl->posicao = dicEntry.posicao;
    pCrawl->comprimento = dicEntry.comprimento;
}

// Declaração do struct de resultado da pesquisa
struct SearchResult {
    struct TrieNode *nodo;
    unsigned long resultadoStatus;
};

// Retorna o resultado da pesquisa na trie, passando as constantes
// de resposta definidas nesta classe
SearchResult *search(struct TrieNode *root, string key) {
    struct TrieNode *pCrawl = root;
    SearchResult *result = new SearchResult();

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        // Se a key não for um nodo da trie, então a palavra não existe e não é um prefixo
        if (!pCrawl->children[index]) {
            result->resultadoStatus = IS_NOT_PREFIX;
            return result;
        }
        pCrawl = pCrawl->children[index];
    }
    // Se os atributos "comprimento" e "posicao" forem igual a "0" no final do percorrimento
    // da key, significa que a palavra é prefixo
    if (pCrawl != nullptr && pCrawl->comprimento == 0 && pCrawl->posicao == 0) {
        result->resultadoStatus = IS_PREFIX;
        return result;
    }
    // Se os atributos "comprimento" e "posicao" forem diferentes de "0",
    // significa que é uma palavra completa que existe no dicionário
    else {
        result->resultadoStatus = IS_KEY;
        result->nodo = pCrawl;
        return result;
    }
}

#endif //TRABALHOTRIE_TRIE_H
