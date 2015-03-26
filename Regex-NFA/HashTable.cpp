#include "HashTable.h"


HashTable::HashTable(void)
{
	
}


HashTable::~HashTable(void)
{
}

int HashTable::hash(std::string value)
{
	unsigned int hashval=0;
	for(auto it : value)
	{
		hashval=(hashval<<5)+it;
	}
		
	return hashval%table_size;
}

void HashTable::insert(Token t)
{
	UnitOfHashTable* pos=get(t.value);
		if(pos==NULL)
		{
			auto new_cell=new UnitOfHashTable;
			auto L=table[hash(t.value)];
			new_cell->next=L->next;
			new_cell->token=t;
			L->next=new_cell;
		}			
}

UnitOfHashTable* HashTable::get(std::string value)
{
		int index=hash(value);
		UnitOfHashTable *pos=table[index];
		while(pos!=NULL&&pos->token.value!=value)
		{
			pos=pos->next;
		}
		return pos;
}
