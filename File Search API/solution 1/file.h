#pragma once

#include "file_attributes.h"

class IFile {
    virtual void SetFileAttributes(std::shared_ptr<FileAttributes> attributes) = 0;
    virtual std::shared_ptr<FileAttributes> GetFileAttributes() const = 0;
};

class File : public IFile{
private:
    class PimpFile : public FileAttributes {
    public:
        PimpFile(std::string Name, std::string Extension, uint64_t Size)
        : FileAttributes(Name, Extension, Size) {} };
    std::shared_ptr<PimpFile> m_attributes;
public:
    File(std::string Name, std::string Extension=".txt", uint64_t Size=0);
    virtual void SetFileAttributes(std::shared_ptr<FileAttributes> attributes) override;
    virtual std::shared_ptr<FileAttributes> GetFileAttributes() const override;
};
