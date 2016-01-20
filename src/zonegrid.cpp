#include "zonegrid.hpp"

ZoneGrid::ZoneGrid(ofVec3f dim):_dim(dim){
    x_axis = false;
    y_axis = false;
    z_axis = false;
    _grad = true;
}

//--------------------------------------------------------------

void ZoneGrid::drawZone(){
    // Draw the zone
    ofPushMatrix();
    ofPushStyle();

    ofSetLineWidth(1);
    ofSetColor(255, 255, 0);
    ofNoFill();
    glDepthMask(false);
    ofDrawBox(_dim.x,_dim.y,_dim.z);
    glDepthMask(true);

    ofPopStyle();
    ofPopMatrix();


}

//--------------------------------------------------------------

void ZoneGrid::drawGraduation(){
    if(_grad){
        // Displays the min and max point
        ofPushStyle();

        ofSetLineWidth(10);
        ofSetColor(0, 255, 0);
        ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
        ofDrawBitmapString("(0,0,0)", ofVec3f(0)-_dim/2);
        string maxPoint = string( "(" + std::to_string((int)_dim.x)
                                  + "," + std::to_string((int)_dim.y) +
                                  "," + std::to_string((int)_dim.z) + ")");
        ofDrawBitmapString(maxPoint, ofVec3f(0)+_dim/2);


        // Displays the graduation along x, y and z axis
        ofPushMatrix();

        float stepSize = 100;
        ofTranslate(-_dim.x/2,-_dim.y/2,-_dim.z/2);
        for(int i = 0;i<_dim.x/stepSize+1;i++){
            ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
            ofVec3f postmp = ofVec3f(i*stepSize,0,_dim.z);
            ofDrawBitmapString(std::to_string(i),postmp);
        }
        for(int i = 0;i<_dim.y/stepSize+1;i++){
            ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
            ofVec3f postmp = ofVec3f(0,i*stepSize,_dim.z);
            ofDrawBitmapString(std::to_string(i),postmp);
        }
        for(int i = 0;i<_dim.z/stepSize+1;i++){
            ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
            ofVec3f postmp = ofVec3f(0,0,i*stepSize);
            ofDrawBitmapString(std::to_string((int)(_dim.z/stepSize-i)),postmp);
        }
        ofPopMatrix();

        ofPopStyle();
    }

}

//--------------------------------------------------------------
void ZoneGrid::drawGrid(){

    // grid with step of 1m (=100cm)
    float stepSizeX = 100;
    float stepSizeZ = 100;

    ofPushStyle();
    ofPushMatrix();

    ofSetLineWidth(1);
    ofSetColor(0, 55, 0);
    ofNoFill();
    glDepthMask(false);

    ofTranslate(0,-_dim.y/2,0);

    for(int i = 0;i<_dim.x/stepSizeX+1;i++){

        glBegin(GL_LINES);
        glVertex3f(-_dim.x/2, 0,-_dim.z/2);
        glVertex3f(-_dim.x/2, 0,_dim.z/2);
        glEnd();
        ofTranslate(stepSizeX,0,0);
    }

    ofTranslate(-stepSizeX-_dim.x,0,0);

    for(int i = 0;i<_dim.z/stepSizeZ+1;i++){

        glBegin(GL_LINES);
        glVertex3f(-_dim.x/2, 0,-_dim.z/2);
        glVertex3f(_dim.x/2, 0,-_dim.z/2);
        glEnd();
        ofTranslate(0,0,stepSizeZ);
    }
    glDepthMask(true);

    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------
void ZoneGrid::drawAxes(){
    // grid with step of 1m (=100cm)
    float stepSizeX = 100;
    float stepSizeY = 100;
    float stepSizeZ = 100;

    ofPushStyle();


    ofSetLineWidth(1);
    ofSetColor(0, 55, 0);
    ofNoFill();
    glDepthMask(false);
    if(x_axis){
        ofPushMatrix();
        ofTranslate(0,-_dim.y/2,_dim.z/2);

        for(int i = 0;i<_dim.y/stepSizeY+1;i++){
            for(int j = 0;j<_dim.z/stepSizeZ+1;j++){

                glBegin(GL_LINES);
                glVertex3f(-_dim.x/2, 0,0);
                glVertex3f(_dim.x/2, 0,0);
                glEnd();
                ofTranslate(0,0,-stepSizeZ);
            }
            ofTranslate(0,0,_dim.z + stepSizeZ);
            ofTranslate(0,stepSizeY,0);

        }
        ofPopMatrix();
    }
    if(y_axis){
        ofPushMatrix();
        ofTranslate(-_dim.x/2,0,_dim.z/2);

        for(int i = 0;i<_dim.x/stepSizeX+1;i++){
            for(int j = 0;j<_dim.z/stepSizeZ+1;j++){

                glBegin(GL_LINES);
                glVertex3f(0, -_dim.y/2,0);
                glVertex3f(0,_dim.y/2,0);
                glEnd();
                ofTranslate(0,0,-stepSizeZ);
            }
            ofTranslate(0,0,_dim.z + stepSizeZ);
            ofTranslate(stepSizeX,0,0);

        }
        ofPopMatrix();
    }
    if(z_axis){
        ofPushMatrix();
        ofTranslate(-_dim.x/2,-_dim.y/2,0);

        for(int i = 0;i<_dim.x/stepSizeX+1;i++){
            for(int j = 0;j<_dim.y/stepSizeY+1;j++){

                glBegin(GL_LINES);
                glVertex3f(0, 0,-_dim.z/2);
                glVertex3f(0, 0,_dim.z/2);
                glEnd();
                ofTranslate(0,stepSizeY,0);
            }
            ofTranslate(0,-_dim.y - stepSizeY,0);
            ofTranslate(stepSizeX,0,0);

        }
        ofPopMatrix();
    }

    glDepthMask(true);
    ofPopStyle();


}

//--------------------------------------------------------------

void ZoneGrid::modifyAxis(int key){

    if (key == 'x')
        x_axis = !x_axis;
    else if (key == 'y')
        y_axis = !y_axis;
    else if (key == 'z')
        z_axis = !z_axis;
    else if (key == 'g')
        _grad = !_grad;
}

//--------------------------------------------------------------
ofVec3f ZoneGrid::dimension(){
    return _dim;
}
