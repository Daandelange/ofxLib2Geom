#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

#include <cmath>
//--------------------------------------------------------------
void ofApp::draw(){
    // Array of points
    Point pts[] = { // p=point, h=handle, winding=CW
        {20,20}, //   0 p
        {55,10}, //   1 h
        {105,35}, // 2 h
        {150,35}, //  3 p
        {205,80}, // 4 h
        {180,120}, // 5 h
        {150,150}, // 6 p
        {95,150}, // 7 h
        {10,60},    // 8 h
    };

    // Instructions
    ofDrawBitmapStringHighlight(ofToString("Offset = ")+ofToString(offset), {10,10}, ofColor::black, ofColor::white);
    ofDrawBitmapStringHighlight(ofToString("Use UP/DOWN arrows to increase/decrease."), {10,30}, ofColor::black, ofColor::white);

    // Offset + Axis
    ofTranslate(100,100);
    ofNoFill();
    ofSetColor(ofColor::gray);
    ofDrawLine(0,0,400,0);
    ofDrawLine(0,0,0,400);

    // Draw the initial shape
    ofSetColor(ofColor::black);
    ofDrawBezier(pts[0].x(), pts[0].y(), pts[1].x(), pts[1].y(), pts[2].x(), pts[2].y(), pts[3].x(), pts[3].y());
    ofDrawBezier(pts[3].x(), pts[3].y(), pts[4].x(), pts[4].y(), pts[5].x(), pts[5].y(), pts[6].x(), pts[6].y());
    ofDrawBezier(pts[6].x(), pts[6].y(), pts[7].x(), pts[7].y(), pts[8].x(), pts[8].y(), pts[0].x(), pts[0].y());

    // Bezier handles
    ofSetColor(ofColor::blue);
    ofDrawLine(pts[0].x(), pts[0].y(), pts[1].x(), pts[1].y());
    ofDrawLine(pts[0].x(), pts[0].y(), pts[8].x(), pts[8].y());
    ofDrawLine(pts[3].x(), pts[3].y(), pts[2].x(), pts[2].y());
    ofDrawLine(pts[3].x(), pts[3].y(), pts[4].x(), pts[4].y());
    ofDrawLine(pts[6].x(), pts[6].y(), pts[5].x(), pts[5].y());
    ofDrawLine(pts[6].x(), pts[6].y(), pts[7].x(), pts[7].y());

    // Create a shape (Path) from Points
    Path p;
    p.setStitching(true); // join segments
    p.setInitial(pts[0]); // initial point p
    p.appendNew<CubicBezier>(pts[1], pts[2], pts[3]); // h, h, p
    p.appendNew<CubicBezier>(pts[4], pts[5], pts[6]);
    p.appendNew<CubicBezier>(pts[7], pts[8], pts[0]);
    //p.setFinal(pts[0]);
    p.close(true); // Closed shape

    // Apply offset, based on lib2geom/src/toys/offset-toy.cpp
    Piecewise<D2<SBasis> > B = p.toPwSb();
    Piecewise<D2<SBasis> > n = rot90(unitVector(derivative(B)));
    Piecewise<D2<SBasis> > offset_curve = B+n*offset;

    // Note: Now the segments are offset, but there are no joints/mitters.
    // That part is still done in Inkscape, maybe even using Livarot. See Inkscape/src/helper/geom-pathstroke.cpp
    // Planned to be implemented in lib2geom in the future.

    // Convert abstract shape (D2<SBasis> to )
    PathVector offset_path = path_from_piecewise(offset_curve, 0.1, true);

    // Prepare animation data
    float f = ofGetElapsedTimef();
    float ff = std::fmod(ofGetElapsedTimef(), 1.f);

    // How to render a D2<SBasis> content (the offset one)
    ofFill();
    ofSetColor(ofColor::red);
    for(unsigned int i=0; i<offset_curve.size();i++){
        Geom::D2<Geom::SBasis>& segment= offset_curve[i];

        // Segment start
        ofDrawCircle(segment.at0().x(), segment.at0().y(), 3);
        // Segment end
        ofDrawCircle(segment.at1().x(), segment.at1().y(), 3);

        // Animate 2 points along the segment
        ofDrawCircle(segment[0](1.f-ff), segment[1](1.f-ff), 2);
        ofDrawCircle(segment[0].valueAt(ff), segment[1].valueAt(ff), 2);
    }

    ofSetColor(ofColor::yellow, 100);
    // Loop Paths of PathVector
    for(const Geom::Path& pp : offset_path) {
        // Loop Curves of Path
        for(const Geom::Curve & pi : pp) {
            // Loop Bezier segments of Curve
            if(const Geom::BezierCurve* bc = dynamic_cast<const Geom::BezierCurve*>(&pi)){
                // Grab data
                Point bezPos = bc->operator[](0);
                Point bezIn = bc->operator[](1);
                Point bezOut = bc->operator[](2);
                Point bezTo = bc->operator[](3);

                // Draw
                ofNoFill();
                ofDrawBezier(bezPos.x(), bezPos.y(), bezIn.x(), bezIn.y(), bezOut.x(), bezOut.y(), bezTo.x(), bezTo.y());
                ofDrawLine(bezPos.x(), bezPos.y(), bezIn.x(), bezIn.y());
                ofDrawLine(bezTo.x(), bezTo.y(), bezOut.x(), bezOut.y());
                ofFill();
                ofDrawCircle(bezOut.x(), bezOut.y(), 3);
                ofDrawCircle(bezIn.x(), bezIn.y(), 3);
            }
        }
    }

    // Loop a Path
    ofSetColor(ofColor::black, 200);
    for(const Geom::Curve& segment : p) {
        // Get a point along the segment
        Point pt = segment.pointAt( ff );
        ofDrawCircle(pt.x(), pt.y(), 3);
    }

    ofNoFill();
    for(const Geom::Curve & pi : p) {
        // Compute bounding box of segment
        Geom::Rect bounds = pi.boundsExact();
        ofSetColor(ofColor::cyan, 20);
        ofDrawRectangle(bounds.min().x(), bounds.min().y(), bounds.width(), bounds.height());

        // Render bezier handles in cyan
        if(const Geom::BezierCurve* bc = dynamic_cast<const Geom::BezierCurve*>(&pi)){
            ofSetColor(ofColor::cyan);
            Point bezOut = bc->operator[](1);
            ofDrawCircle(bezOut.x(), bezOut.y(), 5);

            Point bezIn = bc->operator[](2);
            ofDrawCircle(bezIn.x(), bezIn.y(), 5);
        }
    }

    // Iteration with an iterator
    Path::iterator iter = p.begin(), last=p.end_open();
    for(; iter!=last; ++iter){
        const Geom::Curve& c = *iter;
        // do nothing
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key==OF_KEY_DOWN){
        offset -=0.5;
    }
    else if(key==OF_KEY_UP){
        offset +=0.5;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
