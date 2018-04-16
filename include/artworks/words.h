#ifndef WORDS_H
#define WORDS_H

#include <include/renderer/artworkgrey.h>
#include <include/renderer/artworkcolor.h>

#include <QFont>

class Words : public ArtWorkGrey, public ArtWorkColor {
public:
    Words(const PropertyList &props);

    void paint(QColor mean, unsigned int &x, unsigned int &y);
    void paint(int mean, unsigned int &x, unsigned int &y);

    bool inline condition();
    bool inline update();

protected:
    virtual ~Words();

private:
    QFont *font;
    qreal fontSize;
    qreal fontCurSize;
    qreal fontStepSize;
    qreal fontMinSize;
    QString text;
};

#endif // WORDS_H
