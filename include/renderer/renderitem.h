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

Christoph Kreisl [04/2019]
*/

#ifndef RENDERITEM_H
#define RENDERITEM_H

#include <QColor>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QString>

class RenderItem
{
public:
    RenderItem();
    virtual ~RenderItem();

    virtual inline void initBBox(QRect &bbox) = 0;
    virtual inline bool update(QRect &bbox) = 0;
    virtual inline bool condition() = 0;

    virtual void paint(QPainter &resultPainter,
                       QPen &resultPen,
                       QPainter &usedPainter,
                       QColor &mean,
                       unsigned int &x,
                       unsigned int &y) = 0;

    virtual void paint(QPainter &resultPainter,
                       QPen &resultPen,
                       QPainter &usedPainter,
                       int &mean,
                       unsigned int &x,
                       unsigned int &y) = 0;

    virtual inline const QString& getOutputName() const = 0;
};

#endif // RENDERITEM_H
