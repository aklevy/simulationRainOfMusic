#include "metabot.hpp"

Metabot::~Metabot(){
    _collision.removeListener(&_collision,&Parameter<bool>::listen);
    _inZone.removeListener(&_inZone,&Parameter<bool>::listen);

    _frequency.removeListener(&_frequency,&Parameter<float>::listen);

    _speed_x.removeListener(&_speed_x,&Parameter<float>::listen);
    _speed_y.removeListener(&_speed_y,&Parameter<float>::listen);

}

Metabot::Metabot(int id , std::shared_ptr<Node> parentNode, ofVec3f size, ofVec3f pos, string modelName, float freq):
    _id(id),
    _size(size),
    _initialPos(pos),
    _color(ofVec3f(0,0,200+id)),
    _initialFreq(freq),
    _modelName(modelName){
    /* if(string::npos != modelName.find(".")){
        _3dmodel = PATH+modelName;
    }*/
    // adds the metabot to the node Scene
    shareMetabot(parentNode);

    setup();
}


//--------------------------------------------------------------

void Metabot::shareMetabot(std::shared_ptr<Node> parentNode){
    _metabotNode = *(parentNode->emplace(parentNode->children().cend(), "Metabot."+ to_string(id())));
}

//--------------------------------------------------------------
void Metabot::setup(){
    // initialize the parameters group
    _parameters.setName(this->className()+std::to_string(_id));

    // creates parameters to be published
    _collision.setup(_metabotNode,"collision",false);

    _inZone.setup(_metabotNode,"inZone",true);

    // creates parameters to be published and listened
    // Frequency set up
    _parameters.add(_frequency.setup(_metabotNode,"frequency",_initialFreq,0,100));
    _frequency.getAddress()->addCallback([&](const Value *v){
        OSSIA::Float * val= (OSSIA::Float *)v;
        if(val->value !=_frequency.get()){
            _frequency.set(val->value);
        }
    });
    _frequency.addListener(&_frequency,&Parameter<float>::listen);

    // Speed set up
    _parameters.add(_speed_x.setup(_metabotNode,"speed_x",1,-20,20));
    _speed_x.getAddress()->addCallback([&](const Value *v){
        OSSIA::Float * val= (OSSIA::Float *)v;
        if(val->value !=_speed_x){
            _speed_x.set(val->value);
        }
    });
    _speed_x.addListener(&_speed_x,&Parameter<float>::listen);


    _parameters.add(_speed_y.setup(_metabotNode,"speed_y",1,-20,20));
    _speed_y.getAddress()->addCallback([&](const Value *v){
        OSSIA::Float * val= (OSSIA::Float *)v;
        if(val->value !=_speed_y){

            std::cout << "vy " << _speed_y.get() << std::endl;
            _speed_y.set(val->value);
        }
    });
    _speed_y.addListener(&_speed_y,&Parameter<float>::listen);

    _parameters.add( _position.setup(_metabotNode,"position",_initialPos,ofVec2f(0),ofVec2f(500,300)));

    _position.getAddress()->addCallback([&](const Value *v){
        OSSIA::Tuple * val = (OSSIA::Tuple *) v;
        OSSIA::Float * valx = (OSSIA::Float *) val->value[0];
        OSSIA::Float * valy = (OSSIA::Float *) val->value[1];

        if(valx->value != _position.get().x
                || valy->value != _position.get().y){
            _position.set(ofVec2f(valx->value,valy->value));
        }
    });
    _position.addListener(&_position,&Parameter<ofVec2f>::listen);
}

//--------------------------------------------------------------

bool Metabot::load(){
    if(_loader.loadModel(_modelName)){
        _loader.setScale(_size.x/100,_size.y/100,_size.z/100);
       // _size = _loader.getScale() * _loader.getBoundingBoxForNode();
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
        _position += ofVec2f(speed.x,speed.z);
    }
}
void Metabot::move(){
    if(!isInCollision()){
        // a simple equation is used here but
        // it can be changed to a more complex one if needed
        _position += ofVec2f(_speed_x.get(),_speed_y.get());
    }
}

//--------------------------------------------------------------

void Metabot::reset(){
    _position.set(_initialPos);
    _frequency.set(_initialFreq);
    _inZone.update(true);
    _collision.update(false);
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
            + std::to_string((int)position().y)+") \n";
    msg += "Walking frequency: "
            + std::to_string(frequency()) + " Hz";

    return msg;
}




