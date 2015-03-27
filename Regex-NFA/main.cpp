#include"ASTCreater.h"
#include"Tokenizer.h"
#include"NFA_Graphics.h"
#include"Regex.h"
#include<iostream>
int main()
{
	Regex* re=new Regex;
	re->compile("(0|1|2)*@qq.com$");
	std::cout<<re->match("012211@qq.com")<<std::endl;
	std::cout<<re->match("abaaaaaaababbbaaaabb")<<std::endl;
	std::cout<<re->match("cailin")<<std::endl;
	system("pause");
	return 0;

}
