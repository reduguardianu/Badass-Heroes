#include "Renderer.h"
#include "DisplayObject.h"
#include "TextureFactory.h"
#include <iostream>

const float FRAME_SIZE = 32.0f;

Renderer::Renderer():m_window_width(0), 
		     m_window_height(0) {


}

void Renderer::setSize(float w, float h) {
  m_window_width = w;
  m_window_height = h;
  glViewport(0, 0, m_window_width, m_window_height);
}

float Renderer::getWindowWidth() const {
  return m_window_width;
}

float Renderer::getWindowHeight() const {
  return m_window_height;
}

bool Renderer::clip(float x, float y, float width, float height) {
  return (x + width < 0 || x > m_window_width || y + height < 0  || y > m_window_height);
}

GLuint Renderer::getTexture(const Frame* frame) {

  std::map<const char*, GLuint>::const_iterator it = m_textures.find(frame->name());
  if (it != m_textures.end()) {
    return it->second;
  }
  else {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
  
    int noOfColors = frame->numberOfColors();
    GLenum textureFormat;
  
    if (noOfColors == 4) {
      if (frame->redMask() == 0x000000ff) {
	textureFormat = GL_RGBA;
      }
      else {
	// TODO: define GL_BGRA on windows
	textureFormat = GL_RGBA;
      }
    }
    else {
      if (frame->redMask() == 0x0000ff) {
	textureFormat = GL_RGB;
      }
      else {
	// TODO: define GL_BGR on windows
	textureFormat = GL_RGB;
      }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, 4, frame->textureWidth(), frame->textureHeight(), 0, textureFormat, GL_UNSIGNED_BYTE, frame->pixels());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_textures.insert(std::make_pair(frame->name(), id));

    return id;
  }
}


void Renderer::renderSprite(const DisplayObject& d, const Frame* frame) {
  GLuint texture_id = getTexture(frame);

    if (!clip(d.x(), d.y(), d.width() * d.scaleX(), d.height() * d.scaleY())) {
	glLoadIdentity();
	glTranslatef( 2 * d.x()  / m_window_width - 1, -2 * d.y() / m_window_height + 1, -d.z());
	glMatrixMode(GL_MODELVIEW);
	
	glColor4f(1.0f,1.0f,1.0f,d.alpha());
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);



	float u1 = frame->u();
	float u2 = frame->u() + frame->width() / static_cast<float>(frame->textureWidth());
	float v1 = frame->v();
	float v2 = frame->v() + frame->height() / static_cast<float>(frame->textureHeight());

	glScalef(2 * d.width() * d.scaleX() / m_window_width, -2 * d.height() * d.scaleY() / m_window_height, 1.0f);	
	if (d.rotation() != 0) {
	  // i have completely no idea why this works
	  glTranslatef(1.f / d.scaleX(), 1.f / d.scaleY(), 0);
	  glRotatef(d.rotation(),0.0f,0.0f,1.0f);
	  glTranslatef(-1.f / d.scaleX(), -1.f / d.scaleY(), 0);
	}

	


	glBegin(GL_TRIANGLES);

	glTexCoord2f(u1, v1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	
	glTexCoord2f(u1, v2);
	glVertex3f(0.0f, 1.0f, 0.0f);
	
	glTexCoord2f(u2, v1);
	glVertex3f(1.0f, 0.0f, 0.0f);
	
	glTexCoord2f(u1, v2);
	glVertex3f(0.0f, 1.0f, 0.0f);
	
	glTexCoord2f(u2, v2);
	glVertex3f(1.0f, 1.0f, 0.0f);
	
	glTexCoord2f(u2, v1);
	glVertex3f(1.0f, 0.0f, 0.0f);
	
	glEnd();
    }
}


void Renderer::beginFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL); 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::endFrame() {
  glfwSwapBuffers();
}
