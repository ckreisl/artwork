#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <include/renderer/artworkgrey.h>
#include <include/renderer/artworkcolor.h>

class Triangles : public ArtWorkGrey, public ArtWorkColor {
public:
    Triangles(const PropertyList &props);

    void paint(int mean, unsigned int &x, unsigned int &y);
    void paint(QColor mean, unsigned int &x, unsigned int &y);

    bool inline condition();
    bool inline update();

protected:
    ~Triangles() { }

private:
    void getSamples(double &r1, double &r2);
    void generateTriangle(QPointF &x1, QPointF &x2, QPointF &x3, unsigned int &x, unsigned int &y);

    bool isSolid;
    unsigned int bboxWidth;
    unsigned int bboxHeight;
    unsigned int stepSizeWidth;
    unsigned int stepSizeHeight;
    unsigned int minSizeWidth;
    unsigned int minSizeHeight;
    unsigned int triangleOffsetX;
    unsigned int triangleOffsetY;
};

#endif // TRIANGLES_H
