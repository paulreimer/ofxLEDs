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

#include "ofVec3f.h"
#include "ofVboMesh.h"
#include "ofFbo.h"

class ofxLEDsAbstraction
{
public:
  ofxLEDsAbstraction();
  virtual ~ofxLEDsAbstraction();
  
  virtual void resize(const ofRectangle& _rect);
  virtual void render();

  ofFbo renderBuffer;
  ofMesh mappingMesh;
  ofRectangle rect;
};
