#pragma once

#include "file.h"

struct PimpFileManager;

enum class SearchBase : uint64_t {  name =      1,
                                    extension = 2,
                                    size =      4,
                                    other =     8};

class FileManager {
private:
    std::shared_ptr<PimpFileManager> m_attributes;

    std::vector<File> SearchExtension(std::string search_etn);
    std::vector<File> SearchName(std::string search_name);
    std::vector<File> SearchSize(uint64_t search_size);

public:
    FileManager();
    void AddFiles(std::vector<File> &vfiles);
    std::vector<File> Search(SearchBase search_base, std::string search_str);
};
