#include "file.h"
#include "file_manager.h"
#include "file_attributes.h"
#include "file_manager_ext.h"

#include <iostream>

template<typename T>
void Display(const std::vector<std::shared_ptr<IFile>> &files)
{
    if(files.empty()) std::cout<<"None\n";
    else
    for(auto &iter : files)
    {
        auto f = std::dynamic_pointer_cast<T>(iter);
        auto attr = f->GetFileAttributes();
        std::cout<< std::get<std::string>(attr[Atr::Name].value);
        std::cout<< std::get<std::string>(attr[Atr::Extension].value);
        std::cout<<" "<< std::get<uint64_t>(attr[Atr::Size].value)<<"\n";
    }
    std::cout<<"--\n";
}

int main()
{
    // List of files to test - container of "concrete" objects (but we want to work with abstract types)
    std::vector<File> vfiles = {
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
    
    // List of files to test - container of "abstract" type object-pointer
    // Learn: Important: How to convert container of concrete types to container of abstract types
    std::vector<std::shared_ptr<IFile>> vifiles;
    std::transform(vfiles.begin(), vfiles.end(), std::back_inserter(vifiles), [](auto &f){
        return std::make_shared<File>(f); // Observe : How memory transfers internally
    });

    // We are not using it anywhere, but just leaving it here for educational purpose
    // Learn : Important: How to convert container of abstract pointer-types to concrete type
    std::vector<File> vfiles2;
    std::transform(vifiles.begin(), vifiles.end(), std::back_inserter(vfiles2), [](auto &i){ // for educational purpose only
        const auto t = std::dynamic_pointer_cast<File>(i); // Observe : How memory transfers internally
        assert(t != nullptr);
        return *t;
    });

    // Simple file manager
    FileManager fm;
    fm.AddFiles(vifiles); // Remember : Always to work with abstract types

    Display<File>(fm.SearchFiles(SearchBy(Attributes::Extension, {".mp3"})));
    Display<File>(fm.SearchFiles(SearchBy(Attributes::Size, {24})));
    Display<File>(fm.SearchFiles(SearchBy(Attributes::Name, {"apple"})));
    Display<File>(fm.SearchFiles(SearchBy(Attributes::Name, {"nokia"})));
    
    // File manager extension
    FileManagerV2 fm2;
    fm2.AddFiles(vifiles); // Remember : Always to work with abstract types

    Display<File>(fm2.SearchFiles(SearchBy(Attributes::Name, {"nokia"}))); // simple search
    Display<File>(fm2.SearchOr({SearchBy{Attributes::Extension, {".mp3"}}, SearchBy{Attributes::Name, {"apple"}}})); // search with OR condition
    Display<File>(fm2.SearchOr({SearchBy{Attributes::Extension, {".mp4"}}, SearchBy{Attributes::Name, {"blackberry"}}})); // search with OR condition

    Display<File>(fm2.SearchAnd({SearchBy(Attributes::Extension, {".mp3"}), SearchBy(Attributes::Name, {"blackberry"})})); // search with AND condition
    Display<File>(fm2.SearchAnd({SearchBy(Attributes::Extension, {".mp3"}), SearchBy(Attributes::Name, {"nokia"})})); // search with AND condition
    Display<File>(fm2.SearchAnd({SearchBy(Attributes::Extension, {".log"}), SearchBy(Attributes::Name, {"apple"})})); // search with AND condition

    return 0;
}

