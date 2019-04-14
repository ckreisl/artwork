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

#include <include/renderer/artwork.h>
#include <include/core/common.h>
#include <iostream>

ArtWork::ArtWork(const PropertyList &props, RenderItem *renderItem) {

    try {
        QString imgFilePath = "";
        QString userCommandLineInputImg = props.getString("userCommandLineInputImg", "");
        if(QString::compare(userCommandLineInputImg,"", Qt::CaseInsensitive) != 0)
            imgFilePath = userCommandLineInputImg;
        else {
            imgFilePath = props.getString("imgFilePath");
            if(!checkImageType(imgFilePath))
                throw std::runtime_error("Non or wrong image file type or forgot to set an image filepath!");
        }

        m_fileName = getImageNameFromPath(imgFilePath);

        QString userCommandLineOutputName = props.getString("userCommandLineOutputName", "");
        if(QString::compare(userCommandLineOutputName,"", Qt::CaseInsensitive) != 0) {
            m_outputName = userCommandLineOutputName;
            if(checkImageType(m_outputName))
                m_outputName = removeFileType(m_outputName);
        } else
            m_outputName = m_fileName;

        if(QString::compare(imgFilePath, "", Qt::CaseInsensitive) == 0)
            throw std::runtime_error("No image path was given. Set image path in .xml render settings file or with -i option");

        m_inputImg = new QImage(imgFilePath);
        if(m_inputImg->isNull())
            throw std::runtime_error("Could not load image file from given path. Image is invalid! Does the image exists or support the given file formats?");
    } catch(std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    } catch(...) {
        std::cout << "An unknown error occurd while loading the image." << std::endl;
        exit(-1);
    }

    m_outputName += "_" + renderItem->getOutputName();

    m_bbox = QRect();
    m_renderItem = renderItem;
    m_renderItem->initBBox(m_bbox);

    m_usedImg = new QImage(*m_inputImg);
    m_resultImg = new QImage(*m_inputImg);
    m_usedImg->fill(QColor(255, 255, 255));

    m_resultBackground = props.getColor("resultBackground", QColor(0,0,0));
    m_resultImg->fill(m_resultBackground);

    m_resultPainter.begin(m_resultImg);
    m_usedPainter.begin(m_usedImg);

    m_resultPen = QPen(QColor(0,0,0));
    m_usedPen = QPen(QColor(0,0,0));

    m_usedPainter.setPen(m_usedPen);

    /* load parameters via xml file */
    m_meanThresholdMin = props.getInteger("meanThresholdMin", 0);
    m_meanThresholdMax = props.getInteger("meanThresholdMax", 255);
    m_printThreshold = props.getInteger("printThreshold", 35);
    m_printThresholdStepSize = props.getInteger("printThresholdStepSize", 15);
    m_saveUsedImg = props.getBoolean("saveUsedImg", false);
    m_outputType = props.getString("imgFileFormatOutput", ".png");
}

ArtWork::~ArtWork() {
    m_usedPainter.end();
    m_resultPainter.end();
    delete m_inputImg;
    delete m_usedImg;
    delete m_resultImg;
    delete m_renderItem;
}

bool ArtWork::save() {
    try {
        m_resultImg->save(m_outputName + m_outputType);
        if(m_saveUsedImg)
            m_usedImg->save(m_outputName + "_usedImg" + m_outputType);
        return true;
    } catch(std::exception e) {
        cerr << "Could not save images: " << e.what() << endl;
        return false;
    }
}

bool ArtWork::isEmpty(unsigned int &imgX, unsigned int &imgY) {
    QRgb *pixelPtr = nullptr;
    for(unsigned int y = 0; y < m_bbox.height(); ++y) {
        pixelPtr = (QRgb *)m_usedImg->scanLine(imgY+y);
        for(unsigned int x = 0; x < m_bbox.width(); ++x) {
            if(qRed(pixelPtr[imgX+x]) < 255)
                return false;
        }
    }
    return true;
}
