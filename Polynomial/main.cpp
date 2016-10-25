#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "polynomial.h"
#include "WordTag.h"

using namespace std;
int main()
{
	string pol;
	Polynomial *p = NULL;                                     //���ʽֱ�����룬ָ�������ԡ�������Ϊ��ͷ��                             
	Polynomial *temp = NULL;	
	char ii;                          //ʲô������ֱ�ӻس���ʾ�������
	ii=cin.get();
	while (ii != '\n')
	{
		if (ii == '!')
		{
			string ord;
			if (p == NULL)
			{
				temp = p;
			}	
			else
			{
				if (temp)
					temp->~Polynomial();
				temp = new Polynomial(*p);	
			}
			getline(cin, ord);
			DealOrder(ord, temp);
		}
		else
		{
			pol.clear();
			if(p)
				p->~Polynomial();
			while (ii != '\n')
			{
				if (ii != ' ')
					pol += ii;
				ii = cin.get();
			}
			p = expression(pol);
			if (p)
				p->display();		
		}
		ii = cin.get();
	}
	
	system("pause");
	return 0;
}