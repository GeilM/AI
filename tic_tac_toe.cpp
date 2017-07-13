#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<windows.system.h>
using namespace std;
#define max 0x3f3f3f
#define min -100

void print(char matrix[9])
{
	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0)
			cout << endl;
		cout << matrix[i] << " ";
	}
	cout << endl << endl;
}

//player1 computer; player2 user; 0 for tie;3 for no result
int check(char matrix[9])
{
	for (int i = 0; i < 3; i++)
	{
		if (matrix[i * 3] == matrix[i * 3 + 1] && matrix[i * 3 + 1] == matrix[i * 3 + 2] && matrix[i * 3 + 2] == 'x')
			return 1;
		if (matrix[i * 3] == matrix[i * 3 + 1] && matrix[i * 3 + 1] == matrix[i * 3 + 2] && matrix[i * 3 + 2] == 'o')
			return -1;
		if (matrix[i] == matrix[i + 3] && matrix[i + 3] == matrix[i + 6] && matrix[i + 6] == 'x')
			return 1;
		if (matrix[i] == matrix[i + 3] && matrix[i + 3] == matrix[i + 6] && matrix[i + 6] == 'o')
			return -1;

	}
	if ((matrix[0] == matrix[4] && matrix[4] == matrix[8] && matrix[8] == 'x') || (matrix[2] == matrix[4] && matrix[4] == matrix[6] && matrix[6] == 'x'))
		return 1;
	else if (((matrix[0] == matrix[4] && matrix[4] == matrix[8]) || (matrix[2] == matrix[4] && matrix[4] == matrix[6])) && matrix[4] == 'o')
		return -1;
	for (int i = 0; i<9; i++)
		if (matrix[i] == '+')
			return 2;
	return 0;
}

//如果当前结点是1，则返回极大值；当前结点是-1，则返回极小值；由player决定；a表示父节点的α，b表示父节点的β;player 表示下一个
int dfs(char* matrix, int player, int a, int b,int depth)
{
	int vt;
	if (check(matrix) != 2)
	{
		return check(matrix);
	}
	for (int k = 0; k < 9; k++)
	{
		if (matrix[k] == '+')
		{
			char* tmp = new char[9];
			strcpy(tmp, matrix);
			//cout << "player :" << player;
			if (player == 1)//电脑选最大值
			{
				tmp[k] = 'x';
				 vt = dfs(tmp, -1, a, b,depth + 1);//选取最小值
				if (vt > a) //更新最大值
					a = vt;
				if (b <= a)//剪枝
				{
					break;
				}
			}
			else if (player == -1)//人，选取最小值
			{
				tmp[k] = 'o';
				 vt = dfs(tmp, 1, a, b, depth + 1);//选取最大值
				if (vt < b)//更新最小值
					b = vt;
				if (a >= b){ break; }
			}
			
		}
	}
	if (player == 1)
		return a;
	else if (player == -1)
		return b;
}

//确定要不要搜索
bool can_search(char* matrix)
{
	for (int i = 0; i < 3; i++)
	{
		if (matrix[i * 3] == matrix[i * 3 + 1] && matrix[i * 3] == 'x')
		if (matrix[i * 3 + 2] == '+')
		{
			matrix[i * 3 + 2] = 'x'; return 0;
		}
		if (matrix[i * 3 + 1] == matrix[i * 3 + 2] && matrix[i*3+1] == 'x')
		if (matrix[i * 3] == '+')
		{
			matrix[i * 3] = 'x'; return 0;
		}
		if (matrix[i * 3] == matrix[i * 3 + 2] && matrix[i*3] == 'x')
		if (matrix[i * 3 + 1] == '+')
		{
			matrix[i * 3 + 1] = 'x'; return 0;
		}
		if (matrix[i] == matrix[i + 3] && matrix[i] == 'x')
		if (matrix[i + 6] == '+')
		{
			matrix[i + 6] = 'x'; return 0;
		}
		if (matrix[i + 3] == matrix[i + 6] && matrix[i+3] == 'x')
		if (matrix[i] == '+')
		{
			matrix[i] = 'x'; return 0;
		}
		if (matrix[i] == matrix[i + 6] && matrix[i] == 'x')
		if (matrix[i + 3] == '+')
		{
			matrix[i + 3] = 'x'; return 0;
		}

	}
	if (matrix[0] == matrix[4] && matrix[0] == 'x')
	if (matrix[8] == '+')
	{
		matrix[8] = 'x'; return 0;
	}
	if (matrix[4] == matrix[8] && matrix[8] == 'x')
	if (matrix[0] == '+')
	{
		matrix[0] = 'x'; return 0;
	}
	if (matrix[8] == matrix[0] && matrix[0] == 'x')
	if (matrix[4] == '+')
	{
		matrix[4] = 'x'; return 0;
	}
	
	if (matrix[2] == matrix[4] && matrix[2] == 'x')
	 if (matrix[6] == '+')
	 {
		 matrix[6] = 'x'; return 0;
	 }
	 if (matrix[4] == matrix[6] && matrix[4] == 'x')
	 if (matrix[2] == '+')
	 {
		 matrix[2] = 'x';
		 return 0; 
	 }
	 if(matrix[2]==matrix[6]&& matrix[2] == 'x')
	 if (matrix[4] == '+')
	 {
		 matrix[4] = 'x';
		 return 0;
	 }
	 return 1;
}

int main()
{
	cout << "Hit:Please input the coordinate x ,y at each step. i.e. 2 3";
	char* m = new char[9];
	for (int i = 0; i < 9; i++)
		m[i] = '+';
	print(m);
	bool f = 0;
	int x, y;
	int a = min; int b = max;
	char* tmp = new char[9];
	int mmax;
	char* next = new char[9];
	int ans;
	while (check(m) == 2)
	{
	c:	cout << ">>";
		cin >> x >> y;
		if (m[x * 3 + y] == '+')
			m[x * 3 + y] = 'o';
		else
		{
			cout << "Error input!\n";
			goto c;
		}
		
		mmax = min;
		f = 0;
		if (!can_search(m))
		{
			print(m);
			break;
		}
		for (int i = 0; i < 9; i++)
		{
			a = min; b = max;
			if (m[i] == '+')
			{
				char* ma = new char[9];
				strcpy(ma, m);
				ma[i] = 'x';//电脑move,选极大
				ans = dfs(ma, -1, a, b,0);//选极大值
				
				if (mmax < ans)
				{
					f = 1;
					mmax = ans;
					strcpy(next, ma);
				}
			}
		}
		if (f)
			strcpy(m,next);
		print(m);
	}
	if (check(m) == 1)
		cout << "\nYou Lose!\n";
	else if (check(m) == 0)
		cout << "\nTie\n";
	else
		cout << "\nYou Win!\n";
	system("pause");
}
