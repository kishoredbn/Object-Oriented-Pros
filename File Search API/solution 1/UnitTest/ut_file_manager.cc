#include "../file.h"
#include "../file_manager.h"
#include "../file_attributes.h"

#include <gtest/gtest.h>

#include <memory> 
#include <variant>

// Test Fixtures: Evaluated before every Unit Test
class FileManagerFixtures : public ::testing::Test {
protected:
    std::unique_ptr<FileManager> file_manager;

public:
    void SetUp() {
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
        
        file_manager = std::make_unique<FileManager>();
        if(!file_manager) file_manager->AddFiles(vifiles);
    }

    void TearDown() {
        // code here will execute just after the test is triggered 
        file_manager = nullptr;
    }

};

// Unit-Test 1: 
TEST_F(FileManagerFixtures, TestFileManagerCase1) {

    const std::string file_ext_mp3 = ".mp3";
    const std::string file_ext_mp4 = ".mp4";
    const Attributes attr_search = Attributes::Extension;

    if(!file_manager) {
        auto vfile_search_mp3 = file_manager->SearchFiles(SearchBy(attr_search, {file_ext_mp3}));
        for (auto &file : vfile_search_mp3) {
            auto attr = file->GetFileAttributes();
            EXPECT_EQ(std::get<std::string>(attr[attr_search].value), file_ext_mp3.c_str());
        }
        
        auto vfile_search_mp4 = file_manager->SearchFiles(SearchBy(attr_search, {file_ext_mp4}));
        for (auto &file : vfile_search_mp4) {
            auto attr = file->GetFileAttributes();
            EXPECT_EQ(std::get<std::string>(attr[attr_search].value), file_ext_mp4.c_str());
        }
    }

}

// main() trigger
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}