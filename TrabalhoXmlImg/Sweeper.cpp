// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado

#include "Sweeper.h"
#include "XmlNode.h"
#include <sstream>
#include <iostream>
#include <queue>

void Sweeper::deleteMatrix(int **matrix, int height) {
    // Deleta a matriz;
    for(int i = 0; i < height; ++i)
        delete [] matrix[i];
    delete [] matrix;
}

int **Sweeper::createMatrix(int width, int height) {
    // Cria matriz dinamicamente;
    int** matrix = new int* [height];
    for (int i = 0; i < height; ++i)
        matrix[i] = new int [width];

    // Inicializa a matriz com zeros;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            matrix[i][j] = 0;
    return matrix;

}

// Este método vai calcular os componentes conexos na imagem binária recebida;
long Sweeper::calculate(XmlNode *imgNode) {
    // Procura o nodo de dimensões;
    XmlNode *imgNodeDimension = imgNode->getNodeByName("dimensions");
    // Pega os valores de height e width (altura e largura);
    stringstream heightStream = stringstream(imgNodeDimension->getNodeByName("height")->getValue());
    stringstream widthStream = stringstream(imgNodeDimension->getNodeByName("width")->getValue());
    // Pega o valor do nodo "data", que são os bits da imagem
    string data = imgNode->getNodeByName("data")->getValue();
    // Converte os valores de altura e largura para variáveis inteiras
    int width, height;
    widthStream >> width;
    heightStream >> height;

    // Prepara matriz de entrada e de rotulação, com os valores de dimensão recebidos;
    int** matrizE = createMatrix(width, height);
    int** matrizR = createMatrix(width, height);

    // Esta parte faz a "tradução" do valor de "data" que atualmente é uma string para montar a matriz de int;
    int index = 0;
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j)
            matrizE[i][j] = (data.at(index++) == '1') ? 1 : 0;

    // Instancia uma fila de vetor de 2 dimensões;
    queue<vec2d> fila;

    // O rótulo é iniciado com 1 para que o primeiro pixel possa ser verificado na primeira execução do algoritmo;
    int rotulo = 1;

    // Laço de varredura da matriz de entrada;
    for(int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Verifica se o pixel atual da matriz de entrada é 1 e se não foi rotulado ainda;
            if (matrizE[i][j] == 1 && matrizR[i][j] == 0) {
                // Cria uma variável de vetor de 2 dimensões e copia as posições x e y atuais;
                vec2d xy;
                xy.x = i;
                xy.y = j;
                // Coloca a variável na fila de verificação de vizinhos e já atribui a esta posição o rótulo atual;
                fila.push(xy);
                matrizR[i][j] = rotulo;
                // Enquanto a fila de verificação não estiver vazia;
                while(!fila.empty()){
                    // Guarda o primeiro da fila e remove;
                    vec2d removido = fila.front(); fila.pop();
                    // Aplica o rótulo atual na posição que está sendo verificada
                    matrizR[removido.x][removido.y] = rotulo;

                    // Instancia as coordenadas dos vizinhos dentro de um array controle para o laço de alternância;
                    vec2d vizinho[4];
                    vizinho[1].x = removido.x-1; vizinho[1].y = removido.y;
                    vizinho[2].x = removido.x+1; vizinho[2].y = removido.y;
                    vizinho[3].x = removido.x; vizinho[3].y = removido.y-1;
                    vizinho[4].x = removido.x; vizinho[4].y = removido.y+1;

                    // Este laço alterna a verificação dos vizinhos, do primeiro ao quarto;
                    for (int numero = 1; numero <= 4; ++numero) {
                        // Verifica se a coordenada atual não ultrapassa os limites da matriz,
                        // se o pixel atual na matriz de entrada é 1 e se o pixel altual na matriz de rótulo é 0;
                        if (isValidCoord(width,height,vizinho[numero]) &&
                            matrizE[vizinho[numero].x][vizinho[numero].y] == 1 &&
                            matrizR[vizinho[numero].x][vizinho[numero].y] == 0)
                        {
                            // Então coloca na fila para verificação dos vizinhos e já marca com o rótulo atual,
                            // para evitar que ele seja verificado mais de uma vez.
                            fila.push(vizinho[numero]);
                            matrizR[vizinho[numero].x][vizinho[numero].y] = rotulo;
                        }
                    }
                }
                // Quando termina de percorrer todos os pixels do componente conexo, incrementa o rótulo.
                rotulo++;
            }
        }
    }
    // Deleta as matrizes de entrada e de rótulo para liberar o espaço na memória;
    deleteMatrix(matrizE, height);
    deleteMatrix(matrizR, height);

    // Retorna o rótulo com um decremento, pois ele foi iniciado com 1 para forçar a primeira verificação.
    return rotulo - 1;
}

// Método que verifica se a coordenada está dentro dos limites da matriz;
bool Sweeper::isValidCoord(int width, int height, vec2d coord) {
    return !(coord.y < 0 || coord.y >= width || coord.x < 0 || coord.x >= height);
}
