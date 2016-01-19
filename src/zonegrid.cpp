#include "zonegrid.hpp"

ZoneGrid::ZoneGrid(ofVec3f dim):_dim(dim){
    x_axis = false;
    y_axis = false;
    z_axis = false;
}

//--------------------------------------------------------------

void ZoneGrid::drawZone(){

    ofPushStyle();
    ofPushMatrix();
    ofSetLineWidth(1);
    ofSetColor(255, 255, 0);
    ofNoFill();
    glDepthMask(false);
    ofDrawBox(_dim.x,_dim.y,_dim.z);
    glDepthMask(true);
    ofPopMatrix();

    ofPopStyle();

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

void ZoneGrid::modifyAxis(int axis){

    if (axis == 'x')
        x_axis = !x_axis;
    else if (axis == 'y')
        y_axis = !y_axis;
    else if (axis == 'z')
        z_axis = !z_axis;

}

//--------------------------------------------------------------
ofVec3f ZoneGrid::dimension(){
    return _dim;
}
