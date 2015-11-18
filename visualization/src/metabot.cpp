#include "metabot.h"

Metabot::Metabot(int size, ofVec3f dimZone, int id):
    Robot(size,dimZone),_id(id),_color(ofVec3f(0,0,200+id)){
    //_color = ofVec3f(0,0,200+id);
}

//--------------------------------------------------------------

ofVec3f Metabot::nextPosition(ofVec3f speed){
    return _position + speed;
}

//--------------------------------------------------------------

string Metabot::botID(){
    return " Metabot " + std::to_string(_id);
}

ofVec3f Metabot::color()
{
    return _color;
}
