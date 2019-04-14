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

#include <include/artworks/rectangle.h>

Rectangle::Rectangle(const PropertyList &props) : RenderItem () {

    m_printSolid = props.getBoolean("printSolidRectangles", false);
    m_rectWidth = props.getInteger("rectWidth", 15);
    m_rectHeight = props.getInteger("rectHeight", 15);
    m_rectMinWidth = props.getInteger("rectMinWidth", 0);
    m_rectMinHeight = props.getInteger("rectMinHeight", 0);
    m_rectStepSizeWidth = props.getInteger("rectStepSizeWidth", 1);
    m_rectStepSizeHeight = props.getInteger("rectStepSizeHeight", 1);
    m_rectOffsetX = props.getInteger("rectOffsetX", 0);
    m_rectOffsetY = props.getInteger("rectOffsetY", 0);

    if(m_rectMinWidth < m_rectOffsetX)
        m_rectOffsetX = m_rectMinWidth - 1;
    if(m_rectMinHeight < m_rectOffsetY)
        m_rectOffsetY = m_rectMinHeight - 1;

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "rectangle_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "rectangle_grey";
    }
}

Rectangle::~Rectangle() {

}

inline void Rectangle::initBBox(QRect &bbox) {
    bbox.setWidth(m_rectWidth+m_rectOffsetX);
    bbox.setHeight(m_rectHeight+m_rectOffsetY);
}

void Rectangle::paint(QPainter &resultPainter,
                      QPen &resultPen,
                      QPainter &usedPainter,
                      QColor &mean, unsigned int &x, unsigned int &y) {
    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawRect(x, y, m_rectWidth, m_rectHeight);

    if(m_printSolid)
        resultPainter.setBrush(QBrush(mean, Qt::SolidPattern));
    resultPen.setColor(mean);
    resultPainter.setPen(resultPen);
    resultPainter.drawRect(x+m_rectOffsetX, y+m_rectOffsetY, m_rectWidth-m_rectOffsetX, m_rectHeight-m_rectOffsetY);
}

void Rectangle::paint(QPainter &resultPainter,
                      QPen &resultPen,
                      QPainter &usedPainter,
                      int &mean, unsigned int &x, unsigned int &y) {

    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawRect(x, y, m_rectWidth, m_rectHeight);

    if(m_printSolid)
        resultPainter.setBrush(QBrush(QColor(mean,mean,mean), Qt::SolidPattern));
    resultPen.setColor(QColor(mean,mean,mean));
    resultPainter.setPen(resultPen);
    resultPainter.drawRect(x+m_rectOffsetX, y+m_rectOffsetY, m_rectWidth-m_rectOffsetX, m_rectHeight-m_rectOffsetY);
}

inline bool Rectangle::condition() {
    return (m_rectWidth > m_rectMinWidth) && (m_rectHeight > m_rectMinHeight);
}

inline bool Rectangle::update(QRect &bbox) {
    m_rectWidth -= m_rectStepSizeWidth;
    m_rectHeight -= m_rectStepSizeHeight;

    bbox.setWidth(m_rectWidth);
    bbox.setHeight(m_rectHeight);

    return true;
}

