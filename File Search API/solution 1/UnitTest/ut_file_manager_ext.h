#include "../file_manager_ext.h"

#include <gtest/gtest.h>

class FileManagerExtFixtures : public ::testing::Test {
protected:
    std::unique_ptr<FileManagerV2> file_manager;
public:
    void SetUp();
    void TearDown();
};