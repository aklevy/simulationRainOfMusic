#ifndef VIEW_H
#define VIEW_H

#include "ofMain.h"
//#include "of3dGraphics.h"
#include "ofxAssimpModelLoader.h"
#include "metabot.hpp"

class View
{
public:
    explicit View(ofVec3f zoneDim); // avoids implicit conversion ofVec3f->View

     // Draws the Robot with the given parameters
    void drawBot(const ofVec3f position, const ofVec3f color, const ofVec3f size, const string& modelName, ofxAssimpModelLoader& model, float angle);

   // Draws the 3d object with the given parameters
    void draw3dObject(const ofVec3f position, const ofVec3f size, const string& modelName, ofxAssimpModelLoader& model, float angle);

    // Checks if the robot is out of the zone
    bool checkPosition(ofVec3f pos, ofVec3f size, string model);

    // Paints the face out of the zone in red
    void paintRed(ofVec3f pos, ofVec3f size, string model);

    // Detects if there is a collision between two robots
    bool detectCollision(ofVec3f pos, ofVec3f size, ofVec3f otherPos, ofVec3f otherSize);

    // Draw the bounding sphere of radius sqrt(2)*size/2 (sphere surrounding a box)
    void drawCollisionCircle(const ofVec3f &position, const ofVec3f size);

    // Returns the information message contaning the given Robot's data
  /*  template<typename Bot_T>
    string information(const Bot_T& bot){
        string msg;
        msg = "Robot selected : "
                + bot.className() + " "
                + std::to_string( bot.id()) + "\n";
        msg += "at position ("
                + std::to_string((int)bot.position().x)+", "
                + std::to_string((int)bot.position().y)+", "
                + std::to_string((int)bot.position().z)+") ";

        return msg;
    }
*/

private:
    // choregraphy zone dimension
    ofVec3f _zoneDim;

};

#endif //VIEW_H
