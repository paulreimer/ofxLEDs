/*
 * Copyright Paul Reimer, 2013
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxLEDsFrame.h"

//--------------------------------------------------------------
ofxLEDsFrame::ofxLEDsFrame(const size_t _numLEDs)
: numLEDs(_numLEDs)
{}

//--------------------------------------------------------------
ofxLEDsFrame::~ofxLEDsFrame()
{}

//--------------------------------------------------------------
void
ofxLEDsFrame::update(const std::vector<uint8_t>& pixelDataBuffer,
                     const size_t pixelOffset)
{
  memcpy(&txBuffer[PixelsStart], &pixelDataBuffer[(3*pixelOffset)], (3*numLEDs));
  needsEncoding = false;
}
