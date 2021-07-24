#include "xmlparser.h"

std::string MasterObject::GetTagName(void) const {
    return "";
}

XmlObjects
MasterObject::GetSubObjects(void) {
    return objs.sub_objects;
}

void
MasterObject::SetSubObject(std::shared_ptr<IObject> obj) {
    objs.sub_objects.push_back(obj);
}

Attributes
MasterObject::GetAttributes(void) const {
    Attributes atr;
    return atr;
}

void
MasterObject::SetAttribute(const Attribute attr) {
}

void
MasterObject::SetXmlValue(const std::string val) {
}
// ============

XmlObject::XmlObject(const std::string &tag)
: tag_name(tag) {
}

std::string
XmlObject::GetTagName(void) const {
    return tag_name;
}

std::string
XmlObject::GetTagValue(void) const {
    return tag_value.tag_value;
};

XmlObjects
XmlObject::GetSubObjects(void) {
    return tag_value.sub_objects;
}

void
XmlObject::SetSubObject(std::shared_ptr<IObject> obj) {
    tag_value.sub_objects.push_back(obj);
}

Attributes
XmlObject::GetAttributes(void) const {
    return attributes;
}

void
XmlObject::SetAttribute(const Attribute attr) {
    attributes.push_back(attr);
}

void
XmlObject::SetXmlValue(const std::string val) {
    tag_value.tag_value = val;
}
// ============

XmlObjectSpl::XmlObjectSpl()
{}

XmlObjectSpl::XmlObjectSpl(const std::string &tag)
: tag_name(tag) {
}

std::string
XmlObjectSpl::GetTagName(void) const {
    return tag_name;
}

XmlObjects
XmlObjectSpl::GetSubObjects(void) {
    XmlValue val;
    return val.sub_objects;
}

void
XmlObjectSpl::SetSubObject(std::shared_ptr<IObject> obj) {
}

Attributes
XmlObjectSpl::GetAttributes(void) const {
    return attributes;
}

void
XmlObjectSpl::SetAttribute(const Attribute attr) {
    attributes.push_back(attr);
}

void
XmlObjectSpl::SetXmlValue(const std::string val) {
}
// ============
