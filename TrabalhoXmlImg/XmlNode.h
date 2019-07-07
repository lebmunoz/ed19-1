// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado

#ifndef UNTITLED_XMLNODE_H
#define UNTITLED_XMLNODE_H


#include <vector>
#include <string>

using namespace std;
class XmlNode {

private:
    string name;
    vector<XmlNode*> nodes;
public:
    const string &getName() const;

    void setName(const string &name);

    const string &getValue() const;

    void setValue(const string &value);

    vector<XmlNode*> &getNodes();

    void setNodes(const vector<XmlNode*> &value);

    XmlNode* getNodeByName(const string &name);

    vector<XmlNode*> getNodesByName(const string &name);

    void appendValue(const char &ch);

private:
    string value;
};

#endif //UNTITLED_XMLNODE_H
