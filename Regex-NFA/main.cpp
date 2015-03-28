#include"Regex.h"
#include<iostream>

int main()
{

	Regex* re=new Regex("(a|b|c|d)(0|1|2|3|4|5|6|7|8|9|a|b|c|d)*@qq.com$");
	
	std::string str;
	while (std::cin>>str)
	{
		if(re->match(str))
			std::cout<<"yes"<<std::endl;
		else
			std::cout<<"no"<<std::endl;		
	}
	delete re;
	system("pause");
	return 0;

}
