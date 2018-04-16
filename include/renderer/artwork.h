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
