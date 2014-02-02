/*
 * Copyright Paul Reimer, 2013
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxLEDsLPD8806Frame.h"

//--------------------------------------------------------------
ofxLEDsLPD8806Frame::ofxLEDsLPD8806Frame(const size_t _numLEDs)
: ofxLEDsFrame(_numLEDs)
{}

//--------------------------------------------------------------
ofxLEDsLPD8806Frame::~ofxLEDsLPD8806Frame()
{}

//--------------------------------------------------------------
void
ofxLEDsLPD8806Frame::resize(size_t _numLEDs)
{
  size_t latchSize = 4;
  std::vector<uint8_t> latch(latchSize, 0);
  resize(_numLEDs, latch, latch);
}

//--------------------------------------------------------------
void
ofxLEDsLPD8806Frame::resize(size_t _numLEDs,
                            const std::vector<uint8_t>& latchPrefix)
{
  size_t latchSize = 4;
  std::vector<uint8_t> latch(latchSize, 0);
  resize(_numLEDs, latchPrefix, latch);
}

//--------------------------------------------------------------
void
ofxLEDsLPD8806Frame::resize(size_t _numLEDs,
                            const std::vector<uint8_t>& latchPrefix,
                            const std::vector<uint8_t>& latchSuffix)
{
  numLEDs = _numLEDs;
  DataStart   = 0;
  PixelsStart = latchPrefix.size();
  PixelsEnd   = PixelsStart + (3*numLEDs);
  DataEnd     = PixelsEnd + latchSuffix.size();
  
  txBuffer.resize(DataEnd);
  
  // Write latch data before any data, and after all the pixel data
  memcpy(&txBuffer[DataStart], latchPrefix.data(), latchPrefix.size());
  memcpy(&txBuffer[PixelsEnd], latchSuffix.data(), latchSuffix.size());

  // Initialized black/LED-off pixel data
  memset(&txBuffer[PixelsStart], 0x80, (PixelsEnd-PixelsStart));
}

//--------------------------------------------------------------
void
ofxLEDsLPD8806Frame::clear(const ofColor& c)
{
#warning color order dependency here?
  uint8_t pixel[3] = {
    (uint8_t)((c.b>>1) | 0x80),
    (uint8_t)((c.r>>1) | 0x80),
    (uint8_t)((c.g>>1) | 0x80)
  };
  for (size_t i=0; i<numLEDs; ++i)
    memcpy(&txBuffer[PixelsStart + (3*i)], pixel, 3);

  needsEncoding=false;
}
