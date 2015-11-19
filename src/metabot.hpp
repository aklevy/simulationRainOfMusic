#ifndef METABOT_H
#define METABOT_H

#include "ofMain.h"
/*
* Point(0,0,0) is at the back left corner
* */
class Metabot
{
public:
    Metabot() = default; //default constructor

    Metabot(ofVec3f zoneDim,ofVec3f size,int id);

    // Set the initial position of the robot
    void initialPosition(ofVec3f initPos);

    // Move to the next position
    void move(ofVec3f speed);

    // Set inZone to false : bot out of zone
    void outOfZone(){_inZone = false;}

    // Returns if the bot is in zone or not
    bool isInZone(){return _inZone;}

    // Returns current position
    ofVec3f position(){return _position;}

    // Returns color
    ofVec3f color(){return _color;}

    // Returns size
    ofVec3f size(){return _size;}

    // Returns 3D model object
    string model(){return _3dmodel;}

private:
    ofVec3f _zoneDim;
    ofVec3f _size;

    ofVec3f _position;
    ofVec3f _color;

    int _id;

    bool _inZone = true;

    // 3D model corresponding
    string _3dmodel;

};

#endif // METABOT_H
