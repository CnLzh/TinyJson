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


int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
	return 0;
}