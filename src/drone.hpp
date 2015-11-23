#ifndef DRONE_H
#define DRONE_H

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

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
    Drone(int id, ofVec3f size, ofVec3f pos = ofVec3f(0), string modelName = "Sphere");

    // Load the 3d model
    bool load();

    // Update 3D model
    void updateBot(){_loader.update();}

    // Moves to the next position
    void move(ofVec3f speed);

    // Modifies the model to the default one (=Sphere)
    void modelToDefault(){_modelName = defaultModel();}

    // Set inZone to false : bot out of zone
    void outOfZone(){_inZone = false;}

    // Returns classname (=Drone)
    string className() const {return "Drone";}

    // Returns the default model (=sphere)
    string defaultModel(){return "Sphere";}

    // Returns id
    int id() const {return _id;}

    // Returns size
    ofVec3f size() const {return _size;}

    // Returns current position
    ofVec3f position() const {return _position;}

    // Returns color
    ofVec3f color() const {return _color;}

    // Returns if the bot is in zone or not
    bool isInZone() const {return _inZone;}

    // Returns 3D model object name
    string modelName() const {return _modelName;}

    // Returns 3D model object loader
    ofxAssimpModelLoader loader() const {return _loader;}

private:
    // Drone individual id
    int _id;

    // Drone size
    ofVec3f _size;

    // Drone current position
    ofVec3f _position;

    // Drone color (temporary used in selecting in ofApp)
    ofVec3f _color;

    // boolean to check if the position is inbound or not
    bool _inZone = true;

    // 3D model name
    string _modelName;

    // 3D object model loader
    ofxAssimpModelLoader _loader;
};

#endif // DRONE_H
