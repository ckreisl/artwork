#ifndef ARTWORKGREY_H
#define ARTWORKGREY_H

#include <QThread>
#include <include/renderer/artwork.h>

class ArtWorkGrey : virtual public ArtWork, public QThread {
public:
    ArtWorkGrey(const PropertyList &props);
    virtual ~ArtWorkGrey();

    void run();
    void calcMean(int &mean, unsigned int &imgX, unsigned int &imgY);
    void calcVar(int &variance, int &mean, unsigned int &imgX, unsigned int &imgY);
    inline bool checkMeanThreshold(int &mean);
    inline bool checkPrintThreshold(int &variance);

    virtual void paint(int mean, unsigned int &x, unsigned int &y) = 0;
    virtual inline bool condition() = 0;
    virtual inline bool update() = 0;

private:
    void preprocess();
    QImage *grayImg;
    vector< vector<unsigned int> > summedAreaTable;
};

#endif // ARTWORKGREY_H
