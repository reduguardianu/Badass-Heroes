#ifndef IDRAWABLE_H__
#define IDRAWABLE_H__

class Texture;

class IDrawable {
public:
    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual float scaleX() const = 0;
    virtual float scaleY() const = 0;
    virtual const Texture* texture() const = 0;
    virtual void render() = 0;
    virtual void setParent(const IDrawable*) = 0;    
    virtual int width() const = 0;
    virtual int height() const = 0;
};

#endif
