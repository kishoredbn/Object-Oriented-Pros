#include "common.h"
#include "file_manager_ext.h"

// extending FileManager::Search
auto FileManagerV2::SearchOr(std::vector<std::tuple<SearchBase, FileMetaType>> vsearch) -> std::vector<File> {
    std::vector<File> ret;
    if(vsearch.empty()) return ret;
    
    std::unordered_set<File, THash, TEqual> unique_entries; // store NO duplicates
    for (auto &iter : vsearch) {
        auto files = Search(std::get<0>(iter), std::get<1>(iter));
        for(auto file : files) {
            unique_entries.emplace(file);
        }
    }
    
    for (auto &iter : unique_entries) ret.emplace_back(iter);
    
    return ret;
}

// extending FileManager::Search
auto FileManagerV2::SearchAnd(std::vector<std::tuple<SearchBase, FileMetaType>> vsearch) -> std::vector<File> {
    std::vector<File> ret;
    if(vsearch.empty()) return ret;
    
    auto iter = vsearch.begin();
    std::vector<File> entries1 = Search(std::get<0>(*iter), std::get<1>(*iter)); // get first set of Files following 1st search criteria
    for (++iter; iter != vsearch.end(); iter++) {
        ret.clear();
        auto entries2= Search(std::get<0>(*iter), std::get<1>(*iter)); // get N set of files following Nth search criteria
        
        for (auto &file1 : entries1) {
            for (auto &file2 : entries2) {
                if(file1 == file2) ret.emplace_back(file1); // iterate over each list and check for commons
            }
        }
        
        entries1 = std::vector<File>(ret);
    }
    
    return ret;
}
