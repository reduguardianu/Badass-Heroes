#ifndef GAMEEVENTPOINTER_H__
#define GAMEEVENTPOINTER_H__

#include "GameEvent.h"

class GameEventPointer {
 public:
 GameEventPointer(GameEvent* ge): m_counter(new int(0)),m_data(ge) {
    *m_counter += 1;
  }
 GameEventPointer(const GameEventPointer& p): m_data(p.m_data), m_counter(p.m_counter) { 
    *m_counter += 1;
 }
  GameEvent& operator*() { 
    return *m_data;
  }
  GameEvent* operator->() {
    return m_data;
  }
  ~GameEventPointer() { 
    *m_counter -= 1; 
    if (*m_counter == 0) { 
      delete m_data; 
      delete m_counter; 
    }
  }

  GameEventPointer& operator=(const GameEventPointer& p) {
    if (this != &p) {
      *m_counter -= 1;
      if (*m_counter == 0) {
	delete m_data;
	delete m_counter;
      }

      m_data = p.m_data;
      m_counter = p.m_counter;
      *m_counter += 1;
    }

    return *this;
  }

  GameEvent* get() {
    return m_data;
  }
 private:
  int* m_counter;
  GameEvent* m_data;
};

#endif
