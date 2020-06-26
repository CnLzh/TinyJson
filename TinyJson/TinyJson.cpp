#include"TinyJson.h"

#include<iterator>
#include<sstream>
#include<regex>
#include<sstream>

using namespace tjson;

/*----------�ڲ�����----------*/

void JsonNode::ParseWhitespace()
{
	if (this->json.empty())
		return;

	const char* p = this->json.c_str();
	while (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
		p++;
	this->json = p;
}

void JsonNode::SubJson(const int& pos)
{
	if (this->json.size() == pos)
		this->json = "";
	else
		this->json = std::move(this->json.substr(pos + 1));
}

int JsonNode::ParseLiteral(const std::string& str, const JsonType& type)
{
	if (this->json.compare(0, str.size(), str))
		return JSON_PARSE_INVALID_VALUE;
	this->SubJson(str.size());
	this->type = type;
	return JSON_PARSE_OK;
}

int JsonNode::ParseFactory()
{
	if (this->json.empty())
		return JSON_PARSE_EXPECT_VALUE;

	switch (*this->json.begin())
	{
	case 'n':	return ParseLiteral("null", JsonType::JSON_NULL);
	case 't':	return ParseLiteral("true", JsonType::JSON_TRUE);
	case 'f':	return ParseLiteral("false", JsonType::JSON_FALSE);
	default:	return ParseNumber();
	}
}

int JsonNode::ParseNumber()
{
	std::regex reg("-?(\\d+|\\d+\\.\\d+)((E|e)[+-]?\\d+)?\\s*");
	if (!std::regex_match(this->json, reg))
		return JSON_PARSE_INVALID_VALUE;

	std::stringstream sstr(this->json);
	sstr >> this->number;

	if (errno == ERANGE || this->number == HUGE_VAL || this->number == -HUGE_VAL)
		return JSON_PARSE_NUMBER_TOO_BIG;

	this->json = "";
	this->type = JsonType::JSON_NUMBER;
	return JSON_PARSE_OK;
}

/*----------�ӿں���----------*/

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

double JsonNode::GetNumber() const
{
	return this->number;
}

/*----------���캯��----------*/

JsonNode::JsonNode(const std::string& str, const JsonType& type)
	:json(str), type(type), number(0.0)
{

}
