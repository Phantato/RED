#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef vector<vector<int>> matGraph;

int main()
{
	string filename, reg, RPN;
	matGraph map;
	std::vector<char> SignStack, ;
	bool flag=FALSE;
	cin>>filename;
	ifstream fin(filename);
	fin>>reg;
	cout<<reg;
	for (string::iterator i = reg.begin(); i != reg.end(); ++i)
	{
		
		if(*i == '(')
		{
			if(flag)
			{
				while(SignStack.back() == '*'):
				{
					RPN.push_back(SignStack.back());
					SignStack.pop_back();
				}
				SignStack.push_back('.');
			}
			flag = FALSE;
			SignStack.push_back('(');
		}
		else if(*i == ')')
		{
			if(!flag)
			{
				SignStack.pop_back();
			}
			while(SignStack.back() != '(')
			{
				RPN.push_back(SignStack.back());
				SignStack.pop_back();
			}
			SignStack.pop_back();
		}
		else if(*i == '|')
		{
			while(SignStack.back() != '|' and SignStack.back() != '(')
			{
				RPN.push_back(SignStack.back());
				SignStack.pop_back();
			}
			SignStack.push_back('|');
			flag = FALSE;
		}
		else if(*i == '*')
		{
			SignStack.push_back('*');
			flag = TRUE;
		}
		else
		{
			if(flag)
			{
				while SignStack.back() == '*':
				{
					RPN.push_back(SignStack.back());
					SignStack.pop_back();
				}
				SignStack.push_back('.');
			}
			RPN.push_back(*i);
			flag = TRUE;
		}
	}
	cout<<RPN;
	return 0;
}