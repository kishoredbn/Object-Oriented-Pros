#include <gtest/gtest.h>
#include "../xmlexpression.h"

// Test Fixtures: Evaluated before every Unit Test
class XmlExpressionFixtures : public ::testing::Test {
private:
    XmlExpressionHandler xml_exp_obj;

public:
    XmlExpressionFixtures() {
        // initialization members goes here
    }

    void SetUp() {
        // code here will execute just before the test is triggered 
        xml_exp_obj.Reset();
    }

    void TearDown() {
        // code here will execute just after the test is triggered 
    }

    // proxy call to XmlExpressionHandler::ParseLine()
    bool ParseLine(const std::string input) {
        return xml_exp_obj.ParseLine(input);
    }
};

// Unit-Test 1: 
TEST_F(XmlExpressionFixtures, TestParsingType1) {
    EXPECT_EQ(true, ParseLine("<year> 1977 </year>"));
}

// Unit-Test 2: 
TEST_F(XmlExpressionFixtures, TestParsingType2) {
    EXPECT_EQ(true, ParseLine("<?xml-stylesheet type = \"text/xsl\" href = \"xslplanes.2.xsl\" ?>"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}