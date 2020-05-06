#include <iostream>
#include <vector>

#include "file_manager.h"
#include "file.h"

void Display(const std::vector<File> &files)
{
    if(files.empty()) std::cout<<"None\n";
    else
    for(auto &iter : files)
    {
        auto attr = iter.GetFileAttributes();
        std::cout<<attr->Name<<attr->Extension<<" "<<attr->Size<<"\n";
    }
    std::cout<<"--\n";
}

int main()
{
    std::vector<File> files = {{"apple", ".log", 24},
                               {"apple", ".mp3", 58},
                               {"android", ".log", 24},
                               {"blackberry", ".mp4", 450},
                               {"blackberry", ".mp3", 430},
                               {"nokia", ".mp3", 2},
                               {"nokia", ".mp4", 2},
                               {"nokia", ".mov", 2}};

    FileManager fm;
    fm.AddFiles(files);

    Display(fm.Search(SearchBase::extension, ".mp3"));
    Display(fm.Search(SearchBase::size, "24"));
    Display(fm.Search(SearchBase::name, "apple"));
    Display(fm.Search(SearchBase::name, "nokia"));

    return 0;
}
