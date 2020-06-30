#include<gtest/gtest.h>

#include"TinyJson.h"
using namespace tjson;

TEST(TES_TPARSE_NULL, TEST_GET_NULL)
{
	JsonNode node("null", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_OK);
	EXPECT_EQ(node.GetType(), JsonType::JSON_NULL);
}

TEST(TEST_PARSE_EXPECT_VALUE1, TEST_PARSE_GET_EXPECT_VALUE1)
{
	JsonNode node("", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_EXPECT_VALUE);
	EXPECT_EQ(node.GetType(), JsonType::JSON_TEST);
}

TEST(TEST_PARSE_EXPECT_VALUE2, TEST_PARSE_GET_EXPECT_VALUE2)
{
	JsonNode node(" ", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_EXPECT_VALUE);
	EXPECT_EQ(node.GetType(), JsonType::JSON_TEST);
}

TEST(TEST_PARSE_INVALID_VALUE1, TEST_PARSE_GET_INVALID_VALUE1)
{
	JsonNode node("nul", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_INVALID_VALUE);
	EXPECT_EQ(node.GetType(), JsonType::JSON_TEST);
}

TEST(TEST_PARSE_INVALID_VALUE2, TEST_PARSE_GET_INVALID_VALUE2)
{
	JsonNode node("???", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_INVALID_VALUE);
	EXPECT_EQ(node.GetType(), JsonType::JSON_TEST);
}

TEST(TEST_PARSE_ROOT_NOT_SINGULAR, TEST_PARSE_GET_ROOT_NOT_SINGULAR)
{
	JsonNode node("null ab c", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_ROOT_NOT_SINGULAR);
	EXPECT_EQ(node.GetType(), JsonType::JSON_NULL);
}

TEST(TES_TPARSE_TRUE, TEST_GET_TRUE)
{
	JsonNode node("true", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_OK);
	EXPECT_EQ(node.GetType(), JsonType::JSON_TRUE);
}

TEST(TES_TPARSE_FALSE, TEST_GET_FALSE)
{
	JsonNode node("false", JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_OK);
	EXPECT_EQ(node.GetType(), JsonType::JSON_FALSE);
}

inline void TestNumber(const double& number, const std::string& json)
{
	JsonNode node(json, JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), JSON_PARSE_OK);
	EXPECT_EQ(node.GetType(), JsonType::JSON_NUMBER);
	EXPECT_EQ(node.GetNumber(), number);
}

inline void TestErrorNumber(const int& return_type, const std::string& json)
{
	JsonNode node(json, JsonType::JSON_TEST);
	EXPECT_EQ(node.Parse(), return_type);
	EXPECT_EQ(node.GetType(), JsonType::JSON_TEST);
}

TEST(TEST_PARSE_NUMBER, TEST_GET_NUMBER)
{
	TestNumber(0.0, "0");
	TestNumber(0.0, "-0");
	TestNumber(0.0, "-0.0");
	TestNumber(1.0, "1");
	TestNumber(-1.0, "-1");
	TestNumber(1.5, "1.5");
	TestNumber(-1.5, "-1.5");
	TestNumber(3.1416, "3.1416");
	TestNumber(1E10, "1E10");
	TestNumber(1e10, "1e10");
	TestNumber(1E+10, "1E+10");
	TestNumber(1E-10, "1E-10");
	TestNumber(-1E10, "-1E10");
	TestNumber(-1e10, "-1e10");
	TestNumber(-1E+10, "-1E+10");
	TestNumber(-1E-10, "-1E-10");
	TestNumber(1.234E+10, "1.234E+10");
	TestNumber(1.234E-10, "1.234E-10");
	TestNumber(0.0, "1e-10000");
	//边界测试
	TestNumber(1.0000000000000002, "1.0000000000000002");
	TestNumber(4.9406564584124654e-324, "4.9406564584124654e-324");
	TestNumber(-4.9406564584124654e-324, "-4.9406564584124654e-324");
	TestNumber(2.2250738585072009e-308, "2.2250738585072009e-308");
	TestNumber(-2.2250738585072009e-308, "-2.2250738585072009e-308");
	TestNumber(2.2250738585072014e-308, "2.2250738585072014e-308");
	TestNumber(-2.2250738585072014e-308, "-2.2250738585072014e-308");
	TestNumber(1.7976931348623157e+308, "1.7976931348623157e+308");
	TestNumber(-1.7976931348623157e+308, "-1.7976931348623157e+308");

}

TEST(TEST_PARSE_ERROR_NUMBER, TEST_GET_ERROR_NUMBER)
{
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, "+0");
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, "+1");
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, ".123");
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, "1.");
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, "INF");
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, "inf");
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, "NAN");
	TestErrorNumber(JSON_PARSE_INVALID_VALUE, "nan");
}

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
	return 0;
}



