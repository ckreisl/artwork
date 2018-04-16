#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <include/renderer/artworkgrey.h>
#include <include/renderer/artworkcolor.h>

class Rectangle : public ArtWorkGrey, public ArtWorkColor {
public:
    Rectangle(const PropertyList &props);

    void paint(QColor mean, unsigned int &x, unsigned int &y);
    void paint(int mean, unsigned int &x, unsigned int &y);

    bool inline condition();
    bool inline update();

protected:
    virtual ~Rectangle() { }

private:
    bool printSolid;
    unsigned int rectWidth;
    unsigned int rectHeight;
    unsigned int rectMinWidth;
    unsigned int rectMinHeight;
    unsigned int rectStepSizeWidth;
    unsigned int rectStepSizeHeight;
    unsigned int rectOffsetX;
    unsigned int rectOffsetY;
};

#endif // RECTANGLE_H
