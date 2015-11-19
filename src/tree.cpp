#include "tree.hpp"

Tree::Tree(ofVec3f zoneDim):
    _zoneDim(zoneDim){
    _tmpPositionVec = new std::vector<ofVec3f>;

    _metabot = new Metabot(_zoneDim,ofVec3f(30,30,30));
}

void Tree::tmpAddPosition(ofVec3f pos){

     _tmpPositionVec->push_back(pos);
}

