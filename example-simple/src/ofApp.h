#pragma once

#include "ofMain.h"
#include "2geom/2geom.h"

#include "2geom/d2.h"
#include "2geom/sbasis.h"
#include "2geom/sbasis-2d.h"
#include "2geom/sbasis-geometric.h"
#include "2geom/sbasis-math.h"
#include "2geom/bezier-to-sbasis.h"
#include "2geom/sbasis-to-bezier.h"
#include "2geom/path-intersection.h"

using namespace Geom;


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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    private:
        Coord offset = -20;
};
