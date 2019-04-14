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

#ifndef WORDS_H
#define WORDS_H

#include <include/renderer/renderitem.h>
#include <include/core/proplist.h>
#include <QFont>

class Words : public RenderItem {
public:
    Words(const PropertyList &props);
    ~Words();

    inline void initBBox(QRect &bbox);

    void paint(QPainter &resultPainter,
               QPen &resultPen,
               QPainter &usedPainter,
               QColor &mean,
               unsigned int &x,
               unsigned int &y);

    void paint(QPainter &resultPainter,
               QPen &resultPen,
               QPainter &usedPainter,
               int &mean,
               unsigned int &x,
               unsigned int &y);

    inline bool condition();
    inline bool update(QRect &bbox);
    inline const QString& getOutputName() const { return m_outputName; }

private:
    QString m_outputName;
    QFont*  m_font;
    qreal   m_fontSize;
    qreal   m_fontCurSize;
    qreal   m_fontStepSize;
    qreal   m_fontMinSize;
    QString m_text;
    QRect*  m_bbox;
};

#endif // WORDS_H
