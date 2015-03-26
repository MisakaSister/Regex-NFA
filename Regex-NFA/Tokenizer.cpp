#include "Tokenizer.h"


Tokenizer::Tokenizer(void)
{
	
}


Tokenizer::~Tokenizer(void)
{
}

Tokenizer::Tokenizer(std::string input_stream)
{
	m_input_stream=input_stream;
	for(auto it:m_input_stream)
	{
		if(it=='*'||it=='|'||it=='('||it==')'||it=='$')
			m_tokens.push_back(Token(std::string(1,it),std::string(1,it)));
		else m_tokens.push_back(Token("char",std::string(1,it)));
	}

}

