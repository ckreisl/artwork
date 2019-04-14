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

#include <include/renderer/artworkgrey.h>
#include <iostream>

ArtWorkGrey::ArtWorkGrey(const PropertyList &props, RenderItem *renderItem)
    : ArtWork(props, renderItem) {

    // init gray image
    grayImg = new QImage(*m_inputImg);
    grayImg->fill(QColor(255,255,255));

    // init size of 2D vector for summed-area table
    summedAreaTable.resize(grayImg->width());
    for(unsigned int i = 0; i < grayImg->width(); ++i)
        summedAreaTable[i].resize(grayImg->height());

    preprocess();
}

ArtWorkGrey::~ArtWorkGrey() {
    delete grayImg;
}

inline bool ArtWorkGrey::checkMeanThreshold(int &mean) {
    return ((mean >= m_meanThresholdMin) && (mean <= m_meanThresholdMax));
}

inline bool ArtWorkGrey::checkPrintThreshold(int &variance) {
    return variance < m_printThreshold;
}

void ArtWorkGrey::preprocess() {
    // convert input image into grayscale image
    QRgb *pixelPtr = nullptr;
    QRgb *pixelGrayPtr = nullptr;
    int gray = 0;
    for(unsigned int y = 0; y < m_inputImg->height(); ++y) {
        pixelPtr = (QRgb *)m_inputImg->scanLine(y);
        pixelGrayPtr = (QRgb *)grayImg->scanLine(y);
        for(unsigned int x = 0; x < m_inputImg->width(); ++x) {
            gray = qGray(pixelPtr[x]);
            pixelGrayPtr[x] = qRgb(gray, gray, gray);
        }
    }

    // generate summed-area table to calculate mean of rectangle in O(1)
    int value = 0;
    for(unsigned int y = 0; y < grayImg->height(); ++y) {
        pixelPtr = (QRgb *)grayImg->scanLine(y);
        for(unsigned int x = 0; x < grayImg->width(); ++x) {
            value = qRed(pixelPtr[x]);
            if(y > 0)
                value += summedAreaTable[x][y-1];
            if(x > 0)
                value += summedAreaTable[x-1][y];
            if(x > 0 && y > 0)
                value -= summedAreaTable[x-1][y-1];
            summedAreaTable[x][y] = value;
        }
    }
}

void ArtWorkGrey::calcMean(int &mean, unsigned int &imgX, unsigned int &imgY) {
    mean = 0;
    if(imgX > 0 && imgY > 0)
        mean += summedAreaTable[imgX-1][imgY-1];
    if(imgY > 0)
        mean -= summedAreaTable[imgX-1+m_bbox.width()][imgY-1];
    if(imgX > 0)
        mean -= summedAreaTable[imgX-1][imgY-1+m_bbox.height()];

    mean += summedAreaTable[imgX+m_bbox.width()-1][imgY+m_bbox.height()-1];
    mean /= (m_bbox.width() * m_bbox.height());
}

void ArtWorkGrey::calcVar(int &variance, int &mean, unsigned int &imgX, unsigned int &imgY) {
    QRgb *pixelPtr = nullptr;
    variance = 0;
    int var = 0;
    for(unsigned int y = 0; y < m_bbox.height(); ++y) {
        pixelPtr = (QRgb *)grayImg->scanLine(imgY+y);
        for(unsigned int x = 0; x < m_bbox.width(); ++x) {
            var = qRed(pixelPtr[imgX+x]) - mean;
            variance += (var * var);
        }
    }

    variance /= (m_bbox.width() * m_bbox.height());
}

void ArtWorkGrey::run() {
    auto final_start = std::chrono::high_resolution_clock::now();

    int mean = 0;
    int variance = 0;
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
        cout << "Round runtime Grey: " << round_time.count() << "ms Printed: " << printed << endl;
        printed = 0;

        m_printThreshold += m_printThresholdStepSize;

        /* Round Step End */
        if(!m_renderItem->update(m_bbox))
            break;

    }

    auto final_end = std::chrono::high_resolution_clock::now();
    auto final_time = std::chrono::duration_cast<std::chrono::milliseconds>(final_end-final_start);
    cout << "Final runtime Grey: " << final_time.count() << "ms" << endl;

    /* save images */
    save();
}
