//
// Created by luis on 26/06/19.
//

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

struct DicEntry{
    string key;
    long posicao;
    long comprimento;
};

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    unsigned long posicao;
    unsigned long comprimento;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->posicao = 0;
    pNode->comprimento = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, DicEntry dicEntry)
{
    struct TrieNode *pCrawl = root;
    int index;
    for (int i = 0; i < dicEntry.key.length(); i++)
    {
        index = dicEntry.key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->posicao = dicEntry.posicao;
    pCrawl->comprimento = dicEntry.comprimento;
}


struct SearchResult
{
    struct TrieNode *nodo;
    unsigned long resultadoStatus;
};

// Returns true if key presents in trie, else
// false
SearchResult *search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    SearchResult *result = new SearchResult();

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]) {
            result->resultadoStatus = IS_NOT_PREFIX;
            return result;  // is not prefix
        }
        pCrawl = pCrawl->children[index];
    }
    if (pCrawl != NULL && pCrawl->comprimento == 0 && pCrawl->posicao == 0) {
        result->resultadoStatus = IS_PREFIX;
        return result;
    } else {
        result->resultadoStatus = IS_KEY;
        result->nodo = pCrawl;
        return result;
    }
}

#endif //TRABALHOTRIE_TRIE_H
