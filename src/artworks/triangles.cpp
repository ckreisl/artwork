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

Triangles::Triangles(const PropertyList &props)
    : ArtWork(props), ArtWorkGrey(props), ArtWorkColor(props) {

    isSolid = props.getBoolean("printSolidTriangles", false);
    bboxWidth = props.getInteger("bboxWidth", 35);
    bboxHeight = props.getInteger("bboxHeight", 35);
    stepSizeWidth = props.getInteger("bboxStepSizeWidth", 1);
    stepSizeHeight = props.getInteger("bboxStepSizeHeight", 1);
    minSizeWidth = props.getInteger("bboxMinSizeWidth", 4);
    minSizeHeight = props.getInteger("bboxMinSizeHeight", 4);
    triangleOffsetX = props.getInteger("triangleOffsetX", 0);
    triangleOffsetY = props.getInteger("triangleOffsetY", 0);

    if(minSizeWidth < triangleOffsetX)
        triangleOffsetX = minSizeWidth - 1;
    if(minSizeHeight < triangleOffsetY)
        triangleOffsetY = minSizeHeight - 1;

    bbox.setWidth(bboxWidth);
    bbox.setHeight(bboxHeight);

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_triangles_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_triangles_grey";
    }
}


void Triangles::paint(int mean, unsigned int &x, unsigned int &y) {
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
    if(isSolid)
        resultPainter.fillPath(path, QBrush(QColor(mean,mean,mean), Qt::SolidPattern));
    else
        resultPainter.drawPath(path);
}

void Triangles::paint(QColor mean, unsigned int &x, unsigned int &y) {
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
    if(isSolid)
        resultPainter.fillPath(path, QBrush(mean, Qt::SolidPattern));
    else
        resultPainter.drawPath(path);
}

inline bool Triangles::condition() {
    return (bboxWidth > minSizeWidth) && (bboxHeight > minSizeHeight);
}

inline bool Triangles::update() {
    bboxWidth -= stepSizeWidth;
    bboxHeight -= stepSizeHeight;

    bbox.setWidth(bboxWidth);
    bbox.setHeight(bboxHeight);

    return true;
}

void Triangles::getSamples(double &r1, double &r2) {
    do {
        r1 = ((double) rand() / (RAND_MAX));
        r2 = ((double) rand() / (RAND_MAX));
    } while ((r1*bboxWidth < 0.5*bboxWidth) || (r2*bboxHeight < 0.5*bboxHeight));
}

void Triangles::generateTriangle(QPointF &x1, QPointF &x2, QPointF &x3, unsigned int &x, unsigned int &y) {
    double r1 = 0, r2 = 0;
    switch ((int)rand() % 4) {
    case 0:
        x1.setX(x+triangleOffsetX);
        x1.setY(y+triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x + (bboxWidth-(r1*bboxWidth)));
        x2.setY(y + (bboxHeight-1) - triangleOffsetY);

        x3.setX(x + (bboxWidth-1) - triangleOffsetX);
        x3.setY(y + (bboxHeight-(r2*bboxHeight)));

        break;
    case 1:
        x1.setX(x+(bboxWidth-1)-triangleOffsetX);
        x1.setY(y+triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x+triangleOffsetX);
        x2.setY(y + (bboxHeight-(r1*bboxHeight)));

        x3.setX(x + (bboxWidth-(r2*bboxWidth)));
        x3.setY(y+(bboxHeight-1)-triangleOffsetY);

        break;
    case 2:
        x1.setX(x+triangleOffsetX);
        x1.setY(y+(bboxHeight-1)-triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x+r1*bboxWidth);
        x2.setY(y+triangleOffsetY);

        x3.setX(x+(bboxWidth-1)+triangleOffsetX);
        x3.setY(y+r2*bboxHeight);

        break;
    case 3:
        x1.setX(x+(bboxWidth-1)-triangleOffsetX);
        x1.setY(y+(bboxHeight-1)-triangleOffsetY);

        getSamples(r1, r2);

        x2.setX(x+r1*bboxWidth);
        x2.setY(y+triangleOffsetY);

        x3.setX(x+triangleOffsetX);
        x3.setY(y+r2*bboxHeight);

        break;
    }
}
