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

#include "ofxLEDsAbstraction.h"

class ofxLEDs2dAbstraction
: public ofxLEDsAbstraction
{
public:
  ofxLEDs2dAbstraction();
  virtual ~ofxLEDs2dAbstraction();
  
  void addLED(ofVec2f fromCoord, ofVec2f toCoord);
  void addLEDRange(std::pair<ofVec2f, ofVec2f> fromSpaceCorners,
                   std::pair<ofVec2f, ofVec2f> toSpaceCorners);
};
