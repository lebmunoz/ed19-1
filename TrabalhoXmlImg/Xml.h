// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado
// Revision by Álvaro Certo

#ifndef UNTITLED_XML_H
#define UNTITLED_XML_H

#include "XmlNode.h"

class Xml : public XmlNode {

public:
    bool parse(const char* path);
};


#endif //UNTITLED_XML_H
