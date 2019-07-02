//
// Created by luis on 01/07/19.
//

#ifndef TRABALHOXMLIMG_COUNTER_H
#define TRABALHOXMLIMG_COUNTER_H
struct vec2d {
   int x,y;
};

class XmlNode;
class Counter {
    public:
    long calculate(XmlNode* imgNode);
private:
    int** createMatrix(int width, int height);
    void deleteMatrix(int** matrix, int width);
    bool isValidCoord(int width, int height, vec2d coord);
};


#endif //TRABALHOXMLIMG_COUNTER_H
