/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Christoph Kreisl [2018]
*/

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
