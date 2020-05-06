#include <string>

#include "file_attributes.h"
#include "file.h"

File::File(std::string Name, std::string Extension, uint64_t Size)
: m_attributes(std::make_shared<PimpFile>(Name, Extension, Size)) {}

void File::SetFileAttributes(std::shared_ptr<FileAttributes> attributes) {
    if(m_attributes) m_attributes = std::dynamic_pointer_cast<PimpFile>(attributes);
    else if(attributes)
        m_attributes = std::make_shared<PimpFile>(attributes->Name, attributes->Extension, attributes->Size);
}

std::shared_ptr<FileAttributes> File::GetFileAttributes() const {
    std::shared_ptr<FileAttributes> ret = nullptr;
    if(m_attributes) ret = m_attributes;
    return ret;
}

