#pragma once
#include<string>
#include<vector>
class Token
{
public:
	std::string type;
	std::string value;
	Token(std::string type,std::string value)
	{
		this->type=type;
		this->value=value;
	}

};

class Tokenizer
{
public:
	Tokenizer(void);
	
	Tokenizer(std::string input_stream);
	~Tokenizer(void);

	std::vector<Token> m_tokens;
private:
	std::string m_input_stream;
	
};

