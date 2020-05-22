#pragma once

class IFileManager {
public:
    virtual auto AddFiles(std::vector<spIFile> vifiles) -> void = 0;
    virtual auto Search(SearchBase search_base) -> std::vector<spIFile> = 0;
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
    virtual auto Search(SearchBase search_base) -> std::vector<spIFile> override;
};
