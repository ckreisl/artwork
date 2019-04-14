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

#ifndef CIRCLES_H
#define CIRCLES_H

#include <include/renderer/renderitem.h>
#include <include/core/proplist.h>

class Circles : public RenderItem {
public:
    Circles(const PropertyList &props);
    ~Circles();

    inline void initBBox(QRect &bbox);

    void paint(QPainter &resultPainter,
               QPen &resultPen,
               QPainter &usedPainter,
               QColor &mean,
               unsigned int &x,
               unsigned int &y);

    void paint(QPainter &resultPainter,
               QPen &resultPen,
               QPainter &usedPainter,
               int &mean,
               unsigned int &x,
               unsigned int &y);

    inline bool condition();
    inline bool update(QRect &bbox);
    inline const QString& getOutputName() const { return m_outputName; }

private:
    QString m_outputName;
    bool m_printSolid;
    unsigned int m_radiusX;
    unsigned int m_radiusY;
    unsigned int m_radiusXStepSize;
    unsigned int m_radiusYStepSize;
    unsigned int m_minRadiusX;
    unsigned int m_minRadiusY;
    unsigned int m_radiusOffsetX;
    unsigned int m_radiusOffsetY;
};

#endif // CIRCLES_H
