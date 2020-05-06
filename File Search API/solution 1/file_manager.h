#pragma once

struct PimpFileManager;

using SearchBase = Attributes;

class FileManager {
private:
    std::shared_ptr<PimpFileManager> m_attributes;

public:
    FileManager();
    virtual auto AddFiles(std::vector<File> &vfiles) -> void final;
    virtual auto Search(SearchBase search_base, FileMetaType search_value) -> std::vector<File>;
};
