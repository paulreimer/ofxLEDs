/*
 * Copyright Paul Reimer, 2013
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#pragma once

#include "ofxLEDsFrame.h"

class ofxLEDsLPD8806Frame
: public ofxLEDsFrame
{
public:
  ofxLEDsLPD8806Frame(const size_t _numLEDs=0);
  virtual ~ofxLEDsLPD8806Frame();
  
  void resize(const size_t _numLEDs);
  void clear(const ofColor& c);
};
