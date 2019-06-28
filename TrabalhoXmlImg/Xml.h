//
// Created by luis on 20/05/19.
//

#ifndef UNTITLED_XML_H
#define UNTITLED_XML_H

#include "XmlNode.h"

class Xml : public XmlNode {

public:
    bool parse(const char* path);
};


#endif //UNTITLED_XML_H
