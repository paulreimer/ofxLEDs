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
    if (ofIsGLProgrammableRenderer())
    {
      vertexShaderSource
      << "attribute vec4 position;"
      << "attribute vec2 texcoord;"
      << "uniform mat4 modelViewProjectionMatrix;"
      << "varying vec2 texCoordVarying;"
      << "void main()"
      << "{"
      << "  texCoordVarying = texcoord;"
      << "  gl_Position = modelViewProjectionMatrix * position;"
      << "}";
    }
    else {
      vertexShaderSource
      << "varying vec2 TexCoord;"
      << "void main(void)"
      << "{"
      << "  TexCoord = gl_MultiTexCoord0.st;"
      << "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
      << "}";
    }
    lpd8806EncodingShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderSource.str());

    std::stringstream fragmentShaderSource;
    if (ofIsGLProgrammableRenderer())
    {
      fragmentShaderSource
      << "precision highp float;"
      << "uniform sampler2D tex0;"
      << "varying vec2 texCoordVarying;"
      << "void main()"
      << "{"
      << "  vec4 originalColor    = texture2D(tex0, texCoordVarying);"
      // When cast as char, this is 0x80 | (c>>1)
      << "  vec4 lpd8806Color     = originalColor*0.498 + 0.502;"
      << "  gl_FragColor          = lpd8806Color.brga;"
      << "}";
    }
    else {
      fragmentShaderSource
      << "#version 120\n"
      << "varying vec2 TexCoord;"
      << "uniform sampler2D tex0;"
      << "void main(void)"
      << "{"
      << "  vec4 originalColor    = texture2D(tex0, TexCoord);"
      // When cast as char, this is 0x80 | (c>>1)
      << "  vec4 lpd8806Color     = originalColor*0.498 + 0.502;"
      << "  gl_FragColor          = lpd8806Color.brga;"
      << "}";
    }

    lpd8806EncodingShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderSource.str());

    if(ofIsGLProgrammableRenderer())
      lpd8806EncodingShader.bindDefaults();

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
ofxLEDsLPD8806::resize(size_t _numLEDs)
{
  ofxLEDsImplementation::resize(_numLEDs);
  pixelDataBufferRGBA.resize(numLEDs*4);
}

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
                 GL_RGBA, GL_UNSIGNED_BYTE,
                 &pixelDataBufferRGBA[0]);
  }
  encodedBuffer.unbind();

  size_t w=stripRect.width;
  size_t h=stripRect.height;
  for (size_t y=0; y<h; ++y)
  {
    for (size_t x=0; x<w; ++x)
    {
      pixelDataBuffer[3*((y*w)+(x))+0] = pixelDataBufferRGBA[4*((y*w)+(x))+0];
      pixelDataBuffer[3*((y*w)+(x))+1] = pixelDataBufferRGBA[4*((y*w)+(x))+1];
      pixelDataBuffer[3*((y*w)+(x))+2] = pixelDataBufferRGBA[4*((y*w)+(x))+2];
    }
  }
#endif

  needsEncoding = false;
}
