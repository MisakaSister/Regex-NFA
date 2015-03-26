#include"ASTCreater.h"
#include"Tokenizer.h"
#include"NFA_Graphics.h"
#include<iostream>
int main()
{
	ASTCreater::initialize();
	Tokenizer* tokenizer=new Tokenizer("ab$");
	NontermianlNode* root=ASTCreater::create_tree(tokenizer->m_tokens);
	ASTNode*  ast=ASTCreater::create_AST(root);
	auto nfa=new NFA_Graphics;
	nfa->create_NFA(ast);
	system("pause");
	return 0;

}
