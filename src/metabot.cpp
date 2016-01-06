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
    std::cout << " constructor "<< _id<<std::endl;

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
    _frequency = new Parameter<Float>(_metabotNode,
                                  Value::Type::FLOAT,
                                  Float(freq),
                                  string("frequency"+to_string(_id)), true);
    std::cout << _frequency->getAddress() <<std::endl;
    _frequency->getAddress()->addCallback([=](const Value *v){

        cout << "ici"<<endl;
        std::cout << _frequency->getName()<<std::endl;

        if(_frequency->getName() == string("frequency"+to_string(_id))){
            Float * val= (Float *)v;
            std::cout << std::to_string((int)val->value)<<" "<< _id<<std::endl;

            _frequency->set(val->value);
         std::cout << std::to_string((int)val->value)<<" "<< std::to_string(_id)<<std::endl;
      }
        });
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


