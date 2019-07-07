// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado

#include "XmlNode.h"

const string &XmlNode::getName() const {
    return name;
}

void XmlNode::setName(const string &name) {
    XmlNode::name = name;
}

const string &XmlNode::getValue() const {
    return value;
}

void XmlNode::setValue(const string &value) {
    XmlNode::value = value;
}

vector<XmlNode*> &XmlNode::getNodes() {
    return nodes;
}

void XmlNode::setNodes(const vector<XmlNode*> &value) {
    nodes = value;
}

// Pega o filho que tem o nome  == "name"
XmlNode *XmlNode::getNodeByName(const string &name) {
    vector<XmlNode*> retNodes = getNodesByName(name);
    return retNodes.size()  == 0 ? nullptr : retNodes.at(0);
}

// Pega os filhos que têm o nome  == "name"
vector<XmlNode*> XmlNode::getNodesByName(const string &name) {
    vector<XmlNode*> retNodes;

    // Percorre todos os nodos que possuem o nome recebido e insere no vetor para retornar;
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes.at(i)->getName() == name)
            retNodes.push_back(nodes.at(i));
    }
    return retNodes;
}

void XmlNode::appendValue(const char &ch) {
    value.append(1,ch);
}
