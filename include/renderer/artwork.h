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
#include <include/renderer/renderitem.h>

using namespace std;

class ArtWork {
public:
    ArtWork(const PropertyList &props, RenderItem *renderItem);
    virtual ~ArtWork();

    bool save();
    bool isEmpty(unsigned int &x, unsigned int &y);

    RenderItem *m_renderItem;

    QString m_fileName;
    QString m_outputName;
    QString m_outputType;

    QImage *m_inputImg;
    QImage *m_usedImg;
    QImage *m_resultImg;

    QPainter m_resultPainter;
    QPainter m_usedPainter;

    QPen m_resultPen;
    QPen m_usedPen;

    QRect m_bbox;

    bool m_saveUsedImg;
    unsigned int m_printThreshold;
    unsigned int m_printThresholdStepSize;
    unsigned int m_meanThresholdMin; /* min = 0 */
    unsigned int m_meanThresholdMax; /* max = 255 */
    QColor m_resultBackground;

private:
    /* nothing here */
};

#endif // ARTWORK_H
