#pragma once

enum class Tag : uint8_t {STRING, INT}; // Types of Attributes
using MusicArgVariant = std::variant<std::string, uint64_t>;

#define ATTRIBUTE  CODE(author,  STRING) \
                   CODE(name,    STRING) \
                   CODE(release, INT)

#undef CODE
#define CODE(__name, __type) __name,
enum class Attributes : uint64_t {  ATTRIBUTE // Expands here as enums
                                    Default
                                    };

using music = Attributes;

#undef CODE
#define CODE(__name, __type) case Attributes::__name: return Tag::__type;
constexpr Tag GetTagType(const Attributes attri) {
    switch(attri) {
       ATTRIBUTE // expands here as switch-case
        // case Attributes::author : return Tag::STRING;
        // case Attributes::name : return Tag::STRING;
        default: return Tag::INT;
    }
}

struct MusicMetaType {
    MusicArgVariant value;
    MusicMetaType() {}
    MusicMetaType(MusicArgVariant value) : value(value) {}
};

using umMusicAttribute = std::unordered_map<Attributes, MusicMetaType>;
using vMusicAttribute = std::vector<std::tuple<Attributes, MusicMetaType>>;
using vvMusicAttribute = std::vector<vMusicAttribute>;

struct MetaMusicValues : public MusicMetaType {
    Tag tag;
    void operator=(const MetaMusicValues &that) {
        value = that.value;
        tag = that.tag;
    }
    bool operator==(const MetaMusicValues &that) {
        switch (that.tag)
        {
        case Tag::INT : if(std::get<uint64_t>(value) == std::get<uint64_t>(that.value)) return true; break;
        case Tag::STRING : if(std::get<std::string>(value) == std::get<std::string>(that.value)) return true; break;
        }
        return false;
    }
    bool operator==(const MusicMetaType &that) {
        switch (tag)
        {
        case Tag::INT : if(std::get<uint64_t>(value) == std::get<uint64_t>(that.value)) return true; break;
        case Tag::STRING : if(std::get<std::string>(value) == std::get<std::string>(that.value)) return true; break;
        }
        return false;
    }
    MetaMusicValues() {}
    MetaMusicValues(MusicMetaType musicArgVariant, Tag tag)
        : MusicMetaType(musicArgVariant), tag(tag) {}
};

using umSongAttribute = std::unordered_map<Attributes, MetaMusicValues>;

struct MusicAttributes {
    umSongAttribute metadata; // music attributes
    MusicAttributes() {}
    MusicAttributes(umMusicAttribute metamap) {
        for (auto &iter : metamap)
        {
            metadata[iter.first] = MetaMusicValues(iter.second, GetTagType(iter.first));
        }
    }
    virtual ~MusicAttributes() {}
};
