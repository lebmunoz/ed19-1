//
// Created by luis on 01/07/19.
//

#include "Counter.h"
#include "XmlNode.h"
#include <sstream>
#include <iostream>
#include <queue>

void Counter::deleteMatrix(int **matrix, int width) {
    //deleta matriz
    for(int i = 0; i < width; ++i)
        delete [] matrix[i];
    delete [] matrix;
}

int **Counter::createMatrix(int width, int height) {
    //cria matriz dinamicamente
    int** matrix = new int*[width];
    for(int i = 0; i < width; ++i)
        matrix[i] = new int[height];

    //inicializa com zeros
    for(int i = 0; i < width; ++i)
        for(int j = 0; j < height; ++j)
            matrix[i][j] = 0;
    return matrix;

}

long Counter::calculate(XmlNode *imgNode) {
    stringstream heightStream = stringstream(imgNode->getNodeByName("dimensions")->getNodeByName("height")->getValue());
    stringstream widthStream = stringstream(imgNode->getNodeByName("dimensions")->getNodeByName("width")->getValue());
    string data = imgNode->getNodeByName("data")->getValue();
    int width, height;
    widthStream >> width;
    heightStream >> height;

    //prepara matriz de entrada
    int** matrizE = createMatrix(width, height);
    int** matrizR = createMatrix(width, height);
    std::istringstream istream(data);
    std::string line;
    char ch;
    int h = 0;

    int index = 0;
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j)
            matrizR[i][j] =  (data.at(index++) == '1') ? 1 : 0;



    queue<vec2d> fila;

    int rotulo = 1;

    for(int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (matrizE[i][j] == 1 && matrizR[i][j] == 0) {
                vec2d xy;
                xy.x = i;
                xy.y = j;
                fila.push(xy);
                matrizR[i][j] = rotulo;
            }
            while(!fila.empty()){
                vec2d removido = fila.front(); fila.pop();
                matrizR[removido.x][removido.y] = rotulo;
                //vizinhos
                vec2d vizinho1,vizinho2,vizinho3,vizinho4;
                vizinho1.x = removido.x-1; vizinho1.y = removido.y;
                vizinho2.x = removido.x+1; vizinho2.y = removido.y;
                vizinho3.x = removido.x; vizinho3.y = removido.y-1;
                vizinho4.x = removido.x; vizinho4.y = removido.y+1;

                if (isValidCoord(width,height,vizinho1) && matrizE[vizinho1.x][vizinho1.y] == 1 && matrizR[vizinho1.x][vizinho1.y] == 0){
                    fila.push(vizinho1);
                }

                if (isValidCoord(width,height,vizinho2) && matrizE[vizinho2.x][vizinho2.y] == 1 && matrizR[vizinho2.x][vizinho2.y] == 0){
                    fila.push(vizinho2);
                }
                if (isValidCoord(width,height,vizinho3) && matrizE[vizinho3.x][vizinho3.y] == 1 && matrizR[vizinho3.x][vizinho3.y] == 0){
                    fila.push(vizinho3);
                }

                if (isValidCoord(width,height,vizinho4) && matrizE[vizinho4.x][vizinho4.y] == 1 && matrizR[vizinho4.x][vizinho4.y] == 0){
                    fila.push(vizinho4);
                }

                rotulo++;

            }
        }
    }
    deleteMatrix(matrizE, width);
    deleteMatrix(matrizR, width);

    return rotulo;
}



bool Counter::isValidCoord(int width, int height, vec2d coord) {
   return !(coord.x < 0 || coord.x > width || coord.y < 0 || coord.y > height);
}
