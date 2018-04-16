#ifndef COMMON_H
#define COMMON_H

#include <QString>

/**
 * @brief checkImageType
 * @param imgInput
 * @return true or false if correct image type is loaded
 */
bool checkImageType(QString imgInput);

/**
 * @brief removeFileType
 * @param inputString
 * @return QString without filetype (image.jpeg -> image)
 */
QString removeFileType(QString inputString);

/**
 * @brief getImageNameFromPath
 * @param imgPath
 * @return QString which holds the image name (removing path and image type)
 */
QString getImageNameFromPath(QString imgPath);

#endif // COMMON_H
