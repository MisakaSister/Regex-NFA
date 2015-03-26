#pragma once
#include<string>
#include<vector>
#include"ASTCreater.h"

class NFA_Node
{
public:
	NFA_Node(char grade)
	{
		this->grade=grade;
	}
	NFA_Node();
	~NFA_Node();

	char grade;
	int state_num;
	NFA_Node* next;

};




class Sub_NFA
{
public:
	NFA_Node* start;
	NFA_Node* finish;
	Sub_NFA();
	~Sub_NFA();
	Sub_NFA(NFA_Node* start,NFA_Node* finish)
	{
		this->start=start;
		this->finish=finish;
	}

};



class NFA_Graphics
{
public:
	NFA_Graphics(void);
	~NFA_Graphics(void);
	void create_NFA(ASTNode* ast);
private:
	Sub_NFA* link_NFA(ASTNode* root,Sub_NFA* left,Sub_NFA* right);
	void add_edge(NFA_Node* node_from,NFA_Node* node_to,char grade);
	NFA_Node* add_node();
	Sub_NFA* visit(ASTNode* root);
private:
	std::vector<NFA_Node*> node_list;
	Sub_NFA NFA;
	int cur_num;
};

