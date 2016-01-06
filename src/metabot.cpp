#include "metabot.hpp"

Metabot::Metabot(int id , std::shared_ptr<Node> parentNode, ofVec3f size, ofVec3f pos, string modelName, float freq):
    _id(id),
    _size(size),
    _position(pos),
    _color(ofVec3f(0,0,200+id)),
    _modelName(modelName){
    /* if(string::npos != modelName.find(".")){
        _3dmodel = PATH+modelName;
    }*/

    // adds the metabot to the node Scene
    shareMetabot(parentNode);

    // creates parameters to be published
    _collision = Parameter<Bool>(_metabotNode,
                                 Value::Type::BOOL,
                                 Bool(false),
                                 string("collision"), false);
    _inZone = Parameter<Bool>(_metabotNode,
                              Value::Type::BOOL,
                              Bool(true),
                              string("inZone"), false);

    // creates parameters to be published and listened
    _frequency =Parameter<Float>(_metabotNode,
                                Value::Type::FLOAT,
                                Float(freq),
                                string("frequency"), true);
}

//--------------------------------------------------------------

bool Metabot::load(){
    if(_loader.loadModel(_modelName)){
        _loader.setScale(0.3,0.3,0.3);
        _size +=70;
        return true;
    }
    else{
        modelToDefault();
        return false;
    }
}
//--------------------------------------------------------------
void Metabot::move(ofVec3f speed){
    if(isInCollision()== Bool(false)){
        _position += speed;
    }
    //_frequency = speed.length();
}

//--------------------------------------------------------------

string Metabot::info() const
{
    string msg;
    msg = "Robot selected : "
            + className() + " "
            + std::to_string( id()) + "\n";
    msg += "at position ("
            + std::to_string((int)position().x)+", "
            + std::to_string((int)position().y)+", "
            + std::to_string((int)position().z)+") \n";
    msg += "Walking frequency: "
            + std::to_string((int)(frequency().value)) + " Hz";

    return msg;
}

void Metabot::shareMetabot(std::shared_ptr<Node> parentNode){
    _metabotNode = *(parentNode->emplace(parentNode->children().cend(), "Metabot "+ to_string(id())));
}


void Metabot::updateAttributes(){

}


