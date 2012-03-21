#ifndef DISPLAYOBJECT_H__
#define DISPLAYOBJECT_H__

#include "Context.h"
#include "IRenderBehaviour.h"
#include "ISizeBehaviour.h"

class DisplayObject {
public:
  DisplayObject(Context const& c);
  virtual ~DisplayObject();
    virtual int x() const;
    virtual int y() const;
    virtual float scaleX() const;
    virtual float scaleY() const;
    virtual int width() const;
    virtual int height() const;
    virtual const DisplayObject* parent() const;
    virtual void render();
    virtual void setPosition(int x, int y);
    virtual void setScale(float scale_x, float scale_y);
    virtual void setParent(const DisplayObject*);
 protected:
    IRenderBehaviour* m_render_behaviour;
    ISizeBehaviour* m_size_behaviour;
    Context const& m_context;
    float m_x;
    float m_y;
    float m_scale_x;
    float m_scale_y;
    const DisplayObject* m_parent;

};

#endif
