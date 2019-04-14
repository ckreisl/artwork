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

Words::Words(const PropertyList &props) : RenderItem () {

    /* round parameters */
    m_text = props.getString("text", "c0op");
    m_fontSize = props.getFloat("fontStartSize", 35.0f);
    m_fontStepSize = props.getFloat("fontStepSize", 1.0f);
    m_fontMinSize = props.getFloat("fontMinSize", 0.5f);
    m_fontCurSize = m_fontSize;

    /* font settings */
    QString pathFont = props.getString("fontPath", "");
    int fontId = -1;

    if(QString::compare(pathFont, "", Qt::CaseInsensitive) != 0)
        fontId = QFontDatabase::addApplicationFont(pathFont);

    if(fontId > -1) {
        QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);
        QString fontName = fontList[0];
        m_font = new QFont(fontName);
    } else {
        m_font = new QFont("Times");
    }

    m_font->setPointSizeF(m_fontSize);

    if(props.getBoolean("colorMode", true)) {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "words_color";
    } else {
        if(QString::compare(props.getString("userCommandLineOutputName", ""), "", Qt::CaseInsensitive) == 0)
            m_outputName = "words_grey";
    }

}

Words::~Words() {
    delete m_font;
}

inline void Words::initBBox(QRect &bbox) {
    m_bbox = &bbox;
    QFontMetrics fontMetrics = QFontMetrics(*m_font);
    bbox = fontMetrics.boundingRect(m_text);
    bbox.setHeight(
                (bbox.height()
                 - (bbox.height()
                    - fontMetrics.overlinePos())));
}

inline bool Words::condition() {
    return m_fontCurSize > m_fontMinSize;
}

inline bool Words::update(QRect &bbox) {

    m_fontCurSize -= m_fontStepSize;

    if(m_font->pointSizeF() <= 0.5)
        return false;

    if(m_fontCurSize <= 0)
        m_font->setPointSizeF(1.0);
    else
        m_font->setPointSizeF(m_fontCurSize);

    QFontMetrics fontMetrics = QFontMetrics(*m_font);

    bbox = fontMetrics.boundingRect(m_text);
    bbox.setHeight(
                (bbox.height()
                 - (bbox.height()
                    - fontMetrics.overlinePos())));

    return true;
}

void Words::paint(QPainter &resultPainter,
                  QPen &resultPen,
                  QPainter &usedPainter,
                  int &mean, unsigned int &x, unsigned int &y) {
    usedPainter.setFont(*m_font);
    usedPainter.drawText(x, y + m_bbox->height(), m_text);

    resultPen.setColor(QColor(mean, mean , mean));
    resultPainter.setFont(*m_font);
    resultPainter.setPen(resultPen);
    resultPainter.drawText(x, y + m_bbox->height(), m_text);
}

void Words::paint(QPainter &resultPainter,
                  QPen &resultPen,
                  QPainter &usedPainter,
                  QColor &mean, unsigned int &x, unsigned int &y) {
    usedPainter.setFont(*m_font);
    usedPainter.drawText(x, y + m_bbox->height(), m_text);

    resultPen.setColor(mean);
    resultPainter.setFont(*m_font);
    resultPainter.setPen(resultPen);
    resultPainter.drawText(x, y + m_bbox->height(), m_text);
}
