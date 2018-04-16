#include <include/core/proplist.h>
#include <iostream>

using namespace std;

#define DEFINE_PROPERTY_ACCESSOR(Type, TypeName, XmlName) \
    void PropertyList::set##TypeName(const std::string &name, const Type &value) { \
        if (m_properties.find(name) != m_properties.end()) \
            cerr << "Property \"" << name <<  "\" was specified multiple times!" << endl; \
        auto &prop = m_properties[name]; \
        prop.value.XmlName##_value = value; \
        prop.type = Property::XmlName##_type; \
    } \
    \
    Type PropertyList::get##TypeName(const std::string &name) const { \
        auto it = m_properties.find(name); \
        return it->second.value.XmlName##_value; \
    } \
    \
    Type PropertyList::get##TypeName(const std::string &name, const Type &defVal) const { \
        auto it = m_properties.find(name); \
        if (it == m_properties.end()) \
            return defVal; \
        return it->second.value.XmlName##_value; \
    }

DEFINE_PROPERTY_ACCESSOR(bool, Boolean, boolean)
DEFINE_PROPERTY_ACCESSOR(int, Integer, integer)
DEFINE_PROPERTY_ACCESSOR(float, Float, float)
DEFINE_PROPERTY_ACCESSOR(QColor, Color, color)
DEFINE_PROPERTY_ACCESSOR(QString, String, string)
