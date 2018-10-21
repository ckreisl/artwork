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

using namespace std;

Circles::Circles(const PropertyList &props)
    : ArtWork(props), ArtWorkGrey(props), ArtWorkColor(props) {

    printSolid = props.getBoolean("printSolidCircles", false);
    radiusX = props.getInteger("radiusX", 8);
    radiusY = props.getInteger("radiusY", 8);
    radiusXStepSize = props.getInteger("radiusXStepSize", 1);
    radiusYStepSize = props.getInteger("radiusYStepSize", 1);
    minRadiusX = props.getInteger("minRadiusX", 0);
    minRadiusY = props.getInteger("minRadiusY", 0);
    radiusOffsetX = props.getInteger("radiusOffsetX", 0);
    radiusOffsetY = props.getInteger("radiusOffsetY", 0);

    if(minRadiusX < radiusOffsetX)
        radiusOffsetX = minRadiusX - 1;
    if(minRadiusY < radiusOffsetY)
        radiusOffsetY = minRadiusY - 1;

    bbox = QRect();
    bbox.setWidth((2*radiusX)+radiusOffsetX);
    bbox.setHeight((2*radiusY)+radiusOffsetY);

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_circles_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_circles_grey";
    }
}

inline bool Circles::condition() {
    return (radiusX > minRadiusX) && (radiusY > minRadiusY);
}

inline bool Circles::update() {
    radiusX -= radiusXStepSize;
    radiusY -= radiusYStepSize;

    bbox.setWidth((2*radiusX)+radiusOffsetX);
    bbox.setHeight((2*radiusY)+radiusOffsetY);

    return true;
}

void Circles::paint(QColor mean, unsigned int &x, unsigned int &y) {
    QPoint center(x+radiusX+(radiusOffsetX/2),y+radiusY+(radiusOffsetY/2));
    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawEllipse(center, radiusX, radiusY);

    if(printSolid)
        resultPainter.setBrush(QBrush(mean, Qt::SolidPattern));
    resultPen.setColor(mean);
    resultPainter.setPen(resultPen);
    resultPainter.drawEllipse(center, radiusX, radiusY);
}

void Circles::paint(int mean, unsigned int &x, unsigned int &y) {
    QPoint center(x+radiusX+(radiusOffsetX/2), y+radiusY+(radiusOffsetY/2));
    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawEllipse(center, radiusX, radiusY);

    if(printSolid)
        resultPainter.setBrush(QBrush(QColor(mean,mean,mean), Qt::SolidPattern));
    resultPen.setColor(QColor(mean,mean,mean));
    resultPainter.setPen(resultPen);
    resultPainter.drawEllipse(center, radiusX, radiusY);
}
