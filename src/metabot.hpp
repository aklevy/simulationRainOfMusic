#ifndef METABOT_H
#define METABOT_H

#include "ofMain.h"

class Metabot
{
public:
    Metabot(ofVec3f zoneDim,ofVec3f size);

    // Set the initial position of the robot
  //  void initialPosition(ofVec3f initPos);

    // Returns the next position
    ofVec3f nextPosition(ofVec3f position,ofVec3f speed);


private:
    ofVec3f _size;
    ofVec3f _zoneDim;
};

#endif // METABOT_H
