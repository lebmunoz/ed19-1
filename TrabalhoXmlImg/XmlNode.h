//
// Created by luis on 20/05/19.
//

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
    vector<XmlNode*> &getNodes();

    XmlNode* getNodeByName(const string &name);

    vector<XmlNode*> getNodesByName(const string &name);



    const string &getName() const;

    void setName(const string &name);

    const string &getValue() const;

    void setValue(const string &value);

    void setNodes(const vector<XmlNode*> &value);



private:
    string value;
};


#endif //UNTITLED_XMLNODE_H
