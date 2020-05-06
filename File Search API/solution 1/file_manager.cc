#include "common.h"
#include "file_manager.h"

struct PimpFileManager {
    std::vector<File> container;
};

FileManager::FileManager() : m_attributes(std::make_shared<PimpFileManager>()) {}

// Add files in to file manager
void FileManager::AddFiles(std::vector<File> &vfiles) {
    if(m_attributes)
    {
        for (auto &iter : vfiles) m_attributes->container.emplace_back(iter);
    }
}

// Search for files in the file manager
std::vector<File> FileManager::Search(SearchBase search_base, FileMetaType search_value) {
    std::vector<File> ret;

    for(auto &iter : m_attributes->container) // for every file in the file-manager
    {
        auto attribute = iter.GetFileAttributes(); // get their attribues
        auto find = attribute.find(search_base);
        if(find != attribute.end()) {
            switch (find->first) {
                case Attributes::Size: { // if attribute is size then compare with integer type
                    if ( std::get<uint64_t>(find->second.value) == std::get<uint64_t>(search_value.value)) {
                        ret.emplace_back(iter);
                    }
                    break;
                }
                default: { // if attribute is anything else then compare with string type
                    if ( std::get<std::string>(find->second.value) == std::get<std::string>(search_value.value)) {
                        ret.emplace_back(iter);
                    }
                    break;
                }
            }
        }
    }

    return ret;
}
