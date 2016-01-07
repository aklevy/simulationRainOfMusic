#ifndef METABOT_H
#define METABOT_H

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "parameter.hpp"

#if defined(Bool)
#undef Bool
#endif
#if defined(True)
#undef True
#endif
#if defined(False)
#undef False
#endif

#include "Network/Address.h"
#include "Network/Device.h"
#include "Network/Protocol/Local.h"
#include "Network/Protocol/Minuit.h"

using namespace OSSIA;
using namespace std;

//Point(0,0,0) is at the back left corner

/*
* Metabot class
*
* 3d Model tends to slow down the movement
* */
class Metabot
{
public:
    Metabot() = delete; //forbids default constructor
    Metabot(const Metabot&) = delete; //forbids copy constructor

    Metabot(Metabot&&) = default; //move constructor : ctrl-X
    Metabot(int id,
            std::shared_ptr<Node> parentNode,
            ofVec3f size = ofVec3f(30),
            ofVec3f pos = ofVec3f(0),
            string modelName = "Square",
            float freq = 2);

    // Load the 3d model
    bool load();

    // Update 3D model
    void updateBot(){_loader.update();}

    // Moves to the next position
    void move(ofVec3f speed);
    void move();
    /*
     * Networks methods
     */

    // Share the metabot with i-score
    void shareMetabot(std::shared_ptr<Node> parentNode);

    // Listeners for GUI
    void listenFreq(float &data){_frequency.update(Float(data));}
    void listenSpeedX(float &data){_speed_x.update(Float(data));}
    void listenSpeedY(float &data){_speed_y.update(Float(data));}


    /*
     * Getter/Setter
     * */

    // Modifies the model to the default one (=Square)
    void modelToDefault(){_modelName = defaultModel();}

    // Set inZone to false : bot out of zone
    void outOfZone(){_inZone.update(Bool(false));}

    // Set collision to true and publishes the value: bot in collision with another
    void collision(){_collision.update(Bool(true));}

    // Returns information on the metabot
    string info() const;

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

    // Returns parameters group
    ofParameterGroup parameters(){return _parameters;}

    // Returns walking frequency
    float frequency() const {return _frequency.get();}

    // Returns if the bot is in zone or not
    bool isInZone() const {return _inZone.get();}

    // Returns if the bot is in collision or not
    bool isInCollision() const {return _collision.get();}

    // Returns 3D model object name
    string modelName() const {return _modelName;}

    // Returns 3D model object loader
    ofxAssimpModelLoader& loader() {return _loader;}



private:
    // Metabot individual id
    int _id;

    // node in the network
    std::shared_ptr<Node> _metabotNode;

    // Metabot size
    ofVec3f _size;

    // Metabot current position
    ofVec3f _position;

    // Speed values updated from i-score
    Parameter<float,Float> _speed_x;
    Parameter<float,Float> _speed_y;

    // Metabot color (temporary used in selecting in ofApp)
    ofVec3f _color;

    // Parameter group
    ofParameterGroup _parameters;

    // Frequency of the walk, in Hz (default = 2Hz)
    Parameter<float,Float> _frequency;

    // boolean to check if the position is inbound or not
    Parameter<bool,Bool> _inZone;

    // boolean for the collision
    Parameter<bool,Bool> _collision;

    // 3D model name
    string _modelName;

    // 3D object model loader
    ofxAssimpModelLoader _loader;
};

#endif // METABOT_H
