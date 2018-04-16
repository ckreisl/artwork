#include <include/core/parser.h>

#include <QXmlStreamReader>
#include <QFile>
#include <QDir>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <iostream>

enum ArtValues {
    ArtBoolean,
    ArtInteger,
    ArtFloat,
    ArtString,
    ArtColor
};

typedef std::map<std::string, ArtValues> ArtTags;

void setProperty(QString name, QXmlStreamReader &xml, PropertyList *props, ArtTags &tags) {

    try {
        switch (tags[name.toStdString()]) {
        case ArtBoolean:
            props->setBoolean(xml.attributes().value("name").toString().toStdString(),
                              (xml.attributes().value("value").toString().toStdString() == "true") ? true : false);
            break;
        case ArtInteger:
            props->setInteger(xml.attributes().value("name").toString().toStdString(),
                              xml.attributes().value("value").toInt());
            break;
        case ArtFloat:
            props->setFloat(xml.attributes().value("name").toString().toStdString(),
                            xml.attributes().value("value").toFloat());
            break;
        case ArtString:
            props->setString(xml.attributes().value("name").toString().toStdString(),
                             xml.attributes().value("value").toString());
            break;
        case ArtColor:
            QStringList colorSplit = xml.attributes().value("value").toString().split(",");
            QColor color;
            if(colorSplit.size() > 3)
                color = QColor(0,0,0);
            else
                color = QColor(colorSplit[0].toInt(), colorSplit[1].toInt(), colorSplit[2].toInt());

            if(!color.isValid())
                color = QColor(0,0,0);

            props->setColor(xml.attributes().value("name").toString().toStdString(),
                            color);
            break;
        }
    } catch(std::exception e) {
        std::cerr << "Error by parsing the XML file: " << e.what() << std::endl;
    }
}

void loadRenderSettingsFromXML(QXmlStreamReader &xml, PropertyList *props, ArtTags &tags) {
    int elements = 9;
    for(int i=0; i<elements;) {
        QXmlStreamReader::TokenType t = xml.readNext();
        if(t == QXmlStreamReader::Characters || t == QXmlStreamReader::EndElement)
            continue;
        else {
            setProperty(xml.name().toString(), xml, props, tags);
            ++i;
        }
    }
}

void loadWordsSettingsFromXML(QXmlStreamReader &xml, PropertyList *props, ArtTags &tags) {
    int elements = 6;
    for(int i=0; i<elements;) {
        QXmlStreamReader::TokenType t = xml.readNext();
        if(t == QXmlStreamReader::Characters || t == QXmlStreamReader::EndElement)
            continue;
        else {
            setProperty(xml.name().toString(), xml, props, tags);
            ++i;
        }
    }
}

void loadTriangleSettingsFromXML(QXmlStreamReader &xml, PropertyList *props, ArtTags &tags) {
    int elements = 10;
    for(int i=0; i<elements;) {
        QXmlStreamReader::TokenType t = xml.readNext();
        if(t == QXmlStreamReader::Characters || t == QXmlStreamReader::EndElement)
            continue;
        else {
            setProperty(xml.name().toString(), xml, props, tags);
            ++i;
        }
    }
}

void loadCircleSettingsFromXML(QXmlStreamReader &xml, PropertyList *props, ArtTags &tags) {
    int elements = 10;
    for(int i=0; i<elements;) {
        QXmlStreamReader::TokenType t = xml.readNext();
        if(t == QXmlStreamReader::Characters || t == QXmlStreamReader::EndElement)
            continue;
        else {
            setProperty(xml.name().toString(), xml, props, tags);
            ++i;
        }
    }
}

void loadRectangleSettingsFromXML(QXmlStreamReader &xml, PropertyList *props, ArtTags &tags) {
    int elements = 10;
    for(int i=0; i<elements;) {
        QXmlStreamReader::TokenType t = xml.readNext();
        if(t == QXmlStreamReader::Characters || t == QXmlStreamReader::EndElement)
            continue;
        else {
            setProperty(xml.name().toString(), xml, props, tags);
            ++i;
        }
    }
}

PropertyList *loadFromXML(const QString &filename) {

    ArtTags tags;
    tags["boolean"] = ArtBoolean;
    tags["integer"] = ArtInteger;
    tags["float"] = ArtFloat;
    tags["string"] = ArtString;
    tags["color"] = ArtColor;

    PropertyList *props = new PropertyList();

    QFile *file = new QFile(filename);

    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return NULL;
    }

    QXmlStreamReader xml(file);

    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if(token == QXmlStreamReader::Invalid) {
            std::cerr << "Error Parsing XML-File. XML File reader reported INVALID" << std::endl;
            break;
        }

        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "rendersettings")
                loadRenderSettingsFromXML(xml, props, tags);

            if(xml.name() == "words")
                loadWordsSettingsFromXML(xml, props, tags);

            if(xml.name() == "triangles")
                loadTriangleSettingsFromXML(xml, props, tags);

            if(xml.name() == "circles")
                loadCircleSettingsFromXML(xml, props, tags);

            if(xml.name() == "rectangles")
                loadRectangleSettingsFromXML(xml, props, tags);

        }
    }

    return props;
}
