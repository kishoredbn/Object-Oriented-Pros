#pragma once

// extending FileManager to implememnt Search OR and AND
class FileManagerV2 : public FileManager {
private:
    struct THash;
    struct TEqual;
    
public:
    virtual auto SearchOr(std::vector<std::tuple<SearchBase, FileMetaType>> vsearch) -> std::vector<spIFile>;
    virtual auto SearchAnd(std::vector<std::tuple<SearchBase, FileMetaType>> vsearch) -> std::vector<spIFile>;
};
