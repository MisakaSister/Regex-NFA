#include "Regex.h"


Regex::Regex(std::string express)
{
	auto astCreater=new ASTCreater(express);
	auto ast=astCreater->getAST();
	nfa=new NFA_Graphics;
	nfa->create_NFA(ast);
	already_on.resize(nfa->size());
	delete ast;
	
}


Regex::~Regex(void)
{
	delete nfa;
}

void Regex::compile(std::string express)
{
	
	
	
	
}


bool Regex:: match(std::string str)
{
	for(int i=0;i<nfa->size();i++)
		already_on[i]=false;
	int s0=nfa->start_state;
	add_state(s0);
	while (!new_states.empty())
		{
			int s=new_states.top();
			new_states.pop();
			old_states.push(s);
			already_on[s]=false;
		}
	for(auto c:str)
	{
		while (!old_states.empty())
		{
			int s=old_states.top();
			std::vector<int> mov;
			nfa->move(s,c,mov);
			for(auto t:mov)
			{
				if(!already_on[t])
					add_state(t);
			}
			old_states.pop();
		}
		while (!new_states.empty())
		{
			int s=new_states.top();
			new_states.pop();
			old_states.push(s);
			already_on[s]=false;
		}
	}
	while(!old_states.empty())
	{
		int t=old_states.top();
		if(t==nfa->finish_state)
			return true;
		old_states.pop();
	}
	return false;


}

void Regex::add_state(int s)
{
	new_states.push(s);
	already_on[s]=true;
	std::vector<int> mov;
	nfa->move(s,'^',mov);
	for(auto it:mov)
	{
		if(!already_on[it])
		{
			add_state(it);
		}
	}

}
