#pragma once
#include<string>
#include"NFA_Graphics.h"
#include"ASTCreater.h"
#include"Tokenizer.h"
#include<stack>
#include<vector>

class Regex
{
public:
	Regex(void);
	~Regex(void);
	void compile(std::string  express);
	bool match(std::string str);
private:
	void add_state(int s);
private:
	NFA_Graphics* nfa;
	std::stack<int> old_states;
	std::stack<int> new_states;
	std::vector<bool> already_on;
};

