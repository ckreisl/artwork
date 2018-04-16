#include <include/artworks/rectangle.h>

Rectangle::Rectangle(const PropertyList &props)
    : ArtWork(props), ArtWorkGrey(props), ArtWorkColor(props) {

    printSolid = props.getBoolean("printSolidRectangles", false);
    rectWidth = props.getInteger("rectWidth", 15);
    rectHeight = props.getInteger("rectHeight", 15);
    rectMinWidth = props.getInteger("rectMinWidth", 0);
    rectMinHeight = props.getInteger("rectMinHeight", 0);
    rectStepSizeWidth = props.getInteger("rectStepSizeWidth", 1);
    rectStepSizeHeight = props.getInteger("rectStepSizeHeight", 1);
    rectOffsetX = props.getInteger("rectOffsetX", 0);
    rectOffsetY = props.getInteger("rectOffsetY", 0);

    if(rectMinWidth < rectOffsetX)
        rectOffsetX = rectMinWidth - 1;
    if(rectMinHeight < rectOffsetY)
        rectOffsetY = rectMinHeight - 1;

    bbox = QRect();
    bbox.setWidth(rectWidth+rectOffsetX);
    bbox.setHeight(rectHeight+rectOffsetY);

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_rectangle_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_rectangle_grey";
    }
}

void Rectangle::paint(QColor mean, unsigned int &x, unsigned int &y) {
    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawRect(x, y, rectWidth, rectHeight);

    if(printSolid)
        resultPainter.setBrush(QBrush(mean, Qt::SolidPattern));
    resultPen.setColor(mean);
    resultPainter.setPen(resultPen);
    resultPainter.drawRect(x+rectOffsetX, y+rectOffsetY, rectWidth-rectOffsetX, rectHeight-rectOffsetY);
}

void Rectangle::paint(int mean, unsigned int &x, unsigned int &y) {

    usedPainter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    usedPainter.drawRect(x, y, rectWidth, rectHeight);

    if(printSolid)
        resultPainter.setBrush(QBrush(QColor(mean,mean,mean), Qt::SolidPattern));
    resultPen.setColor(QColor(mean,mean,mean));
    resultPainter.setPen(resultPen);
    resultPainter.drawRect(x+rectOffsetX, y+rectOffsetY, rectWidth-rectOffsetX, rectHeight-rectOffsetY);
}

inline bool Rectangle::condition() {
    return (rectWidth > rectMinWidth) && (rectHeight > rectMinHeight);
}

inline bool Rectangle::update() {
    rectWidth -= rectStepSizeWidth;
    rectHeight -= rectStepSizeHeight;

    bbox.setWidth(rectWidth);
    bbox.setHeight(rectHeight);

    return true;
}

