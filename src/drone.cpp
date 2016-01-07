#include "drone.hpp"

Drone::Drone(int id , std::shared_ptr<Node> parentNode, ofVec3f size, ofVec3f pos, string modelName):
    _id(id),
    _size(size),
    _initialPos(pos),
    _color(ofVec3f(0,200+id,0)),
    _modelName(modelName){

    // adds the drone to the node Scene
    shareDrone(parentNode);

    // creates parameters to be published
    _collision = Parameter<bool>(_droneNode,
                                 false,
                                 string("collision"));
    _collision.setup("collision");

    _inZone = Parameter<bool>(_droneNode,
                              true,
                              string("inZone"));
    _inZone.setup("inZone");

    // Creates parameters to be published and listened
    // Speed set up
    _speed_x = Parameter<float>(_droneNode,
                                0,
                                string("speed_x"));
    _speed_x.setup("speed_x",-20,20);
    _speed_x.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        _speed_x.set(val->value);
    });
     _speed_x.addListener(&_speed_x,&Parameter<float>::listen);

    _speed_y = Parameter<float>(_droneNode,
                                0,
                                string("speed_y"));
    _speed_y.setup("speed_y",-20,20);
    _speed_y.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        _speed_y.set(val->value);
    });
    _speed_y.addListener(&_speed_y,&Parameter<float>::listen);

    _speed_z = Parameter<float>(_droneNode,
                                0,
                                string("speed_z"));
    _speed_z.setup("speed_z",-20,20);
    _speed_z.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        _speed_z.set(val->value);
    });
    _speed_z.addListener(&_speed_z,&Parameter<float>::listen);

    // position
    _position = Parameter<ofVec3f>(_droneNode,
                                pos,
                                string("position"));
    _position.setup("position",ofVec3f(0),ofVec3f(500,300,400));

    _position.getAddress()->addCallback([&](const Value *v){
        OSSIA::Tuple * val = (OSSIA::Tuple *) v;
        OSSIA::Float * valx = (OSSIA::Float *) val->value[0];
        OSSIA::Float * valy = (OSSIA::Float *) val->value[1];
        OSSIA::Float * valz = (OSSIA::Float *) val->value[2];

        if(valx->value != _position.get().x
                && valz->value != _position.get().y
                && valy->value != _position.get().z){
            _position.set(ofVec3f(valx->value,valz->value,valy->value));
        }
    });
    _position.addListener(&_position,&Parameter<ofVec3f>::listen);

    // adds parameters to the group of parameter
    _parameters.setName(this->className()+std::to_string(_id));
    _parameters.add(_speed_x);
    _parameters.add(_speed_y);
    _parameters.add(_speed_z);
    _parameters.add(_position);

    //_parameters.add(_collision);
    // _parameters.add(_inZone);

}

//--------------------------------------------------------------

void Drone::shareDrone(std::shared_ptr<Node> parentNode){
    _droneNode = *(parentNode->emplace(parentNode->children().cend(), "Drone."+ to_string(id())));
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
    if(!isInCollision()){
        _position += speed;
    }
}

void Drone::move(){
    if(!isInCollision()){
        // a simple equation is used here but
        // it can be changed to a more complex one if needed
        _position += ofVec3f(_speed_x.get(),_speed_z.get(),_speed_y.get());
        // Sends values to i-score
        /* _speed_x.update(_position.x);
        _speed_z.update(_position.y);
        _speed_y.update(_position.z);*/
    }
}
//--------------------------------------------------------------

void Drone::reset(){
    _position.set(ofVec3f(_initialPos.x,_initialPos.z,_initialPos.y));
    _inZone.update(true);
    _collision.update(false);
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

