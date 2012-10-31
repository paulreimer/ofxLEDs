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

//#include "ofxLEDsAbstraction.h"
#include "ofxLEDs2dAbstraction.h"

class ofxLEDs1dAbstraction
: public ofxLEDsAbstraction
{
public:
  ofxLEDs1dAbstraction();
  ofxLEDs1dAbstraction(size_t startIdx, size_t endIdx);

  virtual ~ofxLEDs1dAbstraction();

  void resize(size_t n);
  void addLED(size_t fromIdx, size_t toIdx);
  void addLEDRange(std::pair<size_t, size_t> fromIdxRange,
                   std::pair<size_t, size_t> toIdxRange);
};
