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
	/*----------Json��������----------*/

	enum class JsonType
	{
		JSON_NULL,		//null
		JSON_FALSE,		//false
		JSON_TRUE,		//true
		JSON_NUMBER,	//number
		JSON_STRING,	//string
		JSON_ARRAY,		//array
		JSON_OBJECT,	//object
		JSON_TEST		//��������
	};

	/*----------����ֵ����----------*/

	enum
	{
		JSON_PARSE_OK = 0,
		JSON_PARSE_EXPECT_VALUE,		//ֻ�пհ�ֵ
		JSON_PARSE_INVALID_VALUE,		//��������ֵ
		JSON_PARSE_ROOT_NOT_SINGULAR,	//һ��ֵ��հ׺����ַ�
		JSON_PARSE_NUMBER_TOO_BIG,		//number������ʾ��Χ
		JSON_PARSE_MISS_QUOTATION_MARK	//�ַ�����û������
	};


	/*----------Json�ڵ�----------*/

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
		/*----------�ڲ�����----------*/

		//�����հ�
		void ParseWhitespace();
		//��������ֵ
		int ParseLiteral(const std::string& str, const JsonType& type);
		//������������
		int ParseFactory();
		//��ȡjson
		void SubJson(const size_t& pos);
		//����Number
		int ParseNumber();
		//����string
		int ParseString();
		//����string
		void SetString(std::string& str);

	public:
		/*----------�ӿں���----------*/

		//����Json�ַ���
		int Parse();
		//��ȡJson type
		JsonType GetType() const;
		//��ȡJson number
		double GetNumber() const;


	public:
		/*----------���캯��----------*/

		JsonNode() = default;
		JsonNode(const std::string& str, const JsonType& type);

	};



}

#endif // !TINYJSON_H__
