#ifndef ARTWORKCOLOR_H
#define ARTWORKCOLOR_H

#include <QThread>
#include <include/renderer/artwork.h>

#include <QDebug>

typedef vector<unsigned int> Vec3;

class ArtWorkColor : virtual public ArtWork, public QThread {
public:
    ArtWorkColor(const PropertyList &props);
    virtual ~ArtWorkColor() { }

    void run();
    void calcMean(QColor &mean, unsigned int &imgX, unsigned int &imgY);
    void calcVar(Vec3 &variance, QColor &mean, unsigned int &imgX, unsigned int &imgY);
    inline bool checkMeanThreshold(QColor &mean);
    inline bool checkPrintThreshold(Vec3 &variance);

    virtual void paint(QColor mean, unsigned int &x, unsigned int &y) = 0;
    virtual inline bool condition() = 0;
    virtual inline bool update() = 0;

private:
    void preprocess();
    vector< vector<unsigned int> > summedAreaTableRed;
    vector< vector<unsigned int> > summedAreaTableGreen;
    vector< vector<unsigned int> > summedAreaTableBlue;
};

#endif // ARTWORKCOLOR_H
