#ifndef VIEW_H
#define VIEW_H

#include "ofMain.h"
#include "metabot.hpp"

class View
{
public:
    explicit View(ofVec3f zoneDim); // avoids implicit conversion ofVec3f->View

    void drawBot(Metabot &meta);

    bool checkPosition(ofVec3f pos, int size);

    void paintRed(ofVec3f t, ofVec3f squareSize, int size);
private:
    // choregraphy zone dimension
    ofVec3f _zoneDim;


};

#endif //VIEW_H
