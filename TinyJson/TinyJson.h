#ifndef TINYJSON_H__
#define TINYJSON_H__

/*

Purpose:	TinyJson
Author:		CnLzh
Date:		2020/6/22


*/

/*---------- ----------*/

#include<string>
#include<variant>
#include<sstream>
#include<regex>

namespace tjson
{
	/*----------Json基础类型----------*/

	enum class JsonType
	{
		JSON_NULL,		//null
		JSON_FALSE,		//false
		JSON_TRUE,		//true
		JSON_NUMBER,	//number
		JSON_STRING,	//string
		JSON_ARRAY,		//array
		JSON_OBJECT,	//object
		JSON_TEST		//测试类型
	};

	/*----------返回值类型----------*/

	enum
	{
		JSON_PARSE_OK = 0,
		JSON_PARSE_EXPECT_VALUE,		//只有空白值
		JSON_PARSE_INVALID_VALUE,		//不是字面值
		JSON_PARSE_ROOT_NOT_SINGULAR,	//一个值后空白后还有字符
		JSON_PARSE_NUMBER_TOO_BIG,		//number超过表示范围
		JSON_PARSE_MISS_QUOTATION_MARK	//字符串后没有引号
	};


	/*----------Json节点----------*/

	class JsonNode
	{
	public:
		//Json type
		JsonType type;
		//Json string
		std::string json;
		//Json variant 
		std::variant<double, std::string> var;


	private:
		/*----------内部函数----------*/

		//分析空白
		void ParseWhitespace();
		//分析字面值
		int ParseLiteral(const std::string& str, const JsonType& type);
		//分析工厂函数
		int ParseFactory();
		//截取json
		void SubJson(const size_t& pos);
		//分析Number
		int ParseNumber();
		//分析string
		int ParseString();
		//设置string
		void SetString(std::string& str);

	public:
		/*----------接口函数----------*/

		//解析Json字符串
		int Parse();
		//获取Json type
		JsonType GetType() const;
		//获取Json number
		double GetNumber() const;


	public:
		/*----------构造函数----------*/

		JsonNode() = default;
		JsonNode(const std::string& str, const JsonType& type);

	};



}

#endif // !TINYJSON_H__
