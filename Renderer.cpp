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
}

float Renderer::getWindowWidth() const {
  return m_window_width;
}

float Renderer::getWindowHeight() const {
  return m_window_height;
}

bool Renderer::clip(float x, float y, float width, float height) {
  return (x + width < 0 || x > m_window_width || y + height < 0 || y > m_window_height);
}

GLuint Renderer::getTexture(const Texture* texture) {

  std::map<const char*, GLuint>::const_iterator it = m_textures.find(texture->name());
  if (it != m_textures.end()) {
    return it->second;
  }
  else {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
  
    int noOfColors = texture->numberOfColors();
    GLenum textureFormat;
  
    if (noOfColors == 4) {
      if (texture->redMask() == 0x000000ff) {
	textureFormat = GL_RGBA;
      }
      else {
	// TODO: define GL_BGRA on windows
	textureFormat = GL_RGBA;
      }
    }
    else {
      if (texture->redMask() == 0x0000ff) {
	textureFormat = GL_RGB;
      }
      else {
	// TODO: define GL_BGR on windows
	textureFormat = GL_RGB;
      }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, 4, texture->width(), texture->height(), 0, textureFormat, GL_UNSIGNED_BYTE, texture->pixels());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_textures.insert(std::make_pair(texture->name(), id));

    return id;
  }
}

void Renderer::renderSprite(const DisplayObject& d, const Texture* texture) {
  GLuint texture_id = getTexture(texture);

    if (!clip(d.x(), d.y(), d.width() * d.scaleX(), d.height() * d.scaleY())) {
	glLoadIdentity();
	glTranslatef( 2 * d.x()  / m_window_width - 1, -2 * d.y() / m_window_height + 1, 0.0f);
	glScalef(2 * d.width() * d.scaleX() / m_window_width, -2 * d.height() * d.scaleY() / m_window_height, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	
	glEnd();
    }
}

void Renderer::renderSpriteAnimation(const DisplayObject& d, const Texture* t, int frame, Anim::DIRECTION direction) {
  GLuint texture_id = getTexture(t);
  unsigned int row = static_cast<unsigned int>(direction);
  if (!clip(d.x(), d.y(), d.width() * d.scaleX(), d.height() * d.scaleY())) {
    glLoadIdentity();
    glTranslatef( 2 * d.x()  / m_window_width - 1, -2 *  d.y() / m_window_height + 1, 0.0f);
    glScalef(2 * d.width() * d.scaleX() / m_window_width, -2 * d.width() * d.scaleY() / m_window_height, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBegin(GL_TRIANGLES);
    float w = static_cast<float>(t->width());
    float h = static_cast<float>(t->height());
    glTexCoord2f(frame * d.width() / w , row * d.height() / h);
    glVertex3f(0.0f, 0.0f, 0.1f);

    glTexCoord2f(frame * d.width() / w, (row + 1) * d.height() / h);
    glVertex3f(0.0f, 1.0f, 0.1f);

    glTexCoord2f((frame + 1) * d.width() / w, row * d.height() / h);
    glVertex3f(1.0f, 0.0f, 0.1f);

    glTexCoord2f(frame * d.width() / w, (row + 1) * d.height() / h);
    glVertex3f(0.0f, 1.0f, 0.1f);

    glTexCoord2f((frame + 1) * d.width() / w, (row + 1) * d.height() / h);
    glVertex3f(1.0f, 1.0f, 0.1f);

    glTexCoord2f((frame + 1) * d.width() / w, row * d.height() / h);
    glVertex3f(1.0f, 0.0f, 0.1f);


    glEnd();
  }

}

void Renderer::beginFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Renderer::endFrame() {
  glfwSwapBuffers();
}
