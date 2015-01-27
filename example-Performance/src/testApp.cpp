#include "testApp.h"

static bool removeShapeOffScreen(ofPtr<ofxBox2dBaseShape> shape) {
    if (!ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape.get()->getPosition())) {
        return true;
    }
    return false;
}

//--------------------------------------------------------------
void testApp::setup() {
    
 
	ofDisableAntiAliasing();
	ofBackgroundHex(0x1F2C30);
	ofSetLogLevel(OF_LOG_NOTICE);

	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    box2d.createGround();
//    box2d.createBounds();
    
    ground.setPhysics(0, 0, 0);
    ground.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()+200, 400);
    
    groundMesh.setUsage(GL_STATIC_DRAW);
    groundMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for(int i=0; i<100; i++) {
        float t = ofMap(i, 0, 99, 0.0, TWO_PI);
        ofVec3f v(ofGetWidth()/2, ofGetHeight()+200);
        groundMesh.addVertex(v);
        v.x += cos(t)*400;
        v.y += sin(t)*400;
        groundMesh.addVertex(v);
    }
}

//--------------------------------------------------------------
void testApp::update() {
   
    ofRemove(circles, removeShapeOffScreen);
    ofRemove(boxes, removeShapeOffScreen);
    
	box2d.update();
    
 
     
    float r = ofRandom(4, 20);
    circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
    circles.back().get()->setup(box2d.getWorld(), ofGetWidth()/2+ofRandom(-100, 100), 200+ofRandom(30, 100), r);


    float w = ofRandom(4, 20);
    float h = ofRandom(4, 20);
    boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
    boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
    boxes.back().get()->setup(box2d.getWorld(), ofGetWidth()/2+ofRandom(-100, 100), 200+ofRandom(30, 100), w, h);
    
   
	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0x90d4e3);
		circles[i].get()->draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xe63b8b);
		boxes[i].get()->draw();
	}

    ofSetColor(255, 100);
    groundMesh.draw();
    
	string info = "";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate())+"\n";
	ofSetColor(255);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
    if(key == '1') {
        for(int i=0; i<10; i++) {
            float r = ofRandom(2, 5);
            circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), ofGetMouseX()+ofRandom(-10, 10), ofGetMouseY()+ofRandom(-10, 10), r);
        }
    }
	if(key == '2') {
        float w = ofRandom(2, 20);
        float h = ofRandom(2, 20);
        boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
        boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
        boxes.back().get()->setup(box2d.getWorld(), ofGetMouseX(), ofGetMouseY(), w, h);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {


}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
	
}

