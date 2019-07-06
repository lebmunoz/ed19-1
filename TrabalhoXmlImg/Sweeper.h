// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado

#ifndef TRABALHOXMLIMG_SWEEPER_H
#define TRABALHOXMLIMG_SWEEPER_H
struct vec2d {
   int x,y;
};

class XmlNode;
class Sweeper {
    public:
    long calculate(XmlNode* imgNode);
private:
    int** createMatrix(int width, int height);
    void deleteMatrix(int** matrix, int width);
    bool isValidCoord(int width, int height, vec2d coord);
};


#endif //TRABALHOXMLIMG_SWEEPER_H
