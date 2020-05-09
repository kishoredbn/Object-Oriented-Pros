#pragma once

// extending FileManager to implememnt Search OR and AND
class FileManagerV2 : public FileManager {
private:
    struct THash;
    struct TEqual;
    
public:
    virtual auto SearchOr(std::vector<SearchBase> vsearch) -> std::vector<spIFile>;
    virtual auto SearchAnd(std::vector<SearchBase> vsearch) -> std::vector<spIFile>;
};
