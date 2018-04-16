#include <include/renderer/artwork.h>
#include <include/core/common.h>
#include <iostream>

ArtWork::ArtWork(const PropertyList &props) {

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

        fileName = getImageNameFromPath(imgFilePath);

        QString userCommandLineOutputName = props.getString("userCommandLineOutputName", "");
        if(QString::compare(userCommandLineOutputName,"", Qt::CaseInsensitive) != 0) {
            outputName = userCommandLineOutputName;
            if(checkImageType(outputName))
                outputName = removeFileType(outputName);
        } else
            outputName = fileName;

        if(QString::compare(imgFilePath, "", Qt::CaseInsensitive) == 0)
            throw std::runtime_error("No image path was given. Set image path in .xml render settings file or with -i option");

        inputImg = new QImage(imgFilePath);
        if(inputImg->isNull())
            throw std::runtime_error("Could not load image file from given path. Image is invalid! Does the image exists or support the given file formats?");
    } catch(std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    usedImg = new QImage(*inputImg);
    resultImg = new QImage(*inputImg);
    usedImg->fill(QColor(255, 255, 255));

    resultBackground = props.getColor("resultBackground", QColor(0,0,0));
    resultImg->fill(resultBackground);

    resultPainter.begin(resultImg);
    usedPainter.begin(usedImg);

    resultPen = QPen(QColor(0,0,0));
    usedPen = QPen(QColor(0,0,0));

    usedPainter.setPen(usedPen);

    /* load parameters via xml file */
    meanThresholdMin = props.getInteger("meanThresholdMin", 0);
    meanThresholdMax = props.getInteger("meanThresholdMax", 255);
    printThreshold = props.getInteger("printThreshold", 35);
    printThresholdStepSize = props.getInteger("printThresholdStepSize", 15);
    saveUsedImg = props.getBoolean("saveUsedImg", false);
    outputType = props.getString("imgFileFormatOutput", ".png");
}

ArtWork::~ArtWork() {
    usedPainter.end();
    resultPainter.end();
    delete inputImg;
    delete usedImg;
    delete resultImg;
}

bool ArtWork::save() {
    try {
        resultImg->save(outputName + outputType);
        if(saveUsedImg)
            usedImg->save(outputName + "_usedImg" + outputType);
        return true;
    } catch(std::exception e) {
        cerr << "Could not save images: " << e.what() << endl;
        return false;
    }
}

bool ArtWork::isEmpty(unsigned int &imgX, unsigned int &imgY) {
    QRgb *pixelPtr = 0;
    for(unsigned int y = 0; y < bbox.height(); ++y) {
        pixelPtr = (QRgb *)usedImg->scanLine(imgY+y);
        for(unsigned int x = 0; x < bbox.width(); ++x) {
            if(qRed(pixelPtr[imgX+x]) < 255)
                return false;
        }
    }
    return true;
}
