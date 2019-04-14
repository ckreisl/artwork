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

#include <include/artworks/circles.h>
#include <iostream>
#include <QPoint>
#include <QBrush>

using namespace std;

Circles::Circles(const PropertyList &props) {

    m_printSolid = props.getBoolean("printSolidCircles", false);
    m_radiusX = props.getInteger("radiusX", 8);
    m_radiusY = props.getInteger("radiusY", 8);
    m_radiusXStepSize = props.getInteger("radiusXStepSize", 1);
    m_radiusYStepSize = props.getInteger("radiusYStepSize", 1);
    m_minRadiusX = props.getInteger("minRadiusX", 0);
    m_minRadiusY = props.getInteger("minRadiusY", 0);
    m_radiusOffsetX = props.getInteger("radiusOffsetX", 0);
    m_radiusOffsetY = props.getInteger("radiusOffsetY", 0);

    if(m_minRadiusX < m_radiusOffsetX)
        m_radiusOffsetX = m_minRadiusX - 1;
    if(m_minRadiusY < m_radiusOffsetY)
        m_radiusOffsetY = m_minRadiusY - 1;

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "circles_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "circles_grey";
    }
}

Circles::~Circles() {

}

inline void Circles::initBBox(QRect &bbox) {
    bbox.setWidth((2*m_radiusX)+m_radiusOffsetX);
    bbox.setHeight((2*m_radiusY)+m_radiusOffsetY);
}

inline bool Circles::condition() {
    return (m_radiusX > m_minRadiusX) && (m_radiusY > m_minRadiusY);
}

inline bool Circles::update(QRect &bbox) {
    m_radiusX -= m_radiusXStepSize;
    m_radiusY -= m_radiusYStepSize;

    bbox.setWidth((2*m_radiusX)+m_radiusOffsetX);
    bbox.setHeight((2*m_radiusY)+m_radiusOffsetY);

    return true;
}

void Circles::paint(QPainter &resultPainter,
                    QPen &resultPen,
                    QPainter &usedPainter,
                    QColor &mean, unsigned int &x, unsigned int &y) {
    QPoint center(x+m_radiusX+(m_radiusOffsetX/2),y+m_radiusY+(m_radiusOffsetY/2));
    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawEllipse(center, m_radiusX, m_radiusY);

    if(m_printSolid)
        resultPainter.setBrush(QBrush(mean, Qt::SolidPattern));
    resultPen.setColor(mean);
    resultPainter.setPen(resultPen);
    resultPainter.drawEllipse(center, m_radiusX, m_radiusY);
}

void Circles::paint(QPainter &resultPainter,
                    QPen &resultPen,
                    QPainter &usedPainter,
                    int &mean, unsigned int &x, unsigned int &y) {
    QPoint center(x+m_radiusX+(m_radiusOffsetX/2), y+m_radiusY+(m_radiusOffsetY/2));
    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawEllipse(center, m_radiusX, m_radiusY);

    if(m_printSolid)
        resultPainter.setBrush(QBrush(QColor(mean,mean,mean), Qt::SolidPattern));
    resultPen.setColor(QColor(mean,mean,mean));
    resultPainter.setPen(resultPen);
    resultPainter.drawEllipse(center, m_radiusX, m_radiusY);
}
