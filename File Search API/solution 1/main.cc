#include <iostream>

#include "common.h"

using Atr = Attributes;

void Display(const std::vector<File> &files)
{
    if(files.empty()) std::cout<<"None\n";
    else
    for(auto &iter : files)
    {
        auto attr = iter.GetFileAttributes();
        std::cout<< std::get<std::string>(attr[Atr::Name].value);
        std::cout<<std::get<std::string>(attr[Atr::Extension].value);
        std::cout<<" "<<std::get<uint64_t>(attr[Atr::Size].value)<<"\n";
    }
    std::cout<<"--\n";
}

int main()
{
    // List of files to test
    std::vector<File> files = {
                            {{{Atr::Name, {"apple"}}, {Atr::Extension, {".mp3"}}, {Atr::Size, {24}}}},
                            {{{Atr::Name, {"apple"}}, {Atr::Extension, {".log"}}, {Atr::Size, {58}}}},
                            {{{Atr::Name, {"android"}}, {Atr::Extension, {".mp3"}}, {Atr::Size, {24}}}},
                            {{{Atr::Name, {"blackberry"}}, {Atr::Extension, {".mp3"}}, {Atr::Size, {23}}}},
                            {{{Atr::Name, {"blackberry"}}, {Atr::Extension, {".mp3"}}, {Atr::Size, {25}}}},
                            {{{Atr::Name, {"apple"}}, {Atr::Extension, {".mp3"}}, {Atr::Size, {44}}}},
                            {{{Atr::Name, {"android"}}, {Atr::Extension, {".mp4"}}, {Atr::Size, {54}}}},
                            {{{Atr::Name, {"nokia"}}, {Atr::Extension, {".mp4"}}, {Atr::Size, {84}}}},
                            {{{Atr::Name, {"nokia"}}, {Atr::Extension, {".mp3"}}, {Atr::Size, {54}}}},
                            {{{Atr::Name, {"nokia"}}, {Atr::Extension, {".mp3"}}, {Atr::Size, {84}}}}
                        };

    // Simple file manager
    FileManager fm;
    fm.AddFiles(files);

    Display(fm.Search(SearchBase::Extension, {".mp3"}));
    Display(fm.Search(SearchBase::Size, {24}));
    Display(fm.Search(SearchBase::Name, {"apple"}));
    Display(fm.Search(SearchBase::Name, {"nokia"}));
    
    // File manager extension
    FileManagerV2 fm2;
    fm2.AddFiles(files);
    
    Display(fm2.Search(SearchBase::Name, {"nokia"})); // simple search
    Display(fm2.SearchOr({{SearchBase::Extension, {".mp3"}},{SearchBase::Name, {"apple"}}})); // search with OR condition
    Display(fm2.SearchOr({{SearchBase::Extension, {".mp4"}},{SearchBase::Name, {"blackberry"}}})); // search with OR condition

    Display(fm2.SearchAnd({{SearchBase::Extension, {".mp3"}},{SearchBase::Name, {"blackberry"}}})); // search with AND condition
    Display(fm2.SearchAnd({{SearchBase::Extension, {".mp3"}},{SearchBase::Name, {"nokia"}}})); // search with AND condition
    Display(fm2.SearchAnd({{SearchBase::Extension, {".log"}},{SearchBase::Name, {"apple"}}})); // search with AND condition

    return 0;
}

