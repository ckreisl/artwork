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

#ifndef ARTWORK_H
#define ARTWORK_H

#include <QImage>
#include <QRect>
#include <QPainter>
#include <QPen>
#include <QString>

#include <include/core/proplist.h>

using namespace std;

class ArtWork {
public:
    ArtWork(const PropertyList &props);

    bool save();
    bool isEmpty(unsigned int &x, unsigned int &y);

protected:
    virtual ~ArtWork();

    QString fileName;
    QString outputName;
    QString outputType;

    QImage *inputImg;
    QImage *usedImg;
    QImage *resultImg;

    QPainter resultPainter;
    QPainter usedPainter;

    QPen resultPen;
    QPen usedPen;

    QRect bbox;

    bool saveUsedImg;
    unsigned int printThreshold;
    unsigned int printThresholdStepSize;
    unsigned int meanThresholdMin; /* min = 0 */
    unsigned int meanThresholdMax; /* max = 255 */
    QColor resultBackground;

private:
    /* nothing here */
};

#endif // ARTWORK_H
