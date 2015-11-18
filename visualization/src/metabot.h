#ifndef METABOT_H
#define METABOT_H

#include "ofMain.h"
#include "robot.h"

class Metabot : public Robot
{
public:
    Metabot(int size, ofVec3f dimZone,int id);

    ofVec3f nextPosition(ofVec3f speed);

    // Robot ID
    string botID();

    // Returns the individual color of the robot
    ofVec3f color();

private:
    int _id;
    ofVec3f _color;
};

#endif // METABOT_H
