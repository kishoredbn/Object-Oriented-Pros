#include "common.h"
#include "file_manager.h"

struct PimpFileManager {
    std::vector<spIFile> container;
};

FileManager::FileManager() : m_attributes(std::make_shared<PimpFileManager>()) {}

// Add files in to file manager
auto FileManager::AddFiles(std::vector<spIFile> vifiles) -> void {
    if(m_attributes)
    {
        //for (auto &iter : vifiles) m_attributes->container.emplace_back(iter);
        std::transform(vifiles.begin(), vifiles.end(), std::back_inserter(m_attributes->container), [](const auto &i) {
            assert(i != nullptr);
            return i; // Observe : How memory transfers internally to Filemanager Object
        });
    }
}

// Search for files in the file manager
auto FileManager::Search(SearchBase search_base) -> std::vector<spIFile> {
    std::vector<spIFile> ret;

    auto [search_attribute_type, search_attribute_value] = search_base.metadata;
    for(auto &iter : m_attributes->container) // for every file in the file-manager
    {
        assert(iter != nullptr);

        auto attribute = iter->GetFileAttributes(); // get their attribues
        auto find = attribute.find(search_attribute_type);

        if(find != attribute.end() && find->second.value == search_attribute_value.value)
            ret.emplace_back(iter);
    }

    return ret;
}
