#include "metabot.hpp"

Metabot::Metabot(int id , std::shared_ptr<Node> parentNode, ofVec3f size, ofVec3f pos, string modelName, float freq):
    _id(id),
    _size(size),
    _initialPos(pos),
    _color(ofVec3f(0,0,200+id)),
    _modelName(modelName){
    /* if(string::npos != modelName.find(".")){
        _3dmodel = PATH+modelName;
    }*/
    // adds the metabot to the node Scene
    shareMetabot(parentNode);

    // creates parameters to be published
    _collision = Parameter<bool>( _metabotNode,
                                  false,
                                  string("collision"));
    _collision.setup("collision");

    _inZone = Parameter<bool>( _metabotNode,
                               true,
                               string("inZone"));
    _inZone.setup("inZone");

    // creates parameters to be published and listened
    // Frequency set up
    _frequency = Parameter<float>( _metabotNode,
                                   freq,
                                   string("frequency"));

    _frequency.setup("frequency",0,100);

    _frequency.getAddress()->addCallback([&](const Value *v){
        OSSIA::Float * val= (OSSIA::Float *)v;
        if(val->value !=_frequency){
            _frequency.set(val->value);
        }
    });
    _frequency.addListener(&_frequency,&Parameter<float>::listen);

    // Speed set up
    _speed_x = Parameter<float>(_metabotNode,
                                0,
                                string("speed_x"));
    _speed_x.setup("speed_x",-20,20);

    _speed_x.getAddress()->addCallback([&](const Value *v){
        OSSIA::Float * val= (OSSIA::Float *)v;
        if(val->value !=_speed_x){
            _speed_x.set(val->value);
        }
    });

    _speed_x.addListener(&_speed_x,&Parameter<float>::listen);


    _speed_y = Parameter<float>(_metabotNode,
                                0,
                                string("speed_y"));
    _speed_y.setup("speed_y",-20,20);
    _speed_y.getAddress()->addCallback([&](const Value *v){
        OSSIA::Float * val= (OSSIA::Float *)v;
        if(val->value !=_speed_y){
            _speed_y.set(val->value);
        }
    });
    _speed_y.addListener(&_speed_y,&Parameter<float>::listen);

    _position = Parameter<ofVec2f>(_metabotNode,
                                pos,
                                string("position"));
    _position.setup("position",ofVec2f(0),ofVec2f(500,300));

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


    // adds parameters to the group of parameter
    _parameters.setName(this->className()+std::to_string(_id));
    /*_parameters.add(_collision); // these two booleans don't need to be control on the GUI

    _parameters.add(_inZone);
*/
    _parameters.add(_frequency);
    _parameters.add(_speed_x);
    _parameters.add(_speed_y);
    _parameters.add(_position);

}


//--------------------------------------------------------------

void Metabot::shareMetabot(std::shared_ptr<Node> parentNode){
    _metabotNode = *(parentNode->emplace(parentNode->children().cend(), "Metabot."+ to_string(id())));
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
        _position += ofVec2f(speed.x,speed.z);
    }
}
void Metabot::move(){
    if(!isInCollision()){
        // a simple equation is used here but
        // it can be changed to a more complex one if needed
        _position += ofVec2f(_speed_x.get(),_speed_y.get());

        // Sends values to i-score
        /* _speed_x.update(_position.x);
        _speed_y.update(_position.y);
        */
    }
}

//--------------------------------------------------------------

void Metabot::reset(){
    _position.set(_initialPos);
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




