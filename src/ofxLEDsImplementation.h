/*
 * Copyright Paul Reimer, 2012
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#pragma once

#include "ofColor.h"
#include "ofTypes.h"
#include "ofFbo.h"
#include <vector>

class ofxLEDsAbstraction;

class ofxLEDsImplementation
{
  friend class ofxLEDsAbstraction;
public:
  ofxLEDsImplementation(const size_t _numLEDs);
  virtual ~ofxLEDsImplementation();

  virtual void resize(size_t _numLEDs);
  virtual void encode()=0;
  virtual void clear(const ofColor& c);

  void draw();
  void addLED(const size_t& ledIdx, const ofVec3f& ledPosition);

  size_t numLEDs;
  ofMesh mappingMesh;

  ofFbo renderBuffer;
  ofFbo encodedBuffer;

  ofRectangle stripRect;
  ofMutex txBufferMutex;
  std::vector<uint8_t> pixelDataBuffer;

protected:
  bool needsEncoding;
};
