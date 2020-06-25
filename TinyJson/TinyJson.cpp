#include"TinyJson.h"

#include<iterator>

using namespace tjson;

void JsonNode::ParseWhitespace()
{
	if (this->json.empty())
		return;

	const char* p = this->json.c_str();
	while (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
		p++;
	this->json = p;
}

int JsonNode::ParseNull()
{
	if (this->json.compare(0, 4, "null"))
		return JSON_PARSE_INVALID_VALUE;
	this->SubJson(4);
	this->type = JsonType::JSON_NULL;
	return JSON_PARSE_OK;
}

int JsonNode::ParseTrue()
{
	if (this->json.compare(0, 4, "true"))
		return JSON_PARSE_INVALID_VALUE;
	this->SubJson(4);
	this->type = JsonType::JSON_TRUE;
	return JSON_PARSE_OK;
}

int JsonNode::ParseFalse()
{
	if (this->json.compare(0, 5, "false"))
		return JSON_PARSE_INVALID_VALUE;
	this->SubJson(5);
	this->type = JsonType::JSON_FALSE;
	return JSON_PARSE_OK;
}

int JsonNode::ParseFactory()
{
	if (this->json.empty())
		return JSON_PARSE_EXPECT_VALUE;

	switch (*this->json.begin())
	{
	case 'n':	return ParseNull();
	case 't': return ParseTrue();
	case 'f': return ParseFalse();
	default:	return JSON_PARSE_INVALID_VALUE;
	}
}

void JsonNode::SubJson(const int& pos)
{
	if (this->json.size() == pos)
		this->json = "";
	else
		this->json = std::move(this->json.substr(pos + 1));
}

int JsonNode::Parse()
{
	this->ParseWhitespace();
	int ret = ParseFactory();
	if (ret == JSON_PARSE_OK)
	{
		this->ParseWhitespace();
		if (!this->json.empty())
			ret = JSON_PARSE_ROOT_NOT_SINGULAR;
	}
	return ret;
}

JsonType JsonNode::GetType() const
{
	return this->type;
}

JsonNode::JsonNode(const std::string& str, const JsonType& type)
	:json(str), type(type)
{

}
