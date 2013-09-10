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
  numLEDs = _numLEDs;
  DataStart   = 0;
  PixelsStart = 4;
  PixelsEnd   = PixelsStart + (3*numLEDs);
  DataEnd     = PixelsEnd + 4;
  
  size_t latchSize = 4;
  std::vector<uint8_t> latch(latchSize, 0);
  
  txBuffer.resize(DataEnd);
  
  // Write latch data before any data, and after all the pixel data
  memcpy(&txBuffer[DataStart], latch.data(), latchSize);
  memcpy(&txBuffer[PixelsEnd], latch.data(), latchSize);
  
  // Initialized black/LED-off pixel data
  memset(&txBuffer[PixelsStart], 0x80, (PixelsEnd-PixelsStart));
}

//--------------------------------------------------------------
void
ofxLEDsLPD8806Frame::clear(const ofColor& c)
{
#warning color order dependency here?
  uint8_t pixel[3] = { (c.b>>1) | 0x80, (c.r>>1) | 0x80, (c.g>>1) | 0x80 };
  std::cout << "do clear, numLEDs=" << numLEDs << ", pixel = [" << (unsigned int)pixel[0] << ", " << (unsigned int)pixel[1] << ", " << (unsigned int)pixel[2] << std::endl;
  for (size_t i=0; i<numLEDs; ++i)
    memcpy(&txBuffer[PixelsStart + (3*i)], pixel, 3);

  needsEncoding=false;
}
