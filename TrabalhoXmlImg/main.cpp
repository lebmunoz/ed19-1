#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "Xml.h"

using namespace std;

int main() {

    Xml *xml = new Xml();
    if (xml->parse("/home/luis/CLionProjects/untitled/cmake-build-debug/datasets/dataset01.xml")){
        auto imgNodes = xml->getNodesByName("img");
        for (int i = 0; i < imgNodes.size(); i++){
            auto image = imgNodes.at(i);
            string name = image->getNodeByName("name")->getValue();
            string height = image->getNodeByName("dimensions")->getNodeByName("height")->getValue();
            string width = image->getNodeByName("dimensions")->getNodeByName("width")->getValue();
            string data = image->getNodeByName("data")->getValue();
            cout << "name: " << name << endl;
            cout << "height: " << height << endl;
            cout << "width: " << width << endl;
            cout << "data: " << data << endl;
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

