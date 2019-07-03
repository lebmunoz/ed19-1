// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado
// Revision by Álvaro Certo

#include <fstream>
#include <iostream>
#include <stack>
#include "Xml.h"

using namespace std;
bool Xml::parse(const char* path){
    ifstream file (path);
    string line;
    string tag;
    char ch;
    stack<XmlNode*> pilha;
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            for (int i = 0; i < line.size(); ++i) {
                ch = line[i];
                if (ch == '<') {
                    tag = "";
                    while(i < line.length() && (ch = line[++i])!='>') {
                        tag +=ch;
                    }

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

// top->appendValue(ch);