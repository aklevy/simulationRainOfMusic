#ifndef VIEW_H
#define VIEW_H

#include "ofMain.h"
#include "zonegrid.hpp"


class View
{
public:
    View(ofVec3f zoneDim);

    void drawBot(string obj, ofVec3f position, ofVec3f color, int size);

  //  bool checkPosition(ofVec3f nextPos);

private:
    ofVec3f _zoneDim;
};

#endif //VIEW_H
