#pragma once
#include<vector>
#include<string>
#include<map>
#include"Tokenizer.h"
class GrammerToken;

typedef std::vector<GrammerToken> production;


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
	~NontermianlNode();
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
	ASTCreater(std::string express);
	~ASTCreater();
	ASTNode* getAST(){
		return ast;
	}
private:
	void initialize();
	NontermianlNode* create_tree(std::vector<Token> token_stream);
	ASTNode* create_AST(NontermianlNode* root);
	void visit_tree(NontermianlNode* root);
private:
	ASTNode* ast;
	std::map<std::string,int> production_map;
	std::map<std::string,int> input_map;
	std::vector<production> productions;
	std::map<std::string,GrammerToken> grammer_token_map;
	static int trans_table[7][6];
};


