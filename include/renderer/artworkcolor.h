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
