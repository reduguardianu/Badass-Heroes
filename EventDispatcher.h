#ifndef EVENTDISPATCHER_H__
#define EVENTDISPATCHER_H__

#include <string>
#include <map>
#include <set>
#include <vector>

class EventDispatcher;

typedef void (EventDispatcher::*Listener)(std::string e, EventDispatcher* dispatcher);

class ListenerComparator {
 public:
  bool operator() (const std::pair<EventDispatcher*, Listener>& lhs, const std::pair<EventDispatcher*, Listener>& rhs) {
      return (lhs.first < rhs.first);
  }
};

typedef std::set<std::pair<EventDispatcher*, Listener>, ListenerComparator > Observers;
typedef std::map<std::string, Observers > ObserversMap;

class EventDispatcher {
 public:
  virtual void dispatchEvent(const std::string& event, EventDispatcher* dispatcher);
  virtual void addEventListener(const std::string& event, EventDispatcher* observer, Listener listener);
 private:
  ObserversMap m_observers;
};

#endif