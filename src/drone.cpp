#include "drone.hpp"
Drone::~Drone(){
    _collision.removeListener(&_collision,&Parameter<bool>::listen);
    _inZone.removeListener(&_inZone,&Parameter<bool>::listen);

    _speed_x.removeListener(&_speed_x,&Parameter<float>::listen);
    _speed_y.removeListener(&_speed_y,&Parameter<float>::listen);
    _speed_z.removeListener(&_speed_z,&Parameter<float>::listen);

}
Drone::Drone(int id , std::shared_ptr<Node> parentNode, float proba, ofVec3f pos, ofVec3f size, string modelName):
    _id(id),
    _size(size),
    _initialPos(pos),
    _color(ofVec3f(0,200+id,0)),
    _modelName(modelName){

    // adds the drone to the node Scene
    shareDrone(parentNode);

    // setup parameters
    setup(proba,parentNode);
}

//--------------------------------------------------------------

void Drone::shareDrone(std::shared_ptr<Node> parentNode){
    _droneNode = *(parentNode->emplace(parentNode->children().cend(), "Drone."+ to_string(id())));
}

//--------------------------------------------------------------
void Drone::setup(float proba,std::shared_ptr<Node> parentNode){

    // initialize the parameters group
    _parameters.setName(this->className()+std::to_string(_id));

    // creates parameters to be published
    _collision.setup(_droneNode,"collision",false);

    _inZone.setup(_droneNode,"inZone",true);

    // Creates parameters to be published and listened
    // probability
    _probability.setupNoPublish(parentNode,"PacketLoss",proba,0,100);

    if(_probability.getAddress() == NULL){
        std::cout << "adress null"<<std::endl;
    }
    else{ _probability.getAddress()->addCallback([&](const Value *v){
            OSSIA::Float * val= (OSSIA::Float *)v;
            if(val->value != _probability.get()){
                _probability.set(val->value);
            }

        });
    }

    // Speed set up
    _parameters.add(_speed_x.setup(_droneNode,"speed.x",0,-20,20));
    _speed_x.getAddress()->addCallback([&](const Value *v){
        // if there is a packet loss
        if(random()%100 <= proba){
            // do nothing
        }
        else{
            OSSIA::Float * val= (OSSIA::Float *)v;
            if(val->value !=_speed_x){
               // std::cout << "vx " << val->value << std::endl;
                _speed_x.set(val->value);
            }
        }
    });
    _speed_x.addListener(&_speed_x,&Parameter<float>::listen);

    _parameters.add(_speed_y.setup(_droneNode,"speed.y",0,-20,20));
    _speed_y.getAddress()->addCallback([&](const Value *v){
        // if there is a packet loss
        if(random()%100 <= proba){
            // do nothing
        }
        else{
            Float * val= (Float *)v;
            if(val->value !=_speed_y){
                _speed_y.set(val->value);
            }
        }
    });
    _speed_y.addListener(&_speed_y,&Parameter<float>::listen);

    _parameters.add(_speed_z.setup(_droneNode,"speed.z",0,-20,20));
    _speed_z.getAddress()->addCallback([&](const Value *v){
        // if there is a packet loss
        if(random()%100 <= proba){
            // do nothing
        }
        else{
            Float * val= (Float *)v;
            if(val->value !=_speed_z){
                _speed_z.set(val->value);
            }
        }
    });
    _speed_z.addListener(&_speed_z,&Parameter<float>::listen);

    // position
    _parameters.add(_position.setup(_droneNode,"position",_initialPos,ofVec3f(0),ofVec3f(50000)));

    _position.getAddress()->addCallback([&](const Value *v){
        // if there is a packet loss
        if(random()%100 <= proba){
            // do nothing
        }
        else{
            OSSIA::Tuple * val = (OSSIA::Tuple *) v;
            val->value.resize(3);
            OSSIA::Float * valx = (OSSIA::Float *) val->value[0];
            OSSIA::Float * valy = (OSSIA::Float *) val->value[1];
            OSSIA::Float * valz = (OSSIA::Float *) val->value[2];

            if(valx->value != _position.get().x
                    || valy->value != _position.get().y
                    || valz->value != _position.get().z){
                _position.set(ofVec3f(valx->value,valy->value,valz->value));
            }
        }
    });
    _position.addListener(&_position,&Parameter<ofVec3f>::listen);
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
        float frameRate = ofGetFrameRate();
        ofVec3f speedtmp = ofVec3f(_speed_x.get()/frameRate,
                                   _speed_y.get()/frameRate,
                                   _speed_z.get()/frameRate);
        ofVec3f newpos = _position.get() + speedtmp;
        _position.set(newpos);
    }
}
//--------------------------------------------------------------

void Drone::reset(){
    if(_initialPos != _position){
        _position.set(_initialPos);
    }
   // _position.set(_initialPos);//ofVec3f(_initialPos.x,_initialPos.y,_initialPos.z));
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

