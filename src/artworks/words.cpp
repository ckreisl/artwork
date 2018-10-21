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

#include <include/artworks/words.h>

#include <QString>
#include <QFontDatabase>
#include <QStringList>
#include <QFontMetrics>

Words::Words(const PropertyList &props)
    : ArtWork(props), ArtWorkGrey(props), ArtWorkColor(props) {

    /* round parameters */
    text = props.getString("text", "c0op");
    fontSize = props.getFloat("fontStartSize", 35);
    fontStepSize = props.getFloat("fontStepSize", 1);
    fontMinSize = props.getFloat("fontMinSize", 0.5);
    fontCurSize = fontSize;

    /* font settings */
    QString pathFont = props.getString("fontPath", "");
    int fontId = -1;

    if(QString::compare(pathFont, "", Qt::CaseInsensitive) != 0)
        fontId = QFontDatabase::addApplicationFont(pathFont);

    if(fontId > -1) {
        QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);
        QString fontName = fontList[0];
        font = new QFont(fontName);
    } else {
        font = new QFont("Times");
    }

    font->setPointSizeF(fontSize);
    QFontMetrics fontMetrics = QFontMetrics(*font);

    bbox = fontMetrics.boundingRect(text);
    bbox.setHeight(
                (bbox.height()
                 - (bbox.height()
                    - fontMetrics.overlinePos())));

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_words_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            outputName += "_words_grey";
    }

}

Words::~Words() {
    delete font;
}

inline bool Words::condition() {
    return fontCurSize > fontMinSize;
}

inline bool Words::update() {

    fontCurSize -= fontStepSize;

    if(font->pointSizeF() <= 0.5)
        return false;

    if(fontCurSize <= 0)
        font->setPointSizeF(1.0);
    else
        font->setPointSizeF(fontCurSize);

    QFontMetrics fontMetrics = QFontMetrics(*font);

    bbox = fontMetrics.boundingRect(text);
    bbox.setHeight(
                (bbox.height()
                 - (bbox.height()
                    - fontMetrics.overlinePos())));

    return true;
}

void Words::paint(int mean, unsigned int &x, unsigned int &y) {
    usedPainter.setFont(*font);
    usedPainter.drawText(x, y + bbox.height(), text);

    resultPen.setColor(QColor(mean, mean , mean));
    resultPainter.setFont(*font);
    resultPainter.setPen(resultPen);
    resultPainter.drawText(x, y + bbox.height(), text);
}

void Words::paint(QColor mean, unsigned int &x, unsigned int &y) {
    usedPainter.setFont(*font);
    usedPainter.drawText(x, y + bbox.height(), text);

    resultPen.setColor(mean);
    resultPainter.setFont(*font);
    resultPainter.setPen(resultPen);
    resultPainter.drawText(x, y + bbox.height(), text);
}
