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
                                 string("collision"));
    _collision.setName("collision");

    _inZone = Parameter<bool,Bool>(_metabotNode,
                              Bool(true),
                              string("inZone"));
    _inZone.setName("inZone");

    // creates parameters to be published and listened
    // Frequency set up
    _frequency = Parameter<float,Float>(_metabotNode,
                                  Float(freq),
                                  string("frequency"));
    _frequency.setup("frequency",0,100);
    _frequency.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        _frequency.set(val->value);
    });
    _frequency.addListener(this,&Metabot::listenFreq);

    // Speed set up
    _speed_x = Parameter<float,Float>(_metabotNode,
                                  Float(0),
                                  string("speed_x"));
    _speed_x.setup("speed_x",-20,20);
    _speed_x.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        _speed_x.set(val->value);
    });
    _speed_x.addListener(this,&Metabot::listenSpeedX);


    _speed_y = Parameter<float,Float>(_metabotNode,
                                  Float(0),
                                  string("speed_y"));
    _speed_y.setup("speed_y",-20,20);
    _speed_y.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        _speed_y.set(val->value);
    });
    _speed_y.addListener(this,&Metabot::listenSpeedY);


    // adds parameters to the group of parameter
    _parameters.setName(this->className()+std::to_string(_id));
   /* _parameters.add(_collision); // these two booleans don't need to be control on the GUI
    _parameters.add(_inZone);
    */
    _parameters.add(_frequency);
    _parameters.add(_speed_x);
    _parameters.add(_speed_y);

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
}
void Metabot::move(){
    if(!isInCollision()){
        // a simple equation is used here but
        // it can be changed to a more complex one if needed
        _position += ofVec3f(_speed_x.get(),0,_speed_y.get());
    }
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
            + std::to_string(frequency()) + " Hz";

    return msg;
}




