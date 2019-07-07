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
        while (getline (file, line))
        {
            // Laço para percorrer a linha obtida, caractere por caractere;
            for (int i = 0; i < line.size(); ++i) {
                ch = line[i];
                // Identifica a abertura da tag;
                if (ch == '<') {
                    tag = "";
                    // Enquanto o caractere estiver dentro do limite da linha, e seu próximo não é um fechamento de tag;
                    while (i < line.length() && (ch = line[++i]) != '>') {
                        // Incrementa a tag com o caractere atual;
                        tag += ch;
                    }

                    // Se a tag possui a barra que indica fechamento na primeira posição;
                    if (tag.find("/") == 0) {
                        // Verifica se a tag após a barra é igual à palavra no topo da pilha;
                        if (pilha.top()->getName() == tag.substr(1, tag.length())) {
                            // Instancia um objeto XmlNode passando a tag de abertura,
                            // pois foi encontrada uma de fechamento;
                            XmlNode *child =  pilha.top();
                            // Desempilha a tag.
                            pilha.pop();
                            // Se a pilha estiver vazia, quer dizer que o root node foi desempilhado, portanto salva
                            // com os setters o nome da tag root, todos os nodos filhos e os respectivos valores;
                            if (pilha.empty()) {
                                this->setName(child->getName());
                                this->setNodes(child->getNodes());
                                this->setValue(child->getValue());
                            } else {
                                // Senão, instancia um objeto XmlNode que vai ser o pai da tag que foi encontrada e
                                // joga a tag no final do vetor;
                                XmlNode *parent = pilha.top();
                                parent->getNodes().push_back(child);
                            }
                        } else {
                            // Se a tag for diferente de algo que está no topo da pilha, quer dizer que há um erro na
                            // estrutura do xml e o método "parse" retorna falso.
                            return false;
                        }
                    // Se for uma tag de fechamento, instancia um novo node, passa o nome da tag encontrada e empilha;
                    } else {
                        XmlNode *node = new XmlNode();
                        node->setName(tag);
                        node->setValue("");
                        pilha.push(node);
                    }
                // Se o caractere não for uma abertura de tag, quer dizer que ele é um valor de tag, o conteúdo em si.
                } else {
                    // Instancia um objeto para referenciar a tag no topo;
                    XmlNode *top = pilha.top();
                    // Adiciona o caractere no final do valor.
                    top->appendValue(ch);
                }
            }
        }
        // Fecha o arquivo.
        file.close();
    }
    // Retorna verdadeiro se a pilha, no final da leitura do aquivo, estiver vazia.
    return pilha.empty();
}
