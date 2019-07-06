// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado

#include <fstream>
#include <iostream>
#include <stack>
#include "Xml.h"

using namespace std;

// Este método faz a varredura da estrutura xml do arquivo, identifica e armazena as tags e verifica se está sendo
// obedecida a ordem de abertura e fechamento de todas as tags;
bool Xml::parse(const char* path){
    ifstream file (path);
    string line;
    string tag;
    char ch;
    // Instanciação da pilha que irá fazer a verificação dos pares de abertura e fechamento das tags;
    stack<XmlNode*> pilha;
    // Enquanto o arquivo estiver aberto;
    if (file.is_open())
    {
        // Pega linha por linha do arquivo;
        while ( getline (file,line) )
        {
            // Laço para percorrer a linha obtida, caractere por caractere;
            for (int i = 0; i < line.size(); ++i) {
                ch = line[i];
                // Identifica a abertura da tag;
                if (ch == '<') {
                    tag = "";
                    // Enquanto o caractere estiver dentro do limite da linha, e seu próximo não é um fechamento de tag;
                    while(i < line.length() && (ch = line[++i])!='>') {
                        // Incrementa a tag com o caractere atual;
                        tag +=ch;
                    }

                    //
                    if (tag.find("/") == 0){
                        if (pilha.top()->getName() == tag.substr(1, tag.length())) {
                            XmlNode *child =  pilha.top();
                            pilha.pop();
                            if (pilha.empty()){ // entao é o root
                                this->setName(child->getName());
                                this->setNodes(child->getNodes());
                                this->setValue(child->getValue());
                            }else{
                                XmlNode * parent = pilha.top();
                                parent->getNodes().push_back(child);
                            }
                        } else {
                            return false; //metodo sai fora errao memo
                        };
                    } else {
                        XmlNode *node = new XmlNode();
                        node->setName(tag);
                        node->setValue("");
                        pilha.push(node);
                    }

                }else{
                    XmlNode *top = pilha.top();
                    top->appendValue(ch);
                }
            }
        }
        file.close();
    }
    return pilha.empty();
}
