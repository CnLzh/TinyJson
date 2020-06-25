#ifndef TINYJSON_H__
#define TINYJSON_H__

/*

Purpose:	TinyJson
Author:		CnLzh
Date:		2020/6/22


*/

/*---------- ----------*/

#include<string>

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
		JSON_PARSE_ROOT_NOT_SINGULAR	//һ��ֵ��հ׺����ַ�
	};

	/*----------Json�ڵ�----------*/

	class JsonNode
	{
	public:
		//Json type
		JsonType type;
		//Json string
		std::string json;

	private:
		/*----------�ڲ�����----------*/

		//�����հ�
		void ParseWhitespace();
		//����NULL
		int ParseNull();
		//����true
		int ParseTrue();
		//����false
		int ParseFalse();
		//������������
		int ParseFactory();
		//��ȡjson
		void SubJson(const int& pos);

	public:
		/*----------�ӿں���----------*/

		//����Json�ַ���
		int Parse();
		//��ȡJson type
		JsonType GetType() const;

	public:
		/*----------���캯��----------*/

		JsonNode() = default;
		JsonNode(const std::string& str, const JsonType& type);

	};


}






#endif // !TINYJSON_H__
