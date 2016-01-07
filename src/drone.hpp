#ifndef DRONE_H
#define DRONE_H

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "parameter.hpp"

#if defined(Bool)
#undef Bool
#endif
#if defined(True)
#undef True
#endif
#if defined(False)
#undef False
#endif

#include "Network/Address.h"
#include "Network/Device.h"
#include "Network/Protocol/Local.h"
#include "Network/Protocol/Minuit.h"

using namespace OSSIA;
using namespace std;

#define PATH ""

//Point(0,0,0) is at the back left corner

/*
* Drone class
* */
class Drone
{
public:
    Drone() = delete; //forbids default constructor
    Drone(const Drone&) = delete; //forbids copy constructor

    Drone(Drone&&) = default; //move constructor : ctrl-X
    Drone(int id, std::shared_ptr<Node> parentNode, ofVec3f size, ofVec3f pos = ofVec3f(0), string modelName = "Sphere");

    // Load the 3d model
    bool load();

    // Update 3D model
    void updateBot(){_loader.update();}

    // Moves to the next position
    void move(ofVec3f speed);
    void move();

    // Resets the robot
    void reset();


    /*
     * Networks methos
     */
    // Share the drone with i-score
    void shareDrone(std::shared_ptr<Node> parentNode);

    /*
     * Getter/Setter
     * */
    // Returns parameters group
    ofParameterGroup parameters(){return _parameters;}

    // Modifies the model to the default one (=Sphere)
    void modelToDefault(){_modelName = defaultModel();}

    // Set inZone to false : bot out of zone
    void outOfZone(){_inZone.update(false);}

    // Set collision to true : bot in collision with another
    void collision(){_collision.update(true);}

    // Returns information on the drone
    string info() const;

    // Returns classname (=Drone)
    string className() const {return "Drone";}

    // Returns the default model (=sphere)
    string defaultModel(){return "Sphere";}

    // Returns id
    int id() const {return _id;}

    // Returns size
    ofVec3f size() const {return _size;}

    // Returns current position
    ofVec3f position() const {return ofVec3f(_position.get().x,_position.get().z,_position.get().y);}

    // Returns color
    ofVec3f color() const {return _color;}

    // Returns if the bot is in zone or not
    bool isInZone() const {return _inZone.get();}

    // Returns if the bot is in collision or not
    bool isInCollision() const {return _collision.get();}

    // Returns 3D model object name
    string modelName() const {return _modelName;}

    // Returns 3D model object loader
    ofxAssimpModelLoader& loader() {return _loader;}



private:
    // Drone individual id
    int _id;

    // node in the network
    std::shared_ptr<Node> _droneNode;

    // Drone size
    ofVec3f _size;

    // Drone current position and initial position
    ofVec3f _initialPos;

    // Speed values updated from i-score
    Parameter<float> _speed_x,_speed_y,_speed_z;
   // z axis is the height
    Parameter<ofVec3f> _position;

    // Drone color (temporary used in selecting in ofApp)
    ofVec3f _color;

    // Parameter group
    ofParameterGroup _parameters;

    // boolean to check if the position is inbound or not
    Parameter<bool> _inZone;

    // boolean for the collision
    Parameter<bool> _collision;

    // 3D model name
    string _modelName;

    // 3D object model loader
    ofxAssimpModelLoader _loader;

    // node in the network
    //std::shared_ptr<Node> droneNode;
    //std::shared_ptr<Address> idAddress;
};

#endif // DRONE_H
