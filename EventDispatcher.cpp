#include "EventDispatcher.h"
#include <iostream>

#define CALL_MEMBER_FN(object, ptrToMember) ((object)->*(ptrToMember))

void EventDispatcher::dispatchEvent(GameEventPointer event, EventDispatcher* dispatcher) {
  ObserversMap::iterator it = m_observers.find(event->name());
  if (it != m_observers.end()) {
    Observers observers = it->second;
    Observers::iterator it2 = observers.begin();
    for (; it2 != observers.end(); ++it2) {
      CALL_MEMBER_FN(it2->first, it2->second)(event, dispatcher);
    }
  }


}

void EventDispatcher::addEventListener(const std::string& event, EventDispatcher* observer, Listener listener) {
  ObserversMap::iterator it = m_observers.find(event);
  if (it == m_observers.end()) {
    it = m_observers.insert(std::make_pair(event, Observers() )).first;
  }
  it->second.insert(std::make_pair(observer, listener));
}

void EventDispatcher::removeEventListener(const std::string& event, EventDispatcher* observer, Listener listener) {
  ObserversMap::iterator it = m_observers.find(event);
  if (it != m_observers.end()) {
    it->second.erase(std::make_pair(observer, listener));
  }
}
