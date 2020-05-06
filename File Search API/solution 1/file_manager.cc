#include <vector>
#include <string>

#include "file.h"
#include "file_attributes.h"
#include "file_manager.h"

struct PimpFileManager {
    std::vector<File> container;
};

FileManager::FileManager() : m_attributes(std::make_shared<PimpFileManager>()) {}

void FileManager::AddFiles(std::vector<File> &vfiles) {
    if(m_attributes)
    {
        for (auto &iter : vfiles)
        {
            auto file_attr = iter.GetFileAttributes();
            m_attributes->container.emplace_back(file_attr->Name, file_attr->Extension, file_attr->Size);
        }
    }
}

std::vector<File> FileManager::Search(SearchBase search_base, std::string search_str) {
    std::vector<File> ret;

    switch (search_base)
    {
    case SearchBase::extension : {
        ret = SearchExtension(search_str);
        break;
        }
    case SearchBase::name : {
        ret = SearchName(search_str);
        break;
        }
    case SearchBase::size : {
        uint64_t size_val = std::stoull(search_str);
        ret = SearchSize(size_val);
        break;
        }
    default: {}
        break;
    }

    return ret;
}

std::vector<File> FileManager::SearchExtension(const std::string search_etn) {
    std::vector<File> ret;

    for (auto &iter : m_attributes->container)
    {
        std::shared_ptr<FileAttributes> attr = iter.GetFileAttributes();
        if(search_etn == attr->Extension) {
            ret.emplace_back(iter);
        }
    }

    return ret;
}

std::vector<File> FileManager::SearchName(std::string search_name) {
    std::vector<File> ret;
    
    for (auto &iter : m_attributes->container)
    {
        std::shared_ptr<FileAttributes> attr = iter.GetFileAttributes();
        if(search_name == attr->Name) {
            ret.emplace_back(iter);
        }
    }

    return ret;
}

std::vector<File> FileManager::SearchSize(uint64_t search_size) {
    std::vector<File> ret;
    
    for (auto &iter : m_attributes->container)
    {
        std::shared_ptr<FileAttributes> attr = iter.GetFileAttributes();
        if(search_size == attr->Size) {
            ret.emplace_back(iter);
        }
    }

    return ret;
}
