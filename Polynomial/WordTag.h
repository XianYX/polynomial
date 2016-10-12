#pragma once
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include "polynomial.h"

using namespace std;

vector <string> a;   //单项式
vector <int> b;      //符号

void MySplite(string s)     //拆分为单项式
{
	int pos=0;
	int i = 0;
	if (s[0] == '-')
	{
		b.push_back(-1);
		i++;
		pos++;
	}	
	else
		b.push_back(1);
	while(i<s.length())
	{
		if (s[i] == '+')
		{
			a.push_back(s.substr(pos, i - pos));
			b.push_back(1);
			i++;
			pos = i;
		}
		else if (s[i] == '-')
		{
			a.push_back(s.substr(pos, i - pos));
			b.push_back(-1);
			i++;
			pos = i;
		}
		else
			i++;
	}
	a.push_back(s.substr(pos, i - pos));   //最后一项
}

Polynomial * expression(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (isalnum(s[i]) || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '^')
			continue;
		else
		{
			cout << "错误输入" << endl;
			return NULL;
		}		
	}
	int pos,j;
	int sum;
	Polynomial* p;
	p = new Polynomial;
	a.clear();
	b.clear();
	MySplite(s);
	for (int i = 0; i < a.size(); i++)
	{
		pos = 0;
		
		Term *t;
		t = new Term;
		a[i] += '*';

		j = 0;
		while (j < a[i].length())
		{

			if (a[i][j] == '*')
			{
				int k = pos;
				while(k < j)
				{
					if ((a[i][k] >= 'a'&&a[i][k] <= 'z') || (a[i][k] >= 'A'&&a[i][k] <= 'Z'))
					{
						string v;
						int exp;
						while ((a[i][k] >= 'a'&&a[i][k] <= 'z') || (a[i][k] >= 'A'&&a[i][k] <= 'Z'))
						{
							v += a[i][k];
							k++;
						}
						if (a[i][k] == '^')
						{
							k++;
							exp = 0;
							while (a[i][k] >= '0'&&a[i][k] <= '9')
							{
								exp = exp * 10 + a[i][k] - '0';
								k++;
							}
						}
						else
						{
							exp = 1;
						}
						t->NewVar(v, exp);
					}
					if (a[i][k] >= '0'&&a[i][k] <= '9')
					{
						sum = 0;
						while (a[i][k] >= '0'&&a[i][k] <= '9')
						{
							sum = sum * 10 + a[i][k] - '0';
							k++;
						}
						t->coef *= sum;
					}
				}
				j++;
				pos = j;
			}
			else
				j++;	
		}
		t->coef *= b[i];   //符号位
		p->NewTerm(*t);
	}
	return p;
}

void DealOrder(string s, Polynomial *p)
{
	if (p == NULL)
	{
		cout << "当前表达式为空" << endl;
		return;
	}
	string m = "simplify";
	string n = "d/d";
	string v;
	if (s == m)
	{
		p->display();
		return;
	}
	else if (s.substr(0, 8) == m && s.length() > 8)
	{
		vector <string> temp;
		int pos = 8;
		int i = 8;
		s += ' ';
		while (i < s.length())
		{
			if (s[i] == ' ')
			{
				if(i > pos)
					temp.push_back(s.substr(pos, i - pos));
				i++;
				pos = i;
			}
			else
				i++;
		}
		for (i = 0; i < temp.size(); i++)
		{
			//pos = 0;
			int j = 0;
			string v;
			int e;
			while (j < temp[i].length())
			{
				if (temp[i][j] == '=')
				{
					v = temp[i].substr(0, j);
					j++;
					e = 0;
					while (temp[i][j] >= '0' && temp[i][j] <= '9')
					{
						e = e * 10 + temp[i][j] - '0';
						j++;
					}
				}
				else
					j++;
			}
			p->eval(v, e);
		}
		p->display();
	}
	else if (s.substr(0, 3) == n)
	{
		for (int i = 3; i < s.length(); i++)
		{
			if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			{
				v += s[i];
			}
			else
			{
				cout << "错误输入！" << endl;
				return;
			}
		}
		p->derivative(v);
	}
	else
	{
		cout << "错误输入！" << endl;
		return;
	}
}