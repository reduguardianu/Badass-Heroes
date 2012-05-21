#ifndef DISPLAYOBJECT_H__
#define DISPLAYOBJECT_H__

#include "Context.h"
#include "IRenderBehaviour.h"
#include "ISizeBehaviour.h"
#include <vector>
#include "EventDispatcher.h"

class DisplayObject: public EventDispatcher {
public:
  explicit DisplayObject(Context const& c);
  virtual ~DisplayObject();
    virtual int x() const;
    virtual int y() const;
    virtual float localX() const;
    virtual float localY() const;
    virtual float z() const;
    virtual float scaleX() const;
    virtual float scaleY() const;
    virtual int width() const;
    virtual int height() const;
    virtual DisplayObject* parent() const;
    virtual float alpha() const;
    virtual float rotation() const;
    virtual int row() const;
    virtual int col() const;

    virtual void tick(float dt);
    virtual void render();
    virtual void setPosition(float x, float y);
    virtual void setScale(float scale_x, float scale_y);
    virtual void setScale(float scale);
    virtual void setParent(DisplayObject*);
    virtual void setZ(float value);
    virtual void setAlpha(float value);
    virtual void setRotation(float value);

    virtual void addChild(DisplayObject*);
    virtual void removeChild(DisplayObject*);

    virtual Rectangle* bounds() const;
    virtual void setBounds(Rectangle* value);

    bool visible() const;
 protected:
    IRenderBehaviour* m_render_behaviour;
    ISizeBehaviour* m_size_behaviour;
    Context const& m_context;
    float m_x;
    float m_y;
    float m_scale_x;
    float m_scale_y;
    float m_z;
    DisplayObject* m_parent;
    float m_alpha;
    std::vector<DisplayObject*> m_children;
    float m_rotation;
    Rectangle* m_bounds;
};

#endif
