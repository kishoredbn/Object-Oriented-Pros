#pragma once

enum class Attributes : uint64_t {  Name      = 0,
                                    Extension = 1,
                                    Size      = 2}; // extend attributes with more fields here

struct FileMetaType {
    std::variant<std::string, uint64_t> value;
};

struct MetaValues : public FileMetaType {
    enum class Tag : uint8_t {STRING, INT};
    Tag tag;
    void operator=(const MetaValues& that) {
        value = that.value;
        tag = that.tag;
    }
    bool operator==(const MetaValues &that) const {
        switch(that.tag) {
            case MetaValues::Tag::INT: if(std::get<uint64_t>(value) == std::get<uint64_t>(that.value)) return true; break;
            case MetaValues::Tag::STRING: if(std::get<std::string>(value) == std::get<std::string>(that.value)) return true; break;
        }
        return false;
    }
};

struct FileAttributes {
    std::unordered_map<Attributes, MetaValues> metadata; // core idea of this solution : representing attributes as key-value pair
    FileAttributes(std::unordered_map<Attributes, MetaValues> attributes): metadata(attributes) {}
    virtual ~FileAttributes() {}
};
