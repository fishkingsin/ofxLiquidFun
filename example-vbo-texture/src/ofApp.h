#pragma once

#include "ofMain.h"
#include "ofxLiquidFun.h"
class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofxBox2d box2d;
    ofxBox2dParticleSystem particles;
    
    //billboard
    int kParticles;
    
    ofShader billboardShader;
    
    ofVboMesh billboards;
    
    ofImage texture;
    
    int                     cellRows;
    
    int                     cellColls;
    
    float           texW, texH;
    
    vector<float>divAtt;
    
    vector<float>moffsetXAtt;
    
    vector<float>moffsetYAtt;
    
    vector<float>angle;

    void setParticleColor(int i, ofColor c);
    
    void setParticleVertex(int i, ofVec3f v);
    
    void setParticleNormal(int i, ofVec3f v);
    
    void setParticleTexCoords(int i, float columnID, float rowID);
    
    void setParticleAngle(int i, float _angle);
    
    void updateAttribtuteData();
};
