#ifndef METABOT_H
#define METABOT_H

#include "ofMain.h"
//Point(0,0,0) is at the back left corner

/*
* Metabot class
* */
class Metabot
{
public:
    Metabot() = delete; //forbids default constructor
    Metabot(const Metabot&) = delete; //forbids copy constructor

    Metabot(Metabot&&) = default; //move constructor : ctrl-X
    Metabot( int id, ofVec3f size, ofVec3f pos = ofVec3f(0), string model = "Square");

    // Moves to the next position
    void move(ofVec3f speed);

    // Modifies the model to the default one (=Square)
    void modelToDefault(){_3dmodel = "Square";}

    // Set inZone to false : bot out of zone
    void outOfZone(){_inZone = false;}

    // Returns classname (=Metabot)
    string className() const {return "Metabot";}

    // Returns the default model (=square)
    string defaultModel(){return "Square";}

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

    // Returns 3D model object
    string model() const {return _3dmodel;}

private:
    // Metabot individual id
    int _id;

    // Metabot size
    ofVec3f _size;

    // Metabot current position
    ofVec3f _position;

    // Metabot color (temporary used in selecting in ofApp)
    ofVec3f _color;

    // boolean to check if the position is inbound or not
    bool _inZone = true;

    // 3D model corresponding
    string _3dmodel;


};

#endif // METABOT_H
