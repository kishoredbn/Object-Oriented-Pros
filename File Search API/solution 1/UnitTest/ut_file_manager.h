#include "../file_manager.h"

#include <gtest/gtest.h>

class FileManagerFixtures : public ::testing::Test {
protected:
    std::unique_ptr<IFileManager> file_manager;
public:
    void SetUp();
    void TearDown();
};