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

// Unit-Test 3: 
TEST_F(XmlExpressionFixtures, TestParsingType3) {
    EXPECT_EQ(false, ParseLine("of the world.</description>"));
}

// Unit-Test 4: 
TEST_F(XmlExpressionFixtures, TestParsingType4) {
    EXPECT_EQ(false, ParseLine("</description>of the world.</description>"));
}

// Unit-Test 5:
TEST_F(XmlExpressionFixtures, TestParsingType5) {
    EXPECT_EQ(false, ParseLine("<</description></description>"));
}

// Unit-Test 6:
TEST_F(XmlExpressionFixtures, TestParsingType6) {
    EXPECT_EQ(true, ParseLine("<description><</description>"));
}

// Unit-Test 7:
TEST_F(XmlExpressionFixtures, TestParsingType7) {
    EXPECT_EQ(false, ParseLine("</description></description>"));
}

// Unit-Test 8:
TEST_F(XmlExpressionFixtures, TestParsingType8) {
    EXPECT_EQ(false, ParseLine("of the world."));
}

// Unit-Test 9:
TEST_F(XmlExpressionFixtures, TestParsingType9) {
    EXPECT_EQ(false, ParseLine(""));
}

// Unit-Test 10:
TEST_F(XmlExpressionFixtures, TestParsingType10) {
    EXPECT_EQ(false, ParseLine("</>"));
}

// Unit-Test 11:
TEST_F(XmlExpressionFixtures, TestParsingType11) {
    EXPECT_EQ(false, ParseLine("<>"));
}

// Unit-Test 12:
TEST_F(XmlExpressionFixtures, TestParsingType12) {
    EXPECT_EQ(false, ParseLine("<"));
}

// Unit-Test 13:
TEST_F(XmlExpressionFixtures, TestParsingType13) {
    EXPECT_EQ(true, ParseLine(">"));
}

// Unit-Test 14:
TEST_F(XmlExpressionFixtures, TestParsingType14) {
    EXPECT_EQ(false, ParseLine("<??>"));
}

// main() trigger
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}