#ifndef IDRAWABLE_H__
#define IDRAWABLE_H__

class IDrawable {
public:
    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual float scaleX() const = 0;
    virtual float scaleY() const = 0;
    virtual const char* texture() const = 0;
};

#endif
