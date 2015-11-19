#include "metabot.hpp"

Metabot::Metabot(int id , ofVec3f size, ofVec3f pos, string model):
    _id(id),
    _size(size),
    _position(pos),
    _color(ofVec3f(0,0,200+id)),
    _3dmodel(model){
}

//--------------------------------------------------------------

void Metabot::move(ofVec3f speed){
    _position += speed;
}

//--------------------------------------------------------------

