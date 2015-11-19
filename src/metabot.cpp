#include "metabot.hpp"

Metabot::Metabot(ofVec3f zoneDim, ofVec3f size, int id , ofVec3f pos,string model):
    _zoneDim(zoneDim),
    _size(size),_id(id),
    _position(pos),
    _color(ofVec3f(0,0,200+id)),
    _3dmodel(model){

}

//--------------------------------------------------------------

void Metabot::move(ofVec3f speed){
    _position += speed;
}

//--------------------------------------------------------------

