#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0x00000);
    ofSetLogLevel(OF_LOG_VERBOSE);
    glDisable(GL_DEPTH_TEST);
    
     kParticles = 20000;
    
    box2d.init();
    box2d.setGravity(0, 0);
    box2d.setFPS(30.0);
    box2d.createBounds();
    
    ofColor color;
    color.set(255);
    particles.setParticleFlag(b2_tensileParticle);
    particles.setup(box2d.getWorld(), kParticles, 60.0, 6.0, 42.0, color);
    
    //billboard
    ofDisableArbTex();
    texture.loadImage("particleGrid.png");
    
    texW = texture.getWidth();
    texH = texture.getHeight();
    
    cellRows  = 2;
    cellColls = 2;

   
    
    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    
    
    billboardShader.setGeometryInputType(GL_POINT);
    billboardShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    billboardShader.setGeometryOutputCount(4);
    
    if(ofGetGLProgrammableRenderer()){
        ofLogVerbose()<< "load shadersGL3";
        billboardShader.load("shadersGL3/Billboard");
    }else{
        ofLogVerbose()<< "load shadersGL2";
        billboardShader.load("shadersGL2/Billboard");
    }
    
    divAtt.resize(kParticles,0);
    moffsetXAtt.resize(kParticles,0);
    moffsetYAtt.resize(kParticles,0);
    angle.resize(kParticles,0);
    for(int i = 0 ; i < kParticles ; i ++)
    {
        divAtt[i] = 1.0f/cellColls;
    }

    billboards.getVertices().resize(kParticles,ofVec3f::zero());
    billboards.getColors().resize(kParticles,ofColor::white);
    billboards.getNormals().resize(kParticles,ofVec3f(0));
    billboards.getTexCoords().resize(kParticles,ofVec2f(0));
    int n = kParticles;
    
    billboardShader.begin();
    int moffsetXAttLoc = billboardShader.getAttributeLocation("moffsetXAtt");
    billboards.getVbo().setAttributeData(moffsetXAttLoc, &moffsetXAtt[0], 1, n, GL_DYNAMIC_DRAW);
    int moffsetYAttLoc = billboardShader.getAttributeLocation("moffsetYAtt");
    billboards.getVbo().setAttributeData(moffsetYAttLoc, &moffsetYAtt[0], 1, n, GL_DYNAMIC_DRAW);
    
    int divAttLoc = billboardShader.getAttributeLocation("divAtt");
    billboards.getVbo().setAttributeData(divAttLoc,  &divAtt[0], 1, n,  GL_DYNAMIC_DRAW);
    int angleAttLoc = billboardShader.getAttributeLocation("angleAtt");
    billboards.getVbo().setAttributeData(angleAttLoc, &angle[0], 1, n, GL_DYNAMIC_DRAW);
    
    billboardShader.end();
    
    updateAttribtuteData();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    box2d.update();
    
    
    int32 particleCount = particles.particleSystem->GetParticleCount();
    b2Vec2 *positnon = particles.particleSystem->GetPositionBuffer();
    b2ParticleColor *particleColor = particles.particleSystem->GetColorBuffer();

    for(int i = 0 ; i < particleCount ; i  ++)
    {


        setParticleVertex(i, ofVec3f(positnon[i].x, positnon[i].y));

    }
    updateAttribtuteData();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(0), ofColor(63), OF_GRADIENT_LINEAR);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);;
    ofSetColor(255);
    
    ofEnablePointSprites();
    ofPushMatrix();
    ofScale(OFX_BOX2D_SCALE, OFX_BOX2D_SCALE);
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    texture.getTextureReference().bind();
    billboards.draw();
    texture.getTextureReference().unbind();
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
    ofPopMatrix();
    ofDisablePointSprites();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for (int i = 0; i < 20; i++) {
        float radius = ofRandom(60, 80);
        float x = cos(ofRandom(PI * 2.0)) * radius + mouseX;
        float y = sin(ofRandom(PI * 2.0)) * radius + mouseY;
        ofVec2f position = ofVec2f(x, y);
        ofVec2f velocity = ofVec2f(0, 0);
        ofColor color;
        int hue = int(ofGetFrameNum() / 4.0) % 255;
        color.setHsb(hue, 180, 200);
        particles.setColor(color);
        particles.createParticle(position, velocity);
        setParticleColor(particles.getParticleCount()-1, color);
        setParticleNormal(particles.getParticleCount()-1, ofVec3f(4,0,0));
        setParticleTexCoords(particles.getParticleCount()-1, (int)ofRandom(cellColls),(int)ofRandom(cellRows));
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::updateAttribtuteData()
{
    int n = kParticles;
    billboardShader.begin();
    int moffsetXAttLoc = billboardShader.getAttributeLocation("moffsetXAtt");
    billboards.getVbo().updateAttributeData(moffsetXAttLoc, &moffsetXAtt[0], n);
    int moffsetYAttLoc = billboardShader.getAttributeLocation("moffsetYAtt");
    billboards.getVbo().updateAttributeData(moffsetYAttLoc, &moffsetYAtt[0], n);
    
    int divAttLoc = billboardShader.getAttributeLocation("divAtt");
    billboards.getVbo().updateAttributeData(divAttLoc,  &divAtt[0], n);
    int angleAttLoc = billboardShader.getAttributeLocation("angleAtt");
    billboards.getVbo().updateAttributeData(angleAttLoc, &angle[0], n);
    billboardShader.end();
}


void ofApp::setParticleColor(int i, ofColor c)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    billboards.setColor(i, c);
}
void ofApp::setParticleVertex(int i, ofVec3f v)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    billboards.getVertices()[i] = v;
}

void ofApp::setParticleNormal(int i, ofVec3f v)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    
    billboards.setNormal(i,v*4);
}

void ofApp::setParticleTexCoords(int i, float columnID, float rowID)
{
    
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    
    if(columnID > cellColls) columnID = cellColls;
    if(rowID    > cellRows)  rowID    = cellRows;
    
    if(columnID < 0) columnID = 0;
    if(rowID < 0)    rowID    = 0;
    
    
    
    // get the cell image width
    float cellWidth  = texW / cellRows;
    float cellHeight = texH / cellColls;
    
    float row = rowID;
    float col = columnID;
    moffsetXAtt[i] = (cellWidth * row) / texW;
    moffsetYAtt[i] = (cellHeight * col) / texH;
    billboards.getTexCoords()[i].set((cellWidth * row) / texW,
                                     moffsetYAtt[i] = (cellHeight * col) / texH);
}
void ofApp::setParticleAngle(int i, float _angle)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    angle[i] = _angle;
}
