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
