/*
 * Copyright Paul Reimer, 2012
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxLEDs2dAbstraction.h"

//--------------------------------------------------------------
ofxLEDs2dAbstraction::ofxLEDs2dAbstraction()
{}

//--------------------------------------------------------------
ofxLEDs2dAbstraction::~ofxLEDs2dAbstraction()
{}

//--------------------------------------------------------------
void
ofxLEDs2dAbstraction::addLED(ofVec2f fromCoord, ofVec2f toCoord)
{
  ofVec3f toCoord3d(toCoord);

  // Triangle 1
  mappingMesh.addTexCoord(fromCoord);
  mappingMesh.addVertex(toCoord3d);

  mappingMesh.addTexCoord(fromCoord + ofVec2f(1, 0));
  mappingMesh.addVertex(toCoord3d + ofVec3f(1, 0, 0));

  mappingMesh.addTexCoord(fromCoord + ofVec2f(0, 1));
  mappingMesh.addVertex(toCoord3d + ofVec3f(0, 1, 0));
  
  // Triangle 2
  mappingMesh.addTexCoord(fromCoord + ofVec2f(1, 0));
  mappingMesh.addVertex(toCoord3d + ofVec3f(1, 0, 0));
  
  mappingMesh.addTexCoord(fromCoord + ofVec2f(1, 1));
  mappingMesh.addVertex(toCoord3d + ofVec3f(1, 1, 0));
  
  mappingMesh.addTexCoord(fromCoord + ofVec2f(0, 1));
  mappingMesh.addVertex(toCoord3d + ofVec3f(0, 1, 0));
}

//--------------------------------------------------------------
void
ofxLEDs2dAbstraction::addLEDRange(std::pair<ofVec2f, ofVec2f> fromSpaceCorners,
                                  std::pair<ofVec2f, ofVec2f> toSpaceCorners)
{
  // Triangle 1
  mappingMesh.addTexCoord(ofVec2f(fromSpaceCorners.first.x, fromSpaceCorners.first.y));
  mappingMesh.addVertex(ofVec3f(toSpaceCorners.first.x, toSpaceCorners.first.y, 0));

  mappingMesh.addTexCoord(ofVec2f(fromSpaceCorners.second.x, fromSpaceCorners.first.y));
  mappingMesh.addVertex(ofVec3f(toSpaceCorners.second.x, toSpaceCorners.first.y, 0));

  mappingMesh.addTexCoord(ofVec2f(fromSpaceCorners.first.x, fromSpaceCorners.second.y));
  mappingMesh.addVertex(ofVec3f(toSpaceCorners.first.x, toSpaceCorners.second.y, 0));

  // Triangle 2
  mappingMesh.addTexCoord(ofVec2f(fromSpaceCorners.second.x, fromSpaceCorners.first.y));
  mappingMesh.addVertex(ofVec3f(toSpaceCorners.second.x, toSpaceCorners.first.y, 0));

  mappingMesh.addTexCoord(ofVec2f(fromSpaceCorners.second.x, fromSpaceCorners.second.y));
  mappingMesh.addVertex(ofVec3f(toSpaceCorners.second.x, toSpaceCorners.second.y, 0));

  mappingMesh.addTexCoord(ofVec2f(fromSpaceCorners.first.x, fromSpaceCorners.second.y));
  mappingMesh.addVertex(ofVec3f(toSpaceCorners.first.x, toSpaceCorners.second.y, 0));
}
