#include "drone.hpp"

Drone::Drone(int id , std::shared_ptr<Node> parentNode, ofVec3f size, ofVec3f pos, string modelName):
    _id(id),
    _size(size),
    _position(pos),
    _color(ofVec3f(0,200+id,0)),
    _modelName(modelName){
    shareDrone(parentNode);
}

//--------------------------------------------------------------

bool Drone::load(){
    if(_loader.loadModel(_modelName)){
        return true;
    }
    else{
        modelToDefault();
        return false;
    }
}

//--------------------------------------------------------------

void Drone::move(ofVec3f speed){
     if(isInCollision()==Bool(false)){
        _position += speed;
     }
}
//--------------------------------------------------------------

string Drone::info() const
{
    string msg;
    msg = "Robot selected : "
            + className() + " "
            + std::to_string( id()) + "\n";
    msg += "at position ("
            + std::to_string((int)position().x)+", "
            + std::to_string((int)position().y)+", "
            + std::to_string((int)position().z)+") \n";

    return msg;
}
//--------------------------------------------------------------

void Drone::shareDrone(std::shared_ptr<Node> parentNode){
    auto droneNode = *(parentNode->emplace(parentNode->children().cend(), "Drone "+ to_string(id())));
    auto idAddress = droneNode->createAddress(Value::Type::INT);
    Int i(_id);
    idAddress->pushValue(&i);
}
