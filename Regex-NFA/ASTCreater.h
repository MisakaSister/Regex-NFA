#pragma once
#include<vector>
#include<string>
#include<map>
#include"Tokenizer.h"


class ASTNode
{
public:
	ASTNode(std::string op,ASTNode* left,ASTNode* right);
	ASTNode();
	~ASTNode();
	std::string op;
	ASTNode* left_child;
	ASTNode* right_child;

};

class NontermianlNode
{
public:
	ASTNode* inh;
	ASTNode* syn;
	ASTNode* node;
	int num;
	std::vector<NontermianlNode*>child;
};


class GrammerToken
{
public:
	std::string type;
	std::string value;
	GrammerToken();
	GrammerToken(std::string type,std::string value)
	{
		this->type=type;
		this->value=value;
	}

};





class ASTCreater
{
public:
	static void initialize();
	static NontermianlNode* create_tree(std::vector<Token> token_stream);
	static ASTNode* create_AST(NontermianlNode* root);
	static void visit_tree(NontermianlNode* root);
};


