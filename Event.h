#ifndef EVENT_H__
#define EVENT_H__

namespace EventType {
  enum TYPE {
    Unknown = 0,
    MouseDown = 1,
    MouseUp = 2,
    MouseMoved = 3,
    MouseClicked = 4,
    KeyDown = 5,
    KeyUp = 6,
    Resize = 7,
    User = 8
  };
};

namespace Keyboard {
  enum KEY {
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 3,
    S = 4
  };
};


namespace Modifier {
  enum TYPE {
    Alt = 0,
    Shift = 1,
    Control = 2
  };
};

namespace MouseButton {
  enum TYPE {
    Left = 0,
    Right = 1,
    Middle = 2
  };
};


struct Event {
  EventType::TYPE event_type;
  bool eaten;

  union {
    struct {
      int x;
      int y;
      MouseButton::TYPE button;
    } mouse_data;

    struct {
      int key;
      int modifiers;
      bool pressed_down;
    } key_data;

    struct {
      const char* action;
      const char* param1;
      const char* param2;
    } user_data;

    struct {
      unsigned int width;
      unsigned int height;
    } resize_data;
  };

Event(EventType::TYPE type = EventType::Unknown): event_type(type), eaten(false) {}
};

class IEventReceiver {
  virtual void onEvent(const Event& e) = 0;
};

#endif
