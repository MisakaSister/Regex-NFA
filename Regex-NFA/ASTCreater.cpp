#include "ASTCreater.h"
#include<stack>
#include<iostream>
#include"Tokenizer.h"


int ASTCreater::trans_table[7][6]={
	1,0,0,1,0,0,
	0,0,2,0,3,3,
	4,0,0,4,0,0,
	5,0,6,5,6,6,
	7,0,0,7,0,0,
	9,8,9,9,9,9,
	10,0,0,11,0,0
	
};
ASTNode::ASTNode(std::string op,ASTNode* left,ASTNode* right)
{
	this->op=op;
	left_child=left;
	right_child=right;
}
ASTNode::ASTNode()
{

}


ASTNode::~ASTNode()
{
	delete left_child;
	delete right_child;
}
NontermianlNode::~NontermianlNode()
{
	for(auto it:child)
	{
		delete it;
	}

}



ASTCreater::ASTCreater(std::string express)
{
	initialize();
	Tokenizer* tokenizer=new Tokenizer(express);
	NontermianlNode* root=create_tree(tokenizer->m_tokens);
	ast=create_AST(root);
	delete tokenizer;
	delete root;
}
ASTCreater::~ASTCreater()
{

}



void ASTCreater::initialize()
{
	productions.resize(12);

	production_map.insert(std::pair<std::string,int>(std::string("or"),0));
	production_map.insert(std::pair<std::string,int>(std::string("or_"),1));
	production_map.insert(std::pair<std::string,int>(std::string("connect"),2));
	production_map.insert(std::pair<std::string,int>(std::string("connect_"),3));
	production_map.insert(std::pair<std::string,int>(std::string("repeat"),4));
	production_map.insert(std::pair<std::string,int>(std::string("repeat_"),5));
	production_map.insert(std::pair<std::string,int>(std::string("factor"),6));

	input_map.insert(std::pair<std::string,int>(std::string("char"),0));
	input_map.insert(std::pair<std::string,int>(std::string("*"),1));
	input_map.insert(std::pair<std::string,int>(std::string("|"),2));
	input_map.insert(std::pair<std::string,int>(std::string("("),3));
	input_map.insert(std::pair<std::string,int>(std::string(")"),4));
	input_map.insert(std::pair<std::string,int>(std::string("$"),5));
	
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("or",GrammerToken("nonterminal","or")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("or_",GrammerToken("nonterminal","or_")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("connect",GrammerToken("nonterminal","connect")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("connect_",GrammerToken("nonterminal","connect_")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("repeat",GrammerToken("nonterminal","repeat")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("repeat_",GrammerToken("nonterminal","repeat_")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("factor",GrammerToken("nonterminal","factor")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("char",GrammerToken("terminal","char")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("*",GrammerToken("terminal","*")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("|",GrammerToken("terminal","|")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("(",GrammerToken("terminal","(")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>(")",GrammerToken("terminal",")")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("$",GrammerToken("terminal","$")));
	grammer_token_map.insert(std::pair<std::string,GrammerToken>("epsilon",GrammerToken("epsilon","epsilon")));

	productions.at(1).push_back(grammer_token_map.at("connect"));
	productions.at(1).push_back(grammer_token_map.at("or_"));
	productions.at(2).push_back(grammer_token_map.at("|"));
	productions.at(2).push_back(grammer_token_map.at("connect"));
	productions.at(2).push_back(grammer_token_map.at("or_"));

	productions.at(3).push_back(grammer_token_map.at("epsilon"));

	productions.at(4).push_back(grammer_token_map.at("repeat"));
	productions.at(4).push_back(grammer_token_map.at("connect_"));

	productions.at(5).push_back(grammer_token_map.at("repeat"));
	productions.at(5).push_back(grammer_token_map.at("connect_"));

	productions.at(6).push_back(grammer_token_map.at("epsilon"));

	productions.at(7).push_back(grammer_token_map.at("factor"));
	productions.at(7).push_back(grammer_token_map.at("repeat_"));

	productions.at(8).push_back(grammer_token_map.at("*"));
	productions.at(8).push_back(grammer_token_map.at("repeat_"));

	productions.at(9).push_back(grammer_token_map.at("epsilon"));

	productions.at(10).push_back(grammer_token_map.at("char"));

	productions.at(11).push_back(grammer_token_map.at("("));
	productions.at(11).push_back(grammer_token_map.at("or"));
	productions.at(11).push_back(grammer_token_map.at(")"));
	
	
	
}


NontermianlNode* ASTCreater:: create_tree(std::vector<Token> token_stream)
{
	std::vector<Token>::iterator ip;
	std::stack<GrammerToken> Stack;
	std::stack<NontermianlNode*> NodeStack;

	ip=token_stream.begin();
	Stack.push(GrammerToken("terminal","$"));
	Stack.push(grammer_token_map.at("or"));
	NodeStack.push(NULL);
	NodeStack.push(new NontermianlNode);

	GrammerToken x=Stack.top();
	NontermianlNode* cur_node=NodeStack.top();
	NontermianlNode* root=cur_node;


	while(x.value!="$")
	{
		if(x.type=="terminal")
		{
			if(x.value==ip->type)
			{
				Stack.pop();
				NodeStack.pop();
				cur_node->node=new ASTNode(ip->value,NULL,NULL);
				ip++;
			}
			else return NULL;
		}
		else if(x.type=="nonterminal")
		{
			int product=trans_table[production_map.at(x.value)][input_map.at(ip->type)];
			if(product!=0)
			{
				//std::cout<<x.value<<":";
				//for(auto it:productions.at(product))
				//{
				//	std::cout<<it.value<<" ";
				//}
				//std::cout<<std::endl;

				Stack.pop();
				NodeStack.pop();
				cur_node->num=product;
				
			
				for(auto it=productions.at(product).rbegin();it!=productions.at(product).rend();++it)
				{
					NontermianlNode* node=new NontermianlNode;
					cur_node->child.insert(cur_node->child.begin(),node);

					if(it->type=="epsilon")
					{ }
					else {
						Stack.push(*it);
						NodeStack.push(node);
					}
				}
			}
			else return NULL;
		}
		x=Stack.top();
		cur_node=NodeStack.top();
	}
	return root;
}

ASTNode* ASTCreater::create_AST(NontermianlNode* root)
{
	visit_tree(root);
	return root->node;
}

void ASTCreater::visit_tree(NontermianlNode* root)
{
	switch(root->num)
	{
	case 1:
		visit_tree(root->child.at(0));
		root->child.at(1)->inh=root->child.at(0)->node;
		visit_tree(root->child.at(1));
		root->node=root->child.at(1)->syn;
		break;
	case 2:
		visit_tree(root->child.at(1));
		root->child.at(2)->inh=new ASTNode("|",root->inh,root->child.at(1)->node);
		visit_tree(root->child.at(2));
		root->syn=root->child.at(2)->syn;
		break;
	case 3:
		root->syn=root->inh;
		break;
	case 4:
		visit_tree(root->child.at(0));
		root->child.at(1)->inh=root->child.at(0)->node;
		visit_tree(root->child.at(1));
		root->node=root->child.at(1)->syn;
		break;
	case 5:
		visit_tree(root->child.at(0));
		root->child.at(1)->inh=new ASTNode("+",root->inh,root->child.at(0)->node);
		visit_tree(root->child.at(1));
		root->syn=root->child.at(1)->syn;
		break;
	case 6:
		root->syn=root->inh;
		break;
	case 7:
		visit_tree(root->child.at(0));
		root->child.at(1)->inh=root->child.at(0)->node;
		visit_tree(root->child.at(1));
		root->node=root->child.at(1)->syn;
		break;
	case 8:
		root->child.at(1)->inh=new ASTNode("*",root->inh,NULL);
		visit_tree(root->child.at(1));
		root->syn=root->child.at(1)->syn;
		break;
	case 9:
		root->syn=root->inh;
		break;
	case 10:
		root->node=root->child.at(0)->node;
		break;
	case 11:
		visit_tree(root->child.at(1));
		root->node=root->child.at(1)->node;
		break;
	default:
		break;
	}
}
