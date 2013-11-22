/*
 * Copyright Paul Reimer, 2012
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxLEDsLPD8806.h"

ofShader ofxLEDsLPD8806::lpd8806EncodingShader;
bool ofxLEDsLPD8806::lpd8806EncodedShaderInitialized;

//--------------------------------------------------------------
ofxLEDsLPD8806::ofxLEDsLPD8806(const size_t _numLEDs)
: ofxLEDsImplementation(_numLEDs)
{
  if (!lpd8806EncodedShaderInitialized)
  {
    std::stringstream vertexShaderSource;
    vertexShaderSource
    << "varying vec2 TexCoord;"
    << "void main(void)"
    << "{"
    << "  TexCoord = gl_MultiTexCoord0.st;"
    << "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
    << "  gl_FrontColor = gl_Color;"
    << "}";
    lpd8806EncodingShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderSource.str());

    std::stringstream fragmentShaderSource;
    fragmentShaderSource
    << "#version 120\n"
    << "#extension GL_ARB_texture_rectangle: enable\n"
    << "varying vec2 TexCoord;"
    << "uniform sampler2DRect tex0;"
    << "void main(void)"
    << "{"
    << "  vec4 originalColor    = texture2DRect(tex0, TexCoord);"
    // When cast as char, this is 0x80 | (c>>1)
    << "  vec4 lpd8806Color     = originalColor*0.498 + 0.502;"
    << "  gl_FragColor          = lpd8806Color.brga;"
    << "}";
    lpd8806EncodingShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderSource.str());

    lpd8806EncodingShader.linkProgram();
    lpd8806EncodedShaderInitialized = true;
  }
  
  resize(_numLEDs);
}

//--------------------------------------------------------------
ofxLEDsLPD8806::~ofxLEDsLPD8806()
{}

//--------------------------------------------------------------
void
ofxLEDsLPD8806::encode()
{
//  ofMutex::ScopedLock lock(txBufferMutex);
  encodedBuffer.begin();
  {
    lpd8806EncodingShader.begin();
    {
      renderBuffer.getTextureReference().draw(stripRect);
    }
    lpd8806EncodingShader.end();
  }
  encodedBuffer.end();

#ifndef TARGET_OPENGLES  
  ofTexture& dataTexture(encodedBuffer.getTextureReference());
  dataTexture.bind();
  {
    // These pixels are swizzled into a 2nd array for FTDI Write
    glGetTexImage(dataTexture.getTextureData().textureTarget, 0,
                  GL_RGB, GL_UNSIGNED_BYTE,
                  &pixelDataBuffer[0]);
  }
  dataTexture.unbind();
#else
  encodedBuffer.bind();
  {
    glReadPixels(0, 0,
                 stripRect.width, stripRect.height,
                 GL_RGB, GL_UNSIGNED_BYTE,
                 &pixelDataBuffer[0]);
  }
  encodedBuffer.unbind();
#endif

  needsEncoding = false;
}
