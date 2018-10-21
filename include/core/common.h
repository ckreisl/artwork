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
