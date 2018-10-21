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
