#include <include/core/common.h>
#include <iostream>

bool checkImageType(QString imgInput) {
    int pos = imgInput.lastIndexOf(QChar('.'));
    if(pos < 0)
        return false;

    QString type = imgInput.right(imgInput.length()-pos-1);
    if(type == "jpg" || type == "JPG" || type == "png" || type == "PNG" || type == "jpeg" || type == "JPEG")
        return true;

    return false;
}

QString removeFileType(QString inputString) {
    int pos = inputString.lastIndexOf(QChar('.'));
    if(pos > 0)
        return inputString.left(pos);
    else {
        throw std::runtime_error("There is no file type to remove");
    }
}

QString getImageNameFromPath(QString imgPath) {
    int pos = imgPath.lastIndexOf(QChar('/'));
    if(pos > -1)
        imgPath = imgPath.right(imgPath.length()-pos-1);

    return removeFileType(imgPath);
}
