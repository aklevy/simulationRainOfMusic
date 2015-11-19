#ifndef ROBOT_H
#define ROBOT_H

#include "ofMain.h"
/*
 * Position of robots will be given in the base
 * which center is at the back left corner of the zone
 * */

class Robot
{
public:
    Robot(int size, ofVec3f dimZone);
    virtual ~Robot();
    // Set the initial position of the robot
    void initialPosition(ofVec3f initPos);

    // Draw bot in the zone at _position
    void drawBot();

    // Update _position to the next position
    bool updatePosition(ofVec3f speed);

    // Check if the bot will not be out of the zone
    bool checkPosition(ofVec3f nextPos);

    // Paint in red the indicated face
    void paintRed(int face);

    // Check if the robot is selected
    string isSelected(ofVec3f colorPicked);

    // Get the next move which depends on the robot type
    virtual ofVec3f nextPosition(ofVec3f speed)=0;

    // Robot ID
    virtual string botID()=0;

    // Choose individual color for robot
    virtual ofVec3f color()=0;

protected:
    int _size;
    ofVec3f _position;
    ofVec3f _dimZone;
};

#endif // ROBOT_H
