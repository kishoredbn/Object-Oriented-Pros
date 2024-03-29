#pragma once

#include <string>
#include <tuple>
#include <memory> 
#include <variant>
#include <unordered_map>

enum class Tag : uint8_t {STRING, INT}; // Type of file attributes

#define ATTRIBUTE CODE(Name,       Tag::STRING) \
                  CODE(Extension,  Tag::STRING) \
                  CODE(Size,       Tag::INT) // extend attributes with more fields here

#undef CODE
#define CODE(name, type) name,
enum class Attributes : uint64_t { ATTRIBUTE // Expands here as enums
                                   Default };

using Atr = Attributes; // short-form notation

#undef CODE
#define CODE(name, type) case Attributes::name: return type;
constexpr Tag GetTagType(const Attributes attri) {
    switch(attri) {
        ATTRIBUTE // expands here as switch-case
        default: return Tag::INT;
    }
}

struct FileMetaType {
    std::variant<std::string, uint64_t> value;
    FileMetaType() {}
    FileMetaType(std::variant<std::string, uint64_t> value) : value(value) {}
};

struct MetaValues : public FileMetaType {
    Tag tag;
    void operator=(const MetaValues& that) {
        value = that.value;
        tag = that.tag;
    }
    bool operator==(const MetaValues &that) const {
        switch(that.tag) {
            case Tag::INT: if(std::get<uint64_t>(value) == std::get<uint64_t>(that.value)) return true; break;
            case Tag::STRING: if(std::get<std::string>(value) == std::get<std::string>(that.value)) return true; break;
        }
        return false;
    }
    MetaValues() {}
    MetaValues(FileMetaType attribute_value, Tag tag) 
        : FileMetaType(attribute_value), tag(tag) {}
};

struct SearchBase {
    std::tuple<Attributes, MetaValues> metadata;
    SearchBase(Attributes attributes, FileMetaType metavalue)
        : metadata(std::make_tuple(attributes, MetaValues(metavalue, GetTagType(attributes)))) {}
    bool operator==(const SearchBase &that) const {
        return metadata == that.metadata;
    }
};

using SearchBy = SearchBase;

struct FileAttributes {
    std::unordered_map<Attributes, MetaValues> metadata; // core idea of this solution : representing attributes as key-value pair
    FileAttributes(std::unordered_map<Attributes, MetaValues> attributes): metadata(attributes) {}
    virtual ~FileAttributes() {}
};
