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
    Metabot(ofVec3f zoneDim, ofVec3f size, int id, ofVec3f pos = ofVec3f(0), string model = "Square");

    // Moves to the next position
    void move(ofVec3f speed);

    // Modifies the model to the default one (=Square)
    void defaultModel(){_3dmodel = "Square";}

    // Set inZone to false : bot out of zone
    void outOfZone(){_inZone = false;}

    // Returns classname (=Metabot)
    string className() const {return "Metabot";}

    // Returns if the bot is in zone or not
    bool isInZone() const {return _inZone;}

    // Returns size
    ofVec3f size() const {return _size;}

    // Returns size
    int id() const {return _id;}

    // Returns current position
    ofVec3f position() const {return _position;}

    // Returns color
    ofVec3f color() const {return _color;}

    // Returns 3D model object
    string model() const {return _3dmodel;}

private:
    ofVec3f _zoneDim;

    ofVec3f _size;
    int _id;

    ofVec3f _position;
    ofVec3f _color;



    bool _inZone = true;

    // 3D model corresponding
    string _3dmodel;

};

#endif // METABOT_H
