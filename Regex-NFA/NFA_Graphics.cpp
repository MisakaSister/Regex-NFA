#include "NFA_Graphics.h"
NFA_Node::NFA_Node()
{
	
}

NFA_Node::~NFA_Node()
{
}
Sub_NFA::Sub_NFA()
{

}

Sub_NFA::~Sub_NFA()
{

}

NFA_Graphics::NFA_Graphics(void)
{
	cur_num=0;
}


NFA_Graphics::~NFA_Graphics(void)
{
}

void NFA_Graphics::add_edge(NFA_Node* node_from,NFA_Node* node_to,char grade)
{
	auto node=new NFA_Node;

	node->state_num=node_to->state_num;
	node->grade=grade;
	node->next=NULL;

	auto cur_node=node_from;

	while (cur_node->next!=NULL)
	{
		cur_node=cur_node->next;
	}

	cur_node->next=node;

}

NFA_Node* NFA_Graphics::add_node()
{
	auto node=new NFA_Node();
	node_list.push_back(node);
	node->state_num=cur_num++;

	return node;
}


Sub_NFA* NFA_Graphics::link_NFA(ASTNode* root,Sub_NFA* left,Sub_NFA* right)
{
	if(root->op=="*")
	{
		//'^'在此代表epsilon
		
		add_edge(left->finish,left->start,'^');

		auto node_in=add_node();
		auto node_out=add_node();

		add_edge(node_in,left->start,'^');
		add_edge(node_in,node_out,'^');
		add_edge(left->finish,node_out,'^');

		return new Sub_NFA(node_in,node_out);
	}
	
	if(root->op=="+")
	{
		add_edge(left->finish,right->start,'^');
		return new Sub_NFA(left->start,right->finish);
	}

	if(root->op=="|")
	{
		auto node_in=add_node();
		auto node_out=add_node();

		add_edge(node_in,left->start,'^');
		add_edge(node_in,right->start,'^');
		add_edge(left->finish,node_out,'^');
		add_edge(right->finish,node_out,'^');

		return new Sub_NFA(node_in,node_out);
	}

	//基础规则（叶节点）：epsilon或常规字符
	
		auto node_in=add_node();
		auto node_out=add_node();

		add_edge(node_in,node_out,root->op.at(0));

		return new Sub_NFA(node_in,node_out);
	
}

void NFA_Graphics::create_NFA(ASTNode* ast)
{
	auto t=visit(ast);
}

Sub_NFA* NFA_Graphics::visit(ASTNode* root)
{
	if(root==NULL)
	{
		return NULL;
	}

	auto left=visit(root->left_child);
	auto right=visit(root->right_child);

	return link_NFA(root,left,right);
	
}
