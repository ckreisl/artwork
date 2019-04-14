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

#include <include/artworks/triangles.h>
#include <QPainterPath>
#include <iostream>

Triangles::Triangles(const PropertyList &props) : RenderItem () {

    m_isSolid = props.getBoolean("printSolidTriangles", false);
    m_bboxWidth = props.getInteger("bboxWidth", 35);
    m_bboxHeight = props.getInteger("bboxHeight", 35);
    m_stepSizeWidth = props.getInteger("bboxStepSizeWidth", 1);
    m_stepSizeHeight = props.getInteger("bboxStepSizeHeight", 1);
    m_minSizeWidth = props.getInteger("bboxMinSizeWidth", 4);
    m_minSizeHeight = props.getInteger("bboxMinSizeHeight", 4);
    m_triangleOffsetX = props.getInteger("triangleOffsetX", 0);
    m_triangleOffsetY = props.getInteger("triangleOffsetY", 0);

    if(m_minSizeWidth < m_triangleOffsetX)
        m_triangleOffsetX = m_minSizeWidth - 1;
    if(m_minSizeHeight < m_triangleOffsetY)
        m_triangleOffsetY = m_minSizeHeight - 1;

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "triangles_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "triangles_grey";
    }
}

Triangles::~Triangles() {

}

inline void Triangles::initBBox(QRect &bbox) {
    bbox.setWidth(m_bboxWidth);
    bbox.setHeight(m_bboxHeight);
}

void Triangles::paint(QPainter &resultPainter,
                      QPen &resultPen,
                      QPainter &usedPainter,
                      int &mean, unsigned int &x, unsigned int &y) {
    QPointF x1,x2,x3;
    generateTriangle(x1,x2,x3,x,y);

    QPainterPath path;
    path.moveTo(x1);
    path.lineTo(x2);
    path.lineTo(x3);
    path.lineTo(x1);
    path.closeSubpath();

    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.fillPath(path, QBrush(QColor(0,0,0), Qt::SolidPattern));

    resultPen.setColor(QColor(mean,mean,mean));
    resultPainter.setPen(resultPen);
    if(m_isSolid)
        resultPainter.fillPath(path, QBrush(QColor(mean,mean,mean), Qt::SolidPattern));
    else
        resultPainter.drawPath(path);
}

void Triangles::paint(QPainter &resultPainter,
                      QPen &resultPen,
                      QPainter &usedPainter,
                      QColor &mean, unsigned int &x, unsigned int &y) {
    QPointF x1,x2,x3;
    generateTriangle(x1,x2,x3,x,y);

    QPainterPath path;
    path.moveTo(x1);
    path.lineTo(x2);
    path.lineTo(x3);
    path.lineTo(x1);
    path.closeSubpath();

    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.fillPath(path, QBrush(QColor(0,0,0), Qt::SolidPattern));

    resultPen.setColor(mean);
    resultPainter.setPen(resultPen);
    if(m_isSolid)
        resultPainter.fillPath(path, QBrush(mean, Qt::SolidPattern));
    else
        resultPainter.drawPath(path);
}

inline bool Triangles::condition() {
    return (m_bboxWidth > m_minSizeWidth) && (m_bboxHeight > m_minSizeHeight);
}

inline bool Triangles::update(QRect &bbox) {
    m_bboxWidth -= m_stepSizeWidth;
    m_bboxHeight -= m_stepSizeHeight;

    bbox.setWidth(m_bboxWidth);
    bbox.setHeight(m_bboxHeight);

    return true;
}

void Triangles::getSamples(double &r1, double &r2) {
    do {
        r1 = ((double) rand() / (RAND_MAX));
        r2 = ((double) rand() / (RAND_MAX));
    } while ((r1*m_bboxWidth < 0.5*m_bboxWidth) || (r2*m_bboxHeight < 0.5*m_bboxHeight));
}

void Triangles::generateTriangle(QPointF &x1, QPointF &x2, QPointF &x3, unsigned int &x, unsigned int &y) {
    double r1 = 0, r2 = 0;
    switch ((int)rand() % 4) {
    case 0:
        x1.setX(x+m_triangleOffsetX);
        x1.setY(y+m_triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x + (m_bboxWidth-(r1*m_bboxWidth)));
        x2.setY(y + (m_bboxHeight-1) - m_triangleOffsetY);

        x3.setX(x + (m_bboxWidth-1) - m_triangleOffsetX);
        x3.setY(y + (m_bboxHeight-(r2*m_bboxHeight)));

        break;
    case 1:
        x1.setX(x+(m_bboxWidth-1)-m_triangleOffsetX);
        x1.setY(y+m_triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x+m_triangleOffsetX);
        x2.setY(y + (m_bboxHeight-(r1*m_bboxHeight)));

        x3.setX(x + (m_bboxWidth-(r2*m_bboxWidth)));
        x3.setY(y+(m_bboxHeight-1)-m_triangleOffsetY);

        break;
    case 2:
        x1.setX(x+m_triangleOffsetX);
        x1.setY(y+(m_bboxHeight-1)-m_triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x+r1*m_bboxWidth);
        x2.setY(y+m_triangleOffsetY);

        x3.setX(x+(m_bboxWidth-1)+m_triangleOffsetX);
        x3.setY(y+r2*m_bboxHeight);

        break;
    case 3:
        x1.setX(x+(m_bboxWidth-1)-m_triangleOffsetX);
        x1.setY(y+(m_bboxHeight-1)-m_triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x+r1*m_bboxWidth);
        x2.setY(y+m_triangleOffsetY);

        x3.setX(x+m_triangleOffsetX);
        x3.setY(y+r2*m_bboxHeight);

        break;
    }
}
