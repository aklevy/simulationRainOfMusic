#ifndef VIEW_H
#define VIEW_H

#include "ofMain.h"
#include "metabot.hpp"

class BotDuPlop
{
public :
    std::string model() const
    { return {}; }
    ofVec3f position() const
    { return {}; }
    ofVec3f color() const
    { return {}; }
    ofVec3f size() const
    { return {}; }
};

class View
{
public:
    explicit View(ofVec3f zoneDim); // avoids implicit conversion ofVec3f->View

    // Draws the Robot given
    template<typename Bot_T>
    void drawBot(const Bot_T& bot){
        ofVec3f position = bot.position();
        ofVec3f color = bot.color();
        int size = bot.size().x;

        ofPushStyle();
        ofPushMatrix();
        glDepthMask(false);

        ofTranslate(ofVec3f(size/2) - _zoneDim/2);
        ofTranslate(position);
        ofSetLineWidth(1);

        ofSetColor(color.x,color.y,color.z);
        ofFill();
        if(bot.model() == "Square"){
        ofDrawBox(size);

        ofSetColor(0,0,0);
        ofNoFill();
        ofDrawBox(size);
        }
        else if(bot.model() == "Sphere"){
        ofDrawSphere(size);
        }

        glDepthMask(true);
        ofPopMatrix();
        ofPopStyle();
    }

    // Checks if the robot is out of the zone
    bool checkPosition(ofVec3f pos, int size, string model);

    // Changes the face out color to red
    void paintRed(ofVec3f trans, ofVec3f squareSize, int size);

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


};

#endif //VIEW_H
