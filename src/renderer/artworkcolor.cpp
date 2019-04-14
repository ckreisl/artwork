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

#include <include/renderer/artworkcolor.h>
#include <iostream>

ArtWorkColor::ArtWorkColor(const PropertyList &props, RenderItem *renderItem)
    : ArtWork(props, renderItem) {

    unsigned int width = m_inputImg->width();
    unsigned int height = m_inputImg->height();

    // init size of 2D vector for summed-area table
    summedAreaTableRed.resize(width);
    summedAreaTableGreen.resize(width);
    summedAreaTableBlue.resize(width);
    for(unsigned int i = 0; i < width; ++i) {
        summedAreaTableRed[i].resize(height);
        summedAreaTableGreen[i].resize(height);
        summedAreaTableBlue[i].resize(height);
    }

    preprocess();
}

ArtWorkColor::~ArtWorkColor() {

}

inline bool ArtWorkColor::checkMeanThreshold(QColor &mean) {
    return ((mean.red() >= m_meanThresholdMin) &&
            (mean.green() >= m_meanThresholdMin) &&
            (mean.blue() >= m_meanThresholdMin) &&
            (mean.red() <= m_meanThresholdMax) &&
            (mean.green() <= m_meanThresholdMax) &&
            (mean.blue() <= m_meanThresholdMax));
}

inline bool ArtWorkColor::checkPrintThreshold(Vec3 &variance) {
    return ((variance[0] < m_printThreshold) &&
            (variance[1] < m_printThreshold) &&
            (variance[2] < m_printThreshold));
}

void ArtWorkColor::preprocess() {
    // generate summed-area table to calculate mean of rectangle in O(1)
    QRgb *pixelPtr = nullptr;
    int valueRed = 0, valueGreen = 0, valueBlue = 0;
    for(unsigned int y = 0; y < m_inputImg->height(); ++y) {
        pixelPtr = (QRgb *)m_inputImg->scanLine(y);
        for(unsigned int x = 0; x < m_inputImg->width(); ++x) {
            valueRed = qRed(pixelPtr[x]);
            valueGreen = qGreen(pixelPtr[x]);
            valueBlue = qBlue(pixelPtr[x]);
            if(y > 0) {
                valueRed += summedAreaTableRed[x][y-1];
                valueGreen += summedAreaTableGreen[x][y-1];
                valueBlue += summedAreaTableBlue[x][y-1];
            }
            if(x > 0) {
                valueRed += summedAreaTableRed[x-1][y];
                valueGreen += summedAreaTableGreen[x-1][y];
                valueBlue += summedAreaTableBlue[x-1][y];
            }
            if(x > 0 && y > 0) {
                valueRed -= summedAreaTableRed[x-1][y-1];
                valueGreen -= summedAreaTableGreen[x-1][y-1];
                valueBlue -= summedAreaTableBlue[x-1][y-1];
            }
            summedAreaTableRed[x][y] = valueRed;
            summedAreaTableGreen[x][y] = valueGreen;
            summedAreaTableBlue[x][y] = valueBlue;
        }
    }
}

void ArtWorkColor::calcMean(QColor &mean, unsigned int &imgX, unsigned int &imgY) {
    int meanRed = 0, meanGreen = 0, meanBlue = 0;
    if(imgX > 0 && imgY > 0) {
        meanRed += summedAreaTableRed[imgX-1][imgY-1];
        meanGreen += summedAreaTableGreen[imgX-1][imgY-1];
        meanBlue += summedAreaTableBlue[imgX-1][imgY-1];
    }
    if(imgY > 0) {
        meanRed -= summedAreaTableRed[imgX-1+m_bbox.width()][imgY-1];
        meanGreen -= summedAreaTableGreen[imgX-1+m_bbox.width()][imgY-1];
        meanBlue -= summedAreaTableBlue[imgX-1+m_bbox.width()][imgY-1];
    }
    if(imgX > 0) {
        meanRed -= summedAreaTableRed[imgX-1][imgY-1+m_bbox.height()];
        meanGreen -= summedAreaTableGreen[imgX-1][imgY-1+m_bbox.height()];
        meanBlue -= summedAreaTableBlue[imgX-1][imgY-1+m_bbox.height()];
    }

    meanRed += summedAreaTableRed[imgX+m_bbox.width()-1][imgY+m_bbox.height()-1];
    meanGreen += summedAreaTableGreen[imgX+m_bbox.width()-1][imgY+m_bbox.height()-1];
    meanBlue += summedAreaTableBlue[imgX+m_bbox.width()-1][imgY+m_bbox.height()-1];

    int n = (m_bbox.width() * m_bbox.height());

    meanRed /= n;
    meanGreen /= n;
    meanBlue /= n;

    mean.setRed(meanRed);
    mean.setGreen(meanGreen);
    mean.setBlue(meanBlue);
}

void ArtWorkColor::calcVar(Vec3 &variance, QColor &mean, unsigned int &imgX, unsigned int &imgY) {
    QRgb *pixelPtr = nullptr;
    int varRed = 0, varGreen = 0, varBlue = 0, tmp = 0;
    for(unsigned int y = 0; y < m_bbox.height(); ++y) {
        pixelPtr = (QRgb *)m_inputImg->scanLine(imgY+y);
        for(unsigned int x = 0; x < m_bbox.width(); ++x) {
            tmp = qRed(pixelPtr[imgX+x]) - mean.red();
            varRed += (tmp * tmp);
            tmp = qGreen(pixelPtr[imgX+x]) - mean.green();
            varGreen += (tmp * tmp);
            tmp = qBlue(pixelPtr[imgX+x]) - mean.blue();
            varBlue += (tmp * tmp);
        }
    }

    int n = (m_bbox.width() * m_bbox.height());

    varRed /= n;
    varGreen /= n;
    varBlue /= n;

    variance[0] = varRed;
    variance[1] = varGreen;
    variance[2] = varBlue;
}

void ArtWorkColor::run() {
    auto final_start = std::chrono::high_resolution_clock::now();

    QColor mean(0,0,0);
    Vec3 variance(3);
    int printed = 0;

    while(m_renderItem->condition()) {
        unsigned int yMax = m_inputImg->height() - m_bbox.height();
        unsigned int xMax = m_inputImg->width() - m_bbox.width();

        /* Round Step Start */
        auto start = std::chrono::high_resolution_clock::now();

        for(unsigned int imgY = 0; imgY < yMax; ++imgY) {
            for(unsigned int imgX = 0; imgX < xMax; /*nothing todo here */) {
                // (1) check if we got a free space to print
                if(isEmpty(imgX, imgY)) {
                    // (2) check mean
                    calcMean(mean, imgX, imgY);
                    // (3) check mean threshold, do not print black on black
                    if(checkMeanThreshold(mean)) {
                        // (4) calculate variance
                        calcVar(variance, mean, imgX, imgY);
                        // (5) check print threshold
                        if(checkPrintThreshold(variance)) {
                            // (6) print text on used and result image
                            m_renderItem->paint(m_resultPainter,
                                                m_resultPen,
                                                m_usedPainter,
                                                mean, imgX, imgY);
                            // (7) update x with bbox.width because of print
                            imgX += m_bbox.width();
                            ++printed;
                        } else {
                            ++imgX;
                        }
                    } else {
                        ++imgX;
                    }
                } else {
                    ++imgX;
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto round_time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        cout << "Round runtime Color: " << round_time.count() << "ms Printed: " << printed << endl;
        printed = 0;

        m_printThreshold += m_printThresholdStepSize;

        /* Round Step End */
        if(!m_renderItem->update(m_bbox))
            break;

    }

    auto final_end = std::chrono::high_resolution_clock::now();
    auto final_time = std::chrono::duration_cast<std::chrono::milliseconds>(final_end-final_start);
    cout << "Final runtime Color: " << final_time.count() << "ms" << endl;

    /* save images */
    save();
}
