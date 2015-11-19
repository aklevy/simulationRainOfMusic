#include "zonegrid.h"

zoneGrid::zoneGrid(int width, int height, int depth)
{
    _widthZone = width;
    _heightZone = height;
    _depthZone = depth;

    x_axis = false;
    y_axis = false;
    z_axis = false;

}

//--------------------------------------------------------------

void zoneGrid::drawZone(){

    ofPushStyle();
    ofPushMatrix();
    ofSetLineWidth(1);
    ofSetColor(255, 255, 0);
    ofNoFill();
    glDepthMask(false);
    ofDrawBox(_widthZone,_heightZone,_depthZone);
    glDepthMask(true);
    ofPopMatrix();

    ofPopStyle();

}
//--------------------------------------------------------------
void zoneGrid::drawGrid(){
    float stepSizeX = _widthZone/6;
    float stepSizeZ = _depthZone/5;

    ofPushStyle();
    ofPushMatrix();

    ofSetLineWidth(1);
    ofSetColor(0, 55, 0);
    ofNoFill();
    glDepthMask(false);

    ofTranslate(0,-_heightZone/2,0);

    for(int i = 0;i<_widthZone/stepSizeX+1;i++){

        glBegin(GL_LINES);
        glVertex3f(-300, 0,-200);
        glVertex3f(-300,0,200);
        glEnd();
        ofTranslate(stepSizeX,0,0);
    }

    ofTranslate(-stepSizeX-_widthZone,0,0);

    for(int i = 0;i<_depthZone/stepSizeZ+1;i++){

        glBegin(GL_LINES);
        glVertex3f(-300, 0,-200);
        glVertex3f(300, 0,-200);
        glEnd();
        ofTranslate(0,0,stepSizeZ);
    }
    glDepthMask(true);

    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------
void zoneGrid::drawAxes(){
    float stepSizeX = _widthZone/3;
    float stepSizeY = _heightZone/5;
    float stepSizeZ = _depthZone/5;

    ofPushStyle();


    ofSetLineWidth(1);
    ofSetColor(0, 55, 0);
    ofNoFill();
    glDepthMask(false);
    if(x_axis){
        ofPushMatrix();
        ofTranslate(0,-_heightZone/2,_depthZone/2);

        for(int i = 0;i<_heightZone/stepSizeY+1;i++){
            for(int j = 0;j<_depthZone/stepSizeZ+1;j++){

                glBegin(GL_LINES);
                glVertex3f(-_widthZone/2, 0,0);
                glVertex3f(_widthZone/2, 0,0);
                glEnd();
                ofTranslate(0,0,-stepSizeZ);
            }
            ofTranslate(0,0,_depthZone + stepSizeZ);
            ofTranslate(0,stepSizeY,0);

        }
        ofPopMatrix();
    }
    if(y_axis){
        ofPushMatrix();
        ofTranslate(-_widthZone/2,0,_depthZone/2);

        for(int i = 0;i<_widthZone/stepSizeX+1;i++){
            for(int j = 0;j<_depthZone/stepSizeZ+1;j++){

                glBegin(GL_LINES);
                glVertex3f(0, -_heightZone/2,0);
                glVertex3f(0,_heightZone/2,0);
                glEnd();
                ofTranslate(0,0,-stepSizeZ);
            }
            ofTranslate(0,0,_depthZone + stepSizeZ);
            ofTranslate(stepSizeX,0,0);

        }
        ofPopMatrix();
    }
    if(z_axis){
        ofPushMatrix();
        ofTranslate(-_widthZone/2,-_heightZone/2,0);

        for(int i = 0;i<_widthZone/stepSizeX+1;i++){
            for(int j = 0;j<_heightZone/stepSizeY+1;j++){

                glBegin(GL_LINES);
                glVertex3f(0, 0,-_depthZone/2);
                glVertex3f(0, 0,_depthZone/2);
                glEnd();
                ofTranslate(0,stepSizeY,0);
            }
            ofTranslate(0,-_heightZone - stepSizeY,0);
            ofTranslate(stepSizeX,0,0);

        }
        ofPopMatrix();
    }

    glDepthMask(true);
    ofPopStyle();


}
//--------------------------------------------------------------
void zoneGrid::modifyAxis(int axis){

    if (axis == 'x')
        x_axis = !x_axis;
    else if (axis == 'y')
        y_axis = !y_axis;
    else if (axis == 'z')
       z_axis = !z_axis;

}
//--------------------------------------------------------------
ofVec3f zoneGrid::dimension(){

    return ofVec3f(_widthZone,_heightZone,_depthZone);
}
