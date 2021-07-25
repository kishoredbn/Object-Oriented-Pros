#pragma once

#include <string>
#include <vector>
#include <memory> 

// abstract class
class IObject;

// representation of tags and values
struct Attribute {
    std::string tag;
    std::string value;
    bool Reset() { tag = std::string(); value=std::string(); return true;}
};

// representation of collection of objects and attributes
using XmlObjects = std::vector<std::shared_ptr<IObject>>;
using Attributes = std::vector<Attribute>;

// struct of tag-values and Xml-sub-objects
struct XmlValue {
    std::string tag_value;
    XmlObjects sub_objects;
    XmlValue(){}
    XmlValue(const XmlValue& other)
    : tag_value(this->tag_value)
    , sub_objects(this->sub_objects) {}
    ~XmlValue(){}
};

// abstract class to be overloaded by concrete objects
class IObject {
public:
    virtual std::string GetTagName(void) const = 0;
    virtual std::string GetTagValue(void) const = 0;
    virtual XmlObjects GetSubObjects(void) = 0;
    virtual void SetSubObject(std::shared_ptr<IObject> obj) = 0;
    virtual Attributes GetAttributes(void) const = 0;
    virtual void SetAttribute(const Attribute attr) = 0;
    virtual void SetXmlValue(const std::string val) = 0;
};

// class representing parent xml file
class MasterObject : public IObject {
private:
    XmlValue objs;
    virtual void SetXmlValue(const std::string val) override;
    virtual std::string GetTagValue(void) const override {return "";};
public:
    MasterObject(){}
    MasterObject(const MasterObject&) = delete;
    virtual std::string GetTagName(void) const override;
    virtual XmlObjects GetSubObjects(void) override;
    virtual void SetSubObject(std::shared_ptr<IObject> obj) override;
    virtual Attributes GetAttributes(void) const override;
    virtual void SetAttribute(const Attribute attr) override;
};

// class representing actual xml objects
class XmlObject : public IObject {
private:
    const std::string tag_name;
    XmlValue tag_value;
    Attributes attributes;
public:
    XmlObject(const std::string &tag);
    virtual std::string GetTagName(void) const override;
    virtual std::string GetTagValue(void) const override;
    virtual XmlObjects GetSubObjects(void) override;
    virtual void SetSubObject(std::shared_ptr<IObject> obj) override;
    virtual Attributes GetAttributes(void) const override;
    virtual void SetAttribute(const Attribute attr) override;
    virtual void SetXmlValue(const std::string val) override;
};

// class representing special xml objects - comments and others
class XmlObjectSpl : public IObject {
private:
    const std::string tag_name;
    Attributes attributes;
    virtual void SetSubObject(std::shared_ptr<IObject> obj) override;
    virtual void SetXmlValue(const std::string val) override;
    virtual std::string GetTagValue(void) const override {return "";};
public:
    XmlObjectSpl();
    XmlObjectSpl(const std::string &tag);
    virtual std::string GetTagName(void) const override;
    virtual XmlObjects GetSubObjects(void) override;
    virtual Attributes GetAttributes(void) const override;
    virtual void SetAttribute(const Attribute attr) override;
};
