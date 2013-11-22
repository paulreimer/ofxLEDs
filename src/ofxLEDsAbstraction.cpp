/*
 * Copyright Paul Reimer, 2012
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include "ofxLEDsAbstraction.h"

//--------------------------------------------------------------
ofxLEDsAbstraction::ofxLEDsAbstraction()
{}

//--------------------------------------------------------------
ofxLEDsAbstraction::~ofxLEDsAbstraction()
{}

//--------------------------------------------------------------
void
ofxLEDsAbstraction::resize(const ofRectangle& _rect)
{
  rect = _rect;
  ofFbo::Settings fboConfig;
  fboConfig.textureTarget = GL_TEXTURE_2D;
  fboConfig.width         = rect.width;
  fboConfig.height        = rect.height;
  fboConfig.minFilter     = GL_NEAREST;
  fboConfig.maxFilter     = GL_NEAREST;
  renderBuffer.allocate(fboConfig);
}

//--------------------------------------------------------------
void
ofxLEDsAbstraction::render()
{
  renderBuffer.getTextureReference().bind();
  {
    mappingMesh.drawFaces();
  }
  renderBuffer.getTextureReference().unbind();
}
