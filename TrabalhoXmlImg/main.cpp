#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "Xml.h"
#include "Counter.h"

using namespace std;

int main() {

    Xml *xml = new Xml();
    for (int j = 1; j <= 5; ++j) {
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




    /*

    char xmlfilename[100];

    cout << "Digite o nome do arquivo a ser verificado: " << endl;

    cin >> xmlfilename;  // entrada

    ifstream myFile (xmlfilename);

    stack<string> pilhaChar;

    string line;

    if (myFile.is_open()) {

    while (
        getline(myFile, line)) {
        for (int i = 0; i < line.size(); ++i) {

            if (line[i] == '<') {
                string tag;
                for (int j = i; j < line.size(); ++j) {
                    if (line[j] != '>') {
                        tag += line[j];
                    } else {
                        break;
                    }
                }
                if (line[i+1] != '/') {
                    pilhaChar.push(tag);
                    cout << pilhaChar.top() << endl;
                } else {
                    if (pilhaChar.empty() || pilhaChar.top().compare(tag) == 0) {
                        cerr << "Erro de XML: missing opening tag" << endl;
                    } else {
                        pilhaChar.pop();
                    }
                }
            }
        }
    }
    myFile.close();

    cout << "Done parsing " << xmlfilename << endl;  // esta linha deve ser removida

    return 0;
}

    */
}

