#pragma once

#include "file_attributes.h"

#include <tuple>
#include <vector>
#include <unordered_map>

class IFile {
public:
    virtual void SetFileAttributes(std::unordered_map<Attributes, MetaValues>  attributes) = 0;
    virtual std::unordered_map<Attributes, MetaValues> GetFileAttributes() const = 0;
    virtual ~IFile(){}
};

using spIFile = std::shared_ptr<IFile>;

class File : public IFile{
private:
    struct PimpFile;
    std::shared_ptr<PimpFile> m_attributes;
public:
    File(std::vector<std::tuple<Attributes, FileMetaType>> attributes);
    virtual auto SetFileAttributes(std::unordered_map<Attributes, MetaValues>  attributes) -> void override;
    virtual auto GetFileAttributes() const -> std::unordered_map<Attributes, MetaValues> override;
};
