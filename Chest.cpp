#include "Chest.h"

Chest::Chest(Context const& c): DisplayObject(c),
				m_is_opened(false),
				m_opened(NULL),
				m_closed(NULL) {
  m_opened = new Sprite(m_context, "chest.png");
  m_opened->setUV(0.5, 0.0);
  m_opened->setSize(32, 32);
  m_opened->setScale(2, 2);
  m_opened->setParent(this);

  m_closed= new Sprite(m_context, "chest.png");
  m_closed->setUV(0.0, 0.0);
  m_closed->setSize(32, 32);  
  m_closed->setScale(2, 2);
  m_closed->setParent(this);
  
}

void Chest::open() {
  m_is_opened = true;
}

void Chest::close() {
  m_is_opened = false;
}

void Chest::render() {
  if (m_is_opened) {
    m_opened->render();
  }
  else {
    m_closed->render();
  }
}

Chest::~Chest() {
  if (m_opened) {
    delete m_opened;
  }
  if (m_closed) {
    delete m_closed;
  }
}
