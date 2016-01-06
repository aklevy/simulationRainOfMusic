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
    _collision = Parameter<bool,Bool>(_metabotNode,
                                 Bool(false),
                                 string("collision"),0,1);
    _inZone = Parameter<bool,Bool>(_metabotNode,
                              Bool(true),
                              string("inZone"),0,1);

    // creates parameters to be published and listened
    _frequency = Parameter<float,Float>(_metabotNode,
                                  Float(freq),
                                  string("frequency"),0,100);

    _frequency.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        _frequency.set(val->value);
        //std::cout << std::to_string((int)val->value)<<" "<< std::endl;
    });

    // adds parameters to the group of parameter
    _parameters.add(_collision);
    _parameters.add(_inZone);
    _parameters.add(_frequency);

}


//--------------------------------------------------------------

void Metabot::shareMetabot(std::shared_ptr<Node> parentNode){
    _metabotNode = *(parentNode->emplace(parentNode->children().cend(), "Metabot "+ to_string(id())));
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
    if(!isInCollision()){
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
            + std::to_string((int)(frequency())) + " Hz";

    return msg;
}




