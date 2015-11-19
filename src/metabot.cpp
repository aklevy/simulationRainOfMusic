#include "metabot.hpp"

Metabot::Metabot(ofVec3f zoneDim,ofVec3f size):
    _zoneDim(zoneDim),_size(size){
}

//--------------------------------------------------------------

ofVec3f Metabot::nextPosition(ofVec3f position, ofVec3f speed){
    return position + speed;
}

//--------------------------------------------------------------

