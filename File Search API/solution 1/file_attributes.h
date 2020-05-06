#pragma once

enum class Tag : uint8_t {STRING, INT}; // Type of file attributes

#define ATTRIBUTE CODE(Name,       Tag::STRING) \
                  CODE(Extension,  Tag::STRING) \
                  CODE(Size,       Tag::INT)    \
                  CODE(Creation,   Tag::STRING) \
                  CODE(Expiration, Tag::STRING) // extend attributes with more fields here

#undef CODE
#define CODE(name, type) name, // Expands here as enums
enum class Attributes : uint64_t { ATTRIBUTE 
                                   Default};
#undef CODE
#define CODE(name, type) case Attributes::name: return type; // expands here as switch-case
constexpr Tag GetTagType(const Attributes attri) {
    switch(attri) {
        ATTRIBUTE
        default: return Tag::INT;
    }
}

struct FileMetaType {
    std::variant<std::string, uint64_t> value;
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
};

struct FileAttributes {
    std::unordered_map<Attributes, MetaValues> metadata; // core idea of this solution : representing attributes as key-value pair
    FileAttributes(std::unordered_map<Attributes, MetaValues> attributes): metadata(attributes) {}
    virtual ~FileAttributes() {}
};
