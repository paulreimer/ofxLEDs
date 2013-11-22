/*
 * Copyright Paul Reimer, 2012
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxLEDs1dAbstraction.h"

//--------------------------------------------------------------
ofxLEDs1dAbstraction::ofxLEDs1dAbstraction()
{
//  mappingMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

//--------------------------------------------------------------
ofxLEDs1dAbstraction::ofxLEDs1dAbstraction(size_t startIdx, size_t endIdx)
{
  size_t n = endIdx-startIdx;
  resize(n);
  for (size_t i=0; i<n; ++i)
    addLED(i, startIdx+i);
}

//--------------------------------------------------------------
ofxLEDs1dAbstraction::~ofxLEDs1dAbstraction()
{}

//--------------------------------------------------------------
void
ofxLEDs1dAbstraction::resize(size_t n)
{
  ofxLEDsAbstraction::resize(ofRectangle(0, 0, n, 1));
}

//--------------------------------------------------------------
void
ofxLEDs1dAbstraction::addLED(size_t fromIdx, size_t toIdx)
{
  // Triangle 1
  mappingMesh.addTexCoord(ofVec2f(fromIdx / rect.width, 0));
  mappingMesh.addVertex(ofVec3f(toIdx, 0, 0));

  mappingMesh.addTexCoord(ofVec2f((fromIdx+1) / rect.width, 0));
  mappingMesh.addVertex(ofVec3f(toIdx+1, 0, 0));

  mappingMesh.addTexCoord(ofVec2f(fromIdx / rect.width, 1));
  mappingMesh.addVertex(ofVec3f(toIdx, 1, 0));

  // Triangle 2
  mappingMesh.addTexCoord(ofVec2f((fromIdx+1) / rect.width, 0));
  mappingMesh.addVertex(ofVec3f(toIdx+1, 0, 0));

  mappingMesh.addTexCoord(ofVec2f((fromIdx+1) / rect.width, 1));
  mappingMesh.addVertex(ofVec3f(toIdx+1, 1, 0));

  mappingMesh.addTexCoord(ofVec2f(fromIdx / rect.width, 1));
  mappingMesh.addVertex(ofVec3f(toIdx, 1, 0));
}

//--------------------------------------------------------------
void
ofxLEDs1dAbstraction::addLEDRange(std::pair<size_t, size_t> fromIdxRange,
                                  std::pair<size_t, size_t> toIdxRange)
{
  // Triangle 1
  mappingMesh.addTexCoord(ofVec2f(fromIdxRange.first / rect.width, 0));
  mappingMesh.addVertex(ofVec3f(toIdxRange.first, 0, 0));
  
  mappingMesh.addTexCoord(ofVec2f(fromIdxRange.second / rect.width, 0));
  mappingMesh.addVertex(ofVec3f(toIdxRange.second, 0, 0));
  
  mappingMesh.addTexCoord(ofVec2f(fromIdxRange.first / rect.width, 1));
  mappingMesh.addVertex(ofVec3f(toIdxRange.first, 1, 0));
  
  // Triangle 2
  mappingMesh.addTexCoord(ofVec2f(fromIdxRange.second / rect.width, 0));
  mappingMesh.addVertex(ofVec3f(toIdxRange.second, 0, 0));
  
  mappingMesh.addTexCoord(ofVec2f(fromIdxRange.second / rect.width, 1));
  mappingMesh.addVertex(ofVec3f(toIdxRange.second, 1, 0));
  
  mappingMesh.addTexCoord(ofVec2f(fromIdxRange.first / rect.width, 1));
  mappingMesh.addVertex(ofVec3f(toIdxRange.first, 1, 0));
}
