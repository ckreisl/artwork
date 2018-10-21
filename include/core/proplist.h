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
