// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "Xml.h"
#include "Counter.h"

using namespace std;

int main() {

    Xml *xml = new Xml();
    for (int j = 1; j <= 6; ++j) {
        string file = "/home/luis/aulas/ed19-1/TrabalhoXmlImg/dataset0" + std::to_string(j) + ".xml";
        cout << "Parsing " << file.c_str() << endl;
        Counter * counter =  new Counter();
        if (xml->parse(file.c_str())) {
            auto imgNodes = xml->getNodesByName("img");

            for (int i = 0; i < imgNodes.size(); i++) {
                auto image = imgNodes.at(i);
                cout << "Imagem: " << image->getNodeByName("name")->getValue() << " " << "Componentes:" << counter->calculate(image) << endl;
            }
        } else {
            cout << "error" << endl;
        }

    }
}

