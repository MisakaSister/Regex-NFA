#pragma once
#include<string>
#include<vector>
class Token
{
public:
	std::string type_name;
	std::string value;
	Token(std::string type,std::string value)
	{
		this->type_name=type;
		this->value=value;
	}
};
class UnitOfHashTable
{
public:
	Token token;
	UnitOfHashTable* next;
};



class HashTable
{
private:
	const int table_size=11;
	UnitOfHashTable* table[table_size];
public:
	HashTable(void);
	~HashTable(void);
	int hash(std::string value);
	
	void insert(Token t);
	

	UnitOfHashTable* get(std::string value);
	
};

