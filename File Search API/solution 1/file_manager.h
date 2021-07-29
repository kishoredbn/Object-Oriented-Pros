#pragma once

#include "file.h"
#include "file_attributes.h"

#include <vector>

class IFileManager {
public:
    virtual auto AddFiles(std::vector<spIFile> vifiles) -> void = 0;
    virtual auto SearchFiles(SearchBase search_base) -> std::vector<spIFile> = 0;
    virtual ~IFileManager(){}
};

using spIFileManager = std::shared_ptr<IFileManager>;

class FileManager : public IFileManager {
private:
    struct PimpFileManager;
    std::shared_ptr<PimpFileManager> m_attributes;

public:
    FileManager();
    virtual auto AddFiles(std::vector<spIFile> vifiles) -> void override;
    virtual auto SearchFiles(SearchBase search_base) -> std::vector<spIFile> override;
};
