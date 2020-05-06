#pragma once

// extending FileManager to implememnt Search OR and AND
class FileManagerV2 : public FileManager {
private:
    struct THash {
    size_t operator()(const File &file) const {
            auto atr = file.GetFileAttributes();
            return std::hash<std::string>{}(std::get<std::string>((atr[Attributes::Name]).value)) +
                   std::hash<std::string>{}(std::get<std::string>((atr[Attributes::Extension]).value)) +
                   std::hash<uint64_t>{}(std::get<std::uint64_t>((atr[Attributes::Size]).value));
        }
    };
    struct TEqual {
        bool operator()(const File &file1, const File &file2) const {
            THash th; return th.operator()(file1) == th.operator()(file2);
        }
    };
    
public:
    virtual auto SearchOr(std::vector<std::tuple<SearchBase, FileMetaType>> vsearch) -> std::vector<File>;
    virtual auto SearchAnd(std::vector<std::tuple<SearchBase, FileMetaType>> vsearch) -> std::vector<File>;
};
