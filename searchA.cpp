#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<cmath>
#include<algorithm>
#include<windows.system.h>
using namespace std;

int maze[5][15] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
bool flag[5][15]={
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
struct node{
	
	int x;
	int y;
	int Gspense;
	int Hspense;
	node* fa;
	node(int tx = 0, int ty = 0, int g = 0, int h = 0) :x(tx), y(ty), Gspense(g), Hspense(h){};
	node(node* f=NULL,int tx = 0, int ty = 0, int g = 0, int h = 0) :fa(f),x(tx), y(ty), Gspense(g), Hspense(h){};
};

	list<node*> sl;
	list<node*> cl;
	bool findans = 0;
	node enode(NULL,2,12,0,0);
void add_neighbor(node* cur){//cur 就是当前父节点,父节点是已经加入关闭列表中的点
	
	int x = cur->x;
	int y = cur->y;
	int h = 0;
	node* tmp;

	if (x - 1 >= 0)
	{
		if (y - 1 >= 0 && maze[x - 1][y - 1] != 3 && flag[x - 1][y - 1] == 0)
		{
			h = abs(enode.x - x+1) * 10 + abs(enode.y - y+1) * 10;
			tmp = new node( x - 1, y - 1, cur->Gspense + 14, h);
			tmp->fa = cur;
			sl.push_back(tmp); flag[x - 1][y - 1] = 1;
		}
		if (maze[x - 1][y] != 3 && flag[x - 1][y] == 0)
		{
			h = abs(enode.x - x + 1) * 10 + abs(enode.y - y) * 10;
			tmp = new node(x - 1, y, cur->Gspense + 10, h);
			tmp->fa = cur;
			sl.push_back(tmp); flag[x - 1][y] = 1;
		}
		if (y + 1 < 15 && maze[x - 1][y + 1] != 3 && flag[x - 1][y + 1] == 0)
		{
			h = abs(enode.x - x + 1) * 10 + abs(enode.y - y - 1) * 10;
			tmp = new node(x - 1, y + 1, cur->Gspense + 14, h);
			tmp->fa = cur;
			sl.push_back(tmp); flag[x - 1][y + 1] = 1;
		}
	}

	if (x + 1 < 5)
	{
		if (y - 1 >= 0 && maze[x + 1][y - 1] != 3 && flag[x + 1][y - 1] == 0)
		{
			h = abs(enode.x - x - 1) * 10 + abs(enode.y - y + 1) * 10;
			tmp = new node(x + 1, y - 1, cur->Gspense + 14, h);
			tmp->fa = cur;
			sl.push_back(tmp); flag[x + 1][y - 1] = 1;
		}
		if (maze[x + 1][y] != 3 && flag[x + 1][y] == 0)
		{
			h = abs(enode.x - x - 1) * 10 + abs(enode.y - y) * 10;
			tmp = new node(x + 1, y, cur->Gspense + 10, h);
			tmp->fa = cur;
			sl.push_back(tmp); flag[x + 1][y] = 1;
		}
		if (y + 1 < 15 && maze[x + 1][y + 1] != 3 && flag[x + 1][y + 1] == 0)
		{
			h = abs(enode.x - x - 1) * 10 + abs(enode.y - y - 1) * 10;
			tmp = new node(x + 1, y + 1, cur->Gspense + 14, h);
			tmp->fa = cur;
			sl.push_back(tmp); flag[x + 1][y + 1] = 1;
		}
	}

	if (y - 1 >= 0 && maze[x][y - 1] != 3 && flag[x][y - 1] == 0)
	{
		h = abs(enode.x - x) * 10 + abs(enode.y - y + 1) * 10;
		tmp = new node(x, y - 1, cur->Gspense + 10, h);
		tmp->fa = cur;
		sl.push_back(tmp); flag[x][y - 1] = 1;
	}
	if (y + 1 < 15 && maze[x][y + 1] != 3 && flag[x][y + 1] == 0)
	{
		h = abs(enode.x - x) * 10 + abs(enode.y - y - 1) * 10;
		tmp = new node(x, y + 1, cur->Gspense + 10, h);
		tmp->fa = cur;
		sl.push_back(tmp); flag[x][y + 1] = 1;
	}
}
//F=G+H
node* evaluate()
{
	list<node*>::iterator mark; list<node*>::iterator it;
	int min = 99999;
	for ( it = sl.begin(); it != sl.end(); it++)
	{
		if ((*it)->Gspense + (*it)->Hspense < min)
		{
			min = (*it)->Gspense + (*it)->Hspense;
			mark = it;
		}
	}


	node* tmp = new node((*mark)->x, (*mark)->y, (*mark)->Gspense, (*mark)->Hspense );
	if ((*mark)->fa != NULL)
		tmp->fa = (*mark);
	cl.push_back(*mark);
	if (mark == sl.begin())
	{
		sl.erase(mark); mark = sl.begin();
	}
	else
	{
		mark = sl.erase(mark); mark--;
	}
	if (tmp->x == enode.x&& tmp->y == enode.y)
		findans = 1;
	return tmp;
}
//cur 为父节点
//对于已存在与开启列表中的相邻节点进行比较查看是否需要更新
void update(node* cur)
{
	list<node*>::iterator it = sl.begin();
	for (it; it != sl.end(); it++)
	{
		if (cur->x - 1 == (*it)->x&&cur->y - 1 == (*it)->y)
		if (cur->Gspense + 14 < (*it)->Gspense)
			{
			(*it)->Gspense = cur->Gspense + 14;
			(*it)->fa = cur;
			}

		if (cur->x - 1 == (*it)->x&&cur->y == (*it)->y)
		if (cur->Gspense + 10 < (*it)->Gspense)
			{
			(*it)->Gspense = cur->Gspense + 10;
			(*it)->fa = cur;
			}

		if (cur->x - 1 == (*it)->x&&cur->y + 1 == (*it)->y)
		if (cur->Gspense + 14 < (*it)->Gspense)
			{
			(*it)->Gspense = cur->Gspense + 14;
			(*it)->fa = cur;
			}

		if (cur->x == (*it)->x&&cur->y - 1 == (*it)->y)
		if (cur->Gspense + 14 < (*it)->Gspense)
			{
			(*it)->Gspense = cur->Gspense + 10;
			(*it)->fa = cur;
			}

		if (cur->x == (*it)->x&&cur->y + 1 == (*it)->y)
		if (cur->Gspense + 14 < (*it)->Gspense)
			{
			(*it)->Gspense = cur->Gspense + 10;
			(*it)->fa = cur;
			}

		if (cur->x + 1 == (*it)->x&&cur->y - 1 == (*it)->y)
		if (cur->Gspense + 14 < (*it)->Gspense)
			{
			(*it)->Gspense = cur->Gspense + 14;
			(*it)->fa = cur;
			}

		if (cur->x + 1 == (*it)->x&&cur->y == (*it)->y)
		if (cur->Gspense + 14 < (*it)->Gspense)
			{
			(*it)->Gspense = cur->Gspense + 10;
			(*it)->fa = cur;
			}

		if (cur->x + 1 == (*it)->x&&cur->y + 1 == (*it)->y)
			if (cur->Gspense + 14 < (*it)->Gspense)
			{
				(*it)->Gspense = cur->Gspense + 14;
				(*it)->fa = cur;
			}
	}
}
int main()
{
	node* tmp=new node( 2, 2, 0, 0);
	sl.push_back(tmp);
	while (!findans)
	{
		add_neighbor(tmp);
		tmp=evaluate();//找到最小值加入进关闭列表
		update(tmp);
	}
	list<node*> ans;
	list<node*>::reverse_iterator it1 = cl.rbegin();
	list<node*>::reverse_iterator it2 = cl.rbegin();
	ans.push_back(*it1);
	//cout << "(" << (*it1)->x << "," << (*it1)->y << ")\n";
	//find path
	while (!((*it1)->x == 2 && (*it1)->y == 2))
	{
		for (it2; it2 != cl.rend(); it2++)
		{
			if ((*it1)->fa->x == (*it2)->x && (*it1)->fa->y == (*it2)->y)
			{
				ans.push_back(*it2);
				//cout << "(" << (*it2)->x << "," << (*it2)->y << ")\n";
				it1 = it2;
			}
		}
	}
	
	for (it1 = ans.rbegin(); it1 != ans.rend();it1++)
		cout << "(" << (*it1)->x << "," << (*it1)->y << ")\n";
	system("pause");
	return 0;
}