#include "common.h"
#include "file.h"

struct File::PimpFile : public FileAttributes {
        PimpFile(std::unordered_map<Attributes, MetaValues> attributes)
            : FileAttributes(attributes) {}
};

File::File(std::vector<std::tuple<Attributes, FileMetaType>> attributes) {
    std::unordered_map<Attributes, MetaValues> attribute_map;
    for(auto &iter : attributes)
    {
        auto [attribute_type, attribute_value] = iter;

        MetaValues metadata(attribute_value.value, GetTagType(attribute_type));
        attribute_map.emplace(attribute_type, metadata);
    }
    m_attributes = std::make_shared<PimpFile>(attribute_map);
}

// Change file  attributes
void File::SetFileAttributes(std::unordered_map<Attributes, MetaValues>  attributes) {
    for(auto &iter : attributes)
    {
        m_attributes->metadata[std::get<0>(iter)] = std::get<1>(iter);
    }
}

// Get file attributes
std::unordered_map<Attributes, MetaValues>  File::GetFileAttributes() const {
    std::unordered_map<Attributes, MetaValues>  ret = m_attributes->metadata;
    return ret;
}
