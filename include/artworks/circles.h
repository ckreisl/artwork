#ifndef CIRCLES_H
#define CIRCLES_H

#include <include/renderer/artworkgrey.h>
#include <include/renderer/artworkcolor.h>

class Circles : public ArtWorkGrey, public ArtWorkColor {
public:
    Circles(const PropertyList &props);

    void paint(QColor mean, unsigned int &x, unsigned int &y);
    void paint(int mean, unsigned int &x, unsigned int &y);

    bool inline condition();
    bool inline update();

protected:
    virtual ~Circles() { }

private:
    bool printSolid;
    unsigned int radiusX;
    unsigned int radiusY;
    unsigned int radiusXStepSize;
    unsigned int radiusYStepSize;
    unsigned int minRadiusX;
    unsigned int minRadiusY;
    unsigned int radiusOffsetX;
    unsigned int radiusOffsetY;
};

#endif // CIRCLES_H
