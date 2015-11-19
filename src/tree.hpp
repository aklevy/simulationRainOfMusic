#ifndef TREE_H
#define TREE_H

#include "ofMain.h"
#include "view.hpp"
#include "metabot.hpp"


class Tree
{
public:
    Tree(ofVec3f zoneDim);

    // Temporary method to add robot's position
    void tmpAddPosition(ofVec3f pos);

private:
    // choregraphy zone dimension
    ofVec3f _zoneDim;

    // Temporary : vector containing robot's positions
    std::vector<ofVec3f> * _tmpPositionVec;

    // Metabot
    Metabot * _metabot;
};

#endif //TREE_H
