#pragma once

class IFile {
public:
    virtual void SetFileAttributes(std::unordered_map<Attributes, MetaValues>  attributes) = 0;
    virtual std::unordered_map<Attributes, MetaValues> GetFileAttributes() const = 0;
};

using spIFile = std::shared_ptr<IFile>;

class File : public IFile{
private:
    class PimpFile : public FileAttributes {
    public:
        PimpFile(std::unordered_map<Attributes, MetaValues> attributes)
        : FileAttributes(attributes) {} };

    std::shared_ptr<PimpFile> m_attributes;
public:
    File(std::vector<std::tuple<Attributes, FileMetaType>> attributes);
    virtual auto SetFileAttributes(std::unordered_map<Attributes, MetaValues>  attributes) -> void override;
    virtual auto GetFileAttributes() const -> std::unordered_map<Attributes, MetaValues> override;
};
