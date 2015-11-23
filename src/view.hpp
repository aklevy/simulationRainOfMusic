#ifndef VIEW_H
#define VIEW_H

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "metabot.hpp"

class View
{
public:
    explicit View(ofVec3f zoneDim); // avoids implicit conversion ofVec3f->View

     // Draws the Robot with the given parameters
    void drawBot(const ofVec3f position, const ofVec3f color, const int size, string modelName, ofxAssimpModelLoader model);

   // Draws the 3d object with the given parameters
    void draw3dObject(const ofVec3f position, const int size, string modelName,ofxAssimpModelLoader model);

    // Checks if the robot is out of the zone
    bool checkPosition(ofVec3f pos, int size, string model);

    // Changes the face out color to red
    void paintRed(ofVec3f trans, ofVec3f squareSize, int size, string model);



    // Returns the information message contaning the given Robot's data
    template<typename Bot_T>
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


private:
    // choregraphy zone dimension
    ofVec3f _zoneDim;

    // 3D object model loader
   // ofxAssimpModelLoader _model;



};

#endif //VIEW_H
