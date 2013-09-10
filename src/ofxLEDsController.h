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

#include "ofColor.h"
#include <vector>
#include <string>

class ofxLEDsController
{
public:
  ofxLEDsController();
  virtual ~ofxLEDsController();

  virtual void connect(const std::string target="")=0;
  virtual void update(const std::vector<uint8_t>& pixelDataBuffer,
                      const size_t pixelOffset)=0;
  virtual void clear(const ofColor& c)=0;
  virtual void sync()=0;

  size_t numLEDs;
};
