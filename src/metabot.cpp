#include "metabot.hpp"

Metabot::Metabot(ofVec3f zoneDim, ofVec3f size, int id , ofVec3f pos):
    _zoneDim(zoneDim),
    _size(size),_id(id),
    _position(pos),
    _color(ofVec3f(0,0,200+id)){
    // Temporary
    _3dmodel = "Square";
}
//--------------------------------------------------------------

void Metabot::initialPosition(ofVec3f initPos){
    _position = initPos;
}
//--------------------------------------------------------------

void Metabot::move(ofVec3f speed){
    _position += speed;
}

//--------------------------------------------------------------

