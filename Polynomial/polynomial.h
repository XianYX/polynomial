#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct Var          //����
{
	string v;     //��������
	int exp;        //ָ��
}var;

bool cmp(var a, var b)
{
	return a.v.compare(b.v) < 0 ? 1 : 0;
}

class Polynomial;
class Term
{
	friend Polynomial;
public: 
	int coef;      //ϵ��
	vector <var> varArray;     //��������
	int varnums;       //������Ŀ
	Term();
	Term(const Term & t);
	~Term();
	//bool cmp(var a, var b);
	bool eval(string& v,int x);
	void NewVar(string v, int exp);
	bool AllExpIsZero();
	
};

Term::Term()
{
	this->coef = 1;
	this->varnums = 0;
	this->varArray;
}

Term::Term(const Term & b)
{
	this->coef = b.coef;
	this->varnums = b.varnums;
	for (int i = 0; i < b.varnums; i++)
	{
		NewVar(b.varArray[i].v, b.varArray[i].exp);
	}
}

Term::~Term()
{
	varArray.clear();
}



bool Term::eval(string& v,int x)
{
	int result = 1;
	for (int i = 0; i < varnums; i++)
	{
		if (this->varArray[i].v == v)
		{
			for (int j = 0; j < this->varArray[i].exp; j++)
			{
				result *= x;
			}
			this->varArray[i].exp = 0;
			this->coef *= result;
			return 1;
		}
	}
	return 0;
}

void Term::NewVar(string v, int exp)
{
	if (varArray.empty())
	{
		var *temp;
		temp = new var;
		temp->v = v;
		temp->exp = exp;
		this->varnums++;
		this->varArray.push_back(*temp);
		sort(this->varArray.begin(), this->varArray.end(), cmp);
		return;
	}
	else
	{
		for (int i = 0; i < this->varnums; i++)
		{
			if (this->varArray[i].v == v)
			{
				this->varArray[i].exp += exp;
				return;
			}
		}
		var *temp;
		temp = new var;
		temp->v = v;
		temp->exp = exp;
		this->varnums++;
		this->varArray.push_back(*temp);
		sort(this->varArray.begin(), this->varArray.end(), cmp);
		return;
	}
	
}

bool Term::AllExpIsZero()
{
	bool flag = 1;
	for (int i = 0; i < this->varnums; i++)
	{
		if (this->varArray[i].exp != 0)
		{
			flag = flag & 0;
		}
	}
	return flag;
}

class Polynomial
{
	friend Term;
public:
	Polynomial();
	Polynomial(const Polynomial & b);
	~Polynomial();
	//bool cmp(var a, var b);
	bool match(Term &a, Term & b);
	void NewTerm( Term & term);
	void eval(string v,int x);   //������ֵ
	void display();
	void derivative(string& v);
private:
	Term *termArray;   //����ϵ��������
	int capacity;      //��������С
	int terms;         //����ϵ��������

};

Polynomial::Polynomial()
{
	this->terms = 0;
	this->capacity = 10;
	termArray = new Term[this->capacity];
}

Polynomial::Polynomial(const Polynomial &b)
{
	this->terms = 0;
	this->capacity = b.capacity;
	termArray = new Term[this->capacity];
	for (int i = 0; i < b.terms; i++)
	{
		NewTerm(b.termArray[i]);
	}
}

Polynomial::~Polynomial()
{
	delete[] termArray;
}

bool Polynomial::match(Term & a, Term & b)     //ƥ�䵥��ʽ
{
	sort(a.varArray.begin(), a.varArray.end(), cmp);
	sort(b.varArray.begin(), b.varArray.end(), cmp);
	if (a.varnums != b.varnums)
		return 0;
	else
	{
		for (int j = 0; j < a.varnums; j++)
		{
			if (a.varArray[j].v != b.varArray[j].v)   //�Ƚϱ�����
				return 0;
			else if (a.varArray[j].exp != b.varArray[j].exp)     //�Ƚ϶�Ӧָ��
				return 0;
			else
				continue;
		}
		return 1;
	}
}
void Polynomial::NewTerm( Term & term)
{
	if (this->terms == 0)
	{
		this->terms++;
		this->termArray[0] = term;
		return;
	}
	else
	{
		int i;
		for (i = 0; i < this->terms; i++)
		{
			if (match(this->termArray[i], term))     //ƥ��ɹ�
			{
				this->termArray[i].coef += term.coef;
				return;
			}
		}
		this->terms++;                    //ƥ��ʧ�ܣ���ʾ��ӵĵ���ʽΪ�µĵ���ʽ
		this->termArray[i] = term;
		return;
	}        

}

void Polynomial::eval(string v, int x)
{
	bool flag = 0;
	for (int i = 0; i < this->terms; i++)
	{
		flag=(flag | this->termArray[i].eval(v, x));
	}
	if (flag == 0)
		cout << "Error, no variable" << endl;
}

void Polynomial::derivative(string& v)
{
	bool flag1 = 0;
	for (int i = 0; i < this->terms; i++)
	{
		bool flag2 = 0;
		for (int j = 0; j < this->termArray[i].varnums; j++)
		{
			if (this->termArray[i].varArray[j].v == v)
			{
				flag1 = (flag1 & 1);
				flag2 = (flag2 & 1);
				if (this->termArray[i].varArray[j].exp >= 1)
				{
					this->termArray[i].coef *= this->termArray[i].varArray[j].exp;
					this->termArray[i].varArray[j].exp--;
					break;
				}
			}
		}
		if(flag2 == 0)
			this->termArray[i].coef = 0;     //������������
	}
	if (flag1 == 0)
	{
		cout << "�ñ��������ڣ�" << endl;
		return;
	}
	else
	{
		this->display();
		return;
	}
}

void Polynomial::display()
{
	string out;
	for (int i = 0; i < terms; i++)
	{
		if (termArray[i].coef == 0)     //�������
			continue;
		else if (termArray[i].coef < 0)
			out += '-';
		else
			out += '+';
		if (termArray[i].coef != 1 && termArray[i].coef != -1)       //����ϵ��
		{
			stringstream ss;                
			ss << abs(termArray[i].coef);
			out += ss.str();
		}
		else if (termArray[i].coef == 1)
		{
			bool z = termArray[i].AllExpIsZero();
			if (z)
				out += '1';
		}
		else if (termArray[i].coef == -1)
		{
			bool z = termArray[i].AllExpIsZero();
			if (z)
				out += "-1";
		}
		for (int j = 0; j < termArray[i].varnums; j++)
		{
			if (termArray[i].varArray[j].exp == 0)
				continue;
			else
			{
				out += termArray[i].varArray[j].v;
				if (termArray[i].varArray[j].exp != 1)
				{
					out += '^';
					stringstream ss;
					ss << termArray[i].varArray[j].exp;
					out += ss.str();
				}
				out += '*';
			}
		}
		if (out[out.size() - 1] == '*')
			out.erase(out.size() - 1, 1);
	}
	if(out[0]=='+')
		out.erase(0, 1);
	cout << out << endl << endl;
}

