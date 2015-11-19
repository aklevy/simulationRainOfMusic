#include "drone.hpp"

Drone::Drone(int id , ofVec3f size, ofVec3f pos, string model):
   _id(id),
   _size(size),
    _position(pos),
    _color(ofVec3f(0,200+id,0)),
    _3dmodel(model){
}

//--------------------------------------------------------------

void Drone::move(ofVec3f speed){
    _position += speed;
}

//--------------------------------------------------------------

