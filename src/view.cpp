#include "view.hpp"

View::View(ofVec3f zoneDim):
    _zoneDim(zoneDim){
}

//--------------------------------------------------------------

void View::drawBot(string obj, ofVec3f position, ofVec3f color,int size = 30){
    if(obj == "Square"){
        ofPushStyle();
        ofPushMatrix();
        glDepthMask(false);

        // ofTranslate(_x-dimZone.x/2,_y+_size/2-dimZone.y/2,_z-dimZone.z/2);
        ofTranslate(size/2 - _zoneDim.x/2, size/2 - _zoneDim.y/2,size/2 - _zoneDim.z/2);
        ofTranslate(position);
        ofSetLineWidth(1);
        ofSetColor(color.x,color.y,color.z);
        // ofSetColor(0,0,255);
        ofFill();
        ofDrawBox(size);


        ofSetColor(0,0,0);
        ofNoFill();
        ofDrawBox(size);

        glDepthMask(true);
        ofPopMatrix();
        ofPopStyle();
    }
    else{
        std::cout << "There is not such 3d model, only square for the moment" <<std::endl;
    }
}
