#include<sstream>
#include<regex>

#include"TinyJson.h"
#include"Stack.h"

namespace tjson
{

	/*----------内部函数----------*/

	void JsonNode::ParseWhitespace()
	{
		if (this->json.empty())
			return;

		const char* p = this->json.c_str();
		while (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
			p++;
		this->json = std::move(p);
	}

	void JsonNode::SubJson(const size_t& pos)
	{
		if (this->json.length() == pos)
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
		case '\"':	return ParseString();
		default:	return ParseNumber();
		}
	}

	int JsonNode::ParseNumber()
	{
		std::regex reg("-?(\\d+|\\d+\\.\\d+)((E|e)[+-]?\\d+)?\\s*");
		if (!std::regex_match(this->json, reg))
			return JSON_PARSE_INVALID_VALUE;

		std::stringstream sstr(this->json);
		sstr >> std::get<double>(this->var);

		if (std::get<double>(this->var) == HUGE_VAL || std::get<double>(this->var) == -HUGE_VAL)
			return JSON_PARSE_NUMBER_TOO_BIG;

		this->json = "";
		this->type = JsonType::JSON_NUMBER;
		return JSON_PARSE_OK;
	}
	int JsonNode::ParseString()
	{
		Stack _stack;
		for (int i = 1; i < this->json.length(); i++)
		{
			char tmp = this->json[i];
			switch (tmp)
			{
			case '\"':
				SetString(_stack.Pop<char>(i - 1), i - 1);
				this->SubJson(i);
				return JSON_PARSE_OK;
			default:
				*_stack.Push<char>() = tmp;
			}
		}
		return JSON_PARSE_MISS_QUOTATION_MARK;
	}

	void JsonNode::SetString(std::string str, const int& size)
	{

		this->var = std::move(str.substr(0, size));
		this->type = JsonType::JSON_STRING;

	}
	/*----------接口函数----------*/

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
		return std::get<double>(this->var);

	}

	std::string JsonNode::GetString() const
	{
		return std::get<std::string>(this->var);
	}


	/*----------构造函数----------*/

	JsonNode::JsonNode(const std::string& str, const JsonType& type)
		:json(str), type(type)
	{

	}
}