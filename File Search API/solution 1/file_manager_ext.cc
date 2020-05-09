#include "common.h"
#include "file_manager_ext.h"

struct FileManagerV2::THash {
    size_t operator()(const spIFile &file) const {
        assert(file != nullptr);
        auto atr = file->GetFileAttributes();
        return std::hash<std::string>{}(std::get<std::string>((atr[Attributes::Name]).value)) +
                std::hash<std::string>{}(std::get<std::string>((atr[Attributes::Extension]).value)) +
                std::hash<uint64_t>{}(std::get<std::uint64_t>((atr[Attributes::Size]).value));
    }
};

struct FileManagerV2::TEqual {
    bool operator()(const spIFile &file1, const spIFile &file2) const {
        assert(file1 != nullptr);
        assert(file2 != nullptr);
        THash th; return th.operator()(file1) == th.operator()(file2);
    }
};

// extending FileManager::Search
auto FileManagerV2::SearchOr(std::vector<SearchBase> vsearch) -> std::vector<spIFile> {
    std::vector<spIFile> ret;
    if(vsearch.empty()) return ret;
    
    std::unordered_set<std::shared_ptr<IFile>, THash, TEqual> unique_entries; // store NO duplicates
    for (auto &iter : vsearch) {
        auto files = Search(iter);
        for(auto file : files) {
            unique_entries.emplace(file);
        }
    }
    
    for (auto &iter : unique_entries) ret.emplace_back(iter);
    
    return ret;
}

// extending FileManager::Search
auto FileManagerV2::SearchAnd(std::vector<SearchBase> vsearch) -> std::vector<spIFile> {
    std::vector<spIFile> ret;
    if(vsearch.empty()) return ret;
    
    auto iter = vsearch.begin();
    std::vector<std::shared_ptr<IFile>> entries1 = Search(*iter); // get first set of Files following 1st search criteria
    for (++iter; iter != vsearch.end(); iter++) {
        ret.clear();
        auto entries2 = Search(*iter); // get N set of files following Nth search criteria
        
        for (auto &file1 : entries1)
            for (auto &file2 : entries2)
                if(file1 == file2) ret.emplace_back(file1); // iterate over each list and check for commons
                
        entries1 = std::vector<std::shared_ptr<IFile>>(ret);
    }
    
    return ret;
}
