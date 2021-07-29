#include "ut_file_manager_ext.h"

#include "../file.h"
#include "../file_attributes.h"

#include <memory> 
#include <variant>

// Test Fixtures: Evaluated before every Unit Test
void FileManagerExtFixtures::SetUp() {
    // code here will execute just before the test is triggered 
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

    std::vector<std::shared_ptr<IFile>> vifiles;
    std::transform(vfiles.begin(), vfiles.end(), std::back_inserter(vifiles), [](auto &f){
        return std::make_shared<File>(f); // Observe : How memory transfers internally
    });
    
    file_manager = std::make_unique<FileManagerV2>();
    if(!file_manager) file_manager->AddFiles(vifiles);
}

void FileManagerExtFixtures::TearDown() {
    // code here will execute just after the test is triggered 
    file_manager = nullptr;
}

// Unit-Test 1: 
TEST_F(FileManagerExtFixtures, TestFileManagerCase1) {

    const std::string file_ext_mp3 = ".mp3";
    const std::string file_ext_mp4 = ".mp4";
    const std::string file_name_apple = "apple"; 
    const std::string file_name_nokia = "nokia"; 
    const Attributes attr_search_ext = Attributes::Extension;
    const Attributes attr_search_name = Attributes::Name;

    if(!file_manager) {
        auto vfile_search_mp3 = file_manager->SearchFiles(SearchBy(attr_search_ext, {file_ext_mp3}));
        for (auto &file : vfile_search_mp3) {
            auto attr = file->GetFileAttributes();
            EXPECT_EQ(std::get<std::string>(attr[attr_search_ext].value), file_ext_mp3);
        }
        
        auto vfile_search_mp4 = file_manager->SearchFiles(SearchBy(attr_search_ext, {file_ext_mp4}));
        for (auto &file : vfile_search_mp4) {
            auto attr = file->GetFileAttributes();
            EXPECT_EQ(std::get<std::string>(attr[attr_search_ext].value), file_ext_mp4);
        }

        auto vfile_search_apple_mp3 = file_manager->SearchOr({SearchBy{attr_search_ext, {file_ext_mp3}}, SearchBy{attr_search_name, {file_name_apple}}});
        for(auto &file : vfile_search_apple_mp3) {
            auto attr = file->GetFileAttributes(); 
            EXPECT_TRUE(file_ext_mp3.compare(std::get<std::string>(attr[attr_search_ext].value)) == 0 
                     || file_name_apple.compare(std::get<std::string>(attr[attr_search_name].value)) == 0);
        }

        auto vfile_search_nokia_mp3 = file_manager->SearchAnd({SearchBy(attr_search_ext, {file_ext_mp3}), SearchBy(attr_search_name, {file_name_nokia})});
        for (auto &file : vfile_search_nokia_mp3){
            auto attr = file->GetFileAttributes();
            EXPECT_TRUE(file_ext_mp3.compare(std::get<std::string>(attr[attr_search_ext].value)) == 0 
                     && file_name_apple.compare(std::get<std::string>(attr[attr_search_name].value)) == 0);
        }
        
    }

}
