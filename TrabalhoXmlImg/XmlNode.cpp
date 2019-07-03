// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado
// Revision by Álvaro Certo

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

void XmlNode::setNodes(const vector<XmlNode *> &value)
{
    nodes = value;
}

vector<XmlNode *> &XmlNode::getNodes()  {
    return nodes;
}
/*
 * pega o filho que tem o nome  == "name"
 */

XmlNode *XmlNode::getNodeByName(const string &name)
{
    vector<XmlNode*> retNodes = getNodesByName(name);
    return retNodes.size()  == 0 ? nullptr : retNodes.at(0);
}

/*
 * pega os filhos que tem o nome  == "name"
 */
vector<XmlNode*> XmlNode::getNodesByName(const string &name)
{
    vector<XmlNode*> retNodes;

    for (int i = 0; i<nodes.size(); ++i){
        if (nodes.at(i)->getName() == name){
            retNodes.push_back(nodes.at(i));
        }
    }

    return retNodes;
}

void XmlNode::appendValue(const char &ch) {
    value.append(1,ch);
}
