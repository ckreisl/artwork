#ifndef PROPLIST_H
#define PROPLIST_H

#include <QColor>
#include <string>
#include <map>

class PropertyList {
public:
    PropertyList() { }

    void setBoolean(const std::string &name, const bool &value);
    bool getBoolean(const std::string &name) const;
    bool getBoolean(const std::string &name, const bool &defaultValue) const;

    void setInteger(const std::string &name, const int &value);
    int getInteger(const std::string &name) const;
    int getInteger(const std::string &name, const int &defaultValue) const;

    void setFloat(const std::string &name, const float &value);
    float getFloat(const std::string &name) const;
    float getFloat(const std::string &name, const float &defaultValue) const;

    void setColor(const std::string &name, const QColor &value);
    QColor getColor(const std::string &name) const;
    QColor getColor(const std::string &name, const QColor &defaultValue) const;

    void setString(const std::string &name, const QString &value);
    QString getString(const std::string &name) const;
    QString getString(const std::string &name, const QString &defaultValue) const;

private:
    struct Property {
        enum {
            boolean_type, integer_type, float_type,
            color_type, string_type
        } type;

        struct Value {
            Value() : boolean_value(false) { }
            ~Value() { }

            bool boolean_value;
            int integer_value;
            float float_value;
            QColor color_value;
            QString string_value;
        } value;

        Property() : type(boolean_type) { }
    };

    std::map<std::string, Property> m_properties;
};

#endif // PROPLIST_H
