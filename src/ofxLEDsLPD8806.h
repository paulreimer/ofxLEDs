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

#include "ofxLEDsImplementation.h"
#include "ofxLEDsLPD8806Frame.h"

#include "ofShader.h"

class ofxLEDsLPD8806
: public ofxLEDsImplementation
{
public:
  ofxLEDsLPD8806(const size_t _numLEDs);
  virtual ~ofxLEDsLPD8806();

  void encode();

private:
  static ofShader lpd8806EncodingShader;
  static bool lpd8806EncodedShaderInitialized;
};
