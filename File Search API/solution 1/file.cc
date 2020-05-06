#include "common.h"
#include "file.h"

File::File(std::vector<std::tuple<Attributes, FileMetaType>> attributes) {
    std::unordered_map<Attributes, MetaValues> attribute_map;
    for(auto &iter : attributes)
    {
        auto [attribute_type, attribute_value] = iter;

        MetaValues metadata;
        metadata.tag = GetTagType(attribute_type);
        metadata.value = attribute_value.value;
        
        attribute_map.emplace(attribute_type, metadata);
    }
    m_attributes = std::make_shared<PimpFile>(attribute_map);
}

bool File::operator==(const File &that) const {
       return m_attributes->metadata[Attributes::Name] == that.m_attributes->metadata[Attributes::Name] &&
              m_attributes->metadata[Attributes::Extension] == that.m_attributes->metadata[Attributes::Extension] &&
              m_attributes->metadata[Attributes::Size] == that.m_attributes->metadata[Attributes::Size];
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

