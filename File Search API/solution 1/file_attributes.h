#pragma once

struct FileAttributes {
    std::string Name;
    std::string Extension;
    uint64_t Size;
    FileAttributes(std::string Name, std::string Extension=".txt", uint64_t Size=0)
    : Name(Name),
    Extension(Extension),
    Size(Size) {}
    virtual ~FileAttributes() {}
};
