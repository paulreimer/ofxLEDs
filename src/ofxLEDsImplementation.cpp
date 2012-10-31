/*
 * Copyright Paul Reimer, 2012
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxLEDsImplementation.h"
#include "ofGraphics.h"

//--------------------------------------------------------------
ofxLEDsImplementation::ofxLEDsImplementation(const size_t _numLEDs)
: numLEDs(_numLEDs)
, stripRect(0, 0, _numLEDs, 1)
{}

//--------------------------------------------------------------
ofxLEDsImplementation::~ofxLEDsImplementation()
{}

//--------------------------------------------------------------
void
ofxLEDsImplementation::clear(const ofColor& c)
{
  renderBuffer.begin();
  {
    ofClear(c);
  }
  renderBuffer.end();

  needsEncoding = true;
}

//--------------------------------------------------------------
void
ofxLEDsImplementation::draw()
{
  glPointSize(40.);
  renderBuffer.getTextureReference().bind();
  {
    mappingMesh.drawVertices();
  }
  renderBuffer.getTextureReference().unbind();
  glPointSize(1.);
}

//--------------------------------------------------------------
void
ofxLEDsImplementation::addLED(const size_t& ledIdx,
                              const ofVec3f& ledPosition)
{
  mappingMesh.addTexCoord(ofVec2f(ledIdx, 0));
  mappingMesh.addVertex(ledPosition);
}
