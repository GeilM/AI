#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
const int num = 5; //皇后个数
int x[num + 1] = { 0 };//存储解(皇后的位置）
int sum = 0;//存储解的个数

void print(vector< vector<int> > t)
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<t[i].size();j++)
		{
			cout<<t[i][j]<<" ";
		}
		cout<<endl;
	}
}
//判断解是否可行
bool place(int k)
{
    for (int j = 1; j < k; j++)
        if (abs(x[k] - x[j]) == abs(k - j) || x[j] == x[k])
            return false;
    return true;

}
//判断解是否可行
vector<vector<int> > fc(int k,vector<vector<int> > domain)
{
//	int j=1;	
	//cout<<"fc\n";
   for(int  i=k;i<5;i++)
   {
   		vector<int>::iterator it=domain[i].begin();
   	//	j=1;
	   for(it;it!=domain[i].end();)
	   {
	   		if(abs(x[k]-*it) == abs(k-(i+1)) || x[k]==*it)
	   			{
	   				//cout<<"delete\n" ;
	   				it=domain[i].erase(it);	 
	   				it=domain[i].begin();
	   			}
   			else
   				it++;
   				
	   }
	   if(domain[i].empty())
	   {
	   		//cout<<"empty\n";
	   		domain.clear();
	   		return domain;
	   	}
	}
	//cout<<"keep search\n";
	return domain;
}

void backtrack(int t,vector<vector<int> > domain)
{
    if (t > num) //num为皇后的数目
    {
        sum++;//sum为所有的可行的解
        for (int m = 1; m <= num; m++)
        {
            cout << x[m];//这一行用输出当递归到叶节点的时候，一个可行解
        }
        cout << endl;
    }
    else
        for (int i = 1; i <= num; i++)
        {
            x[t] = i;
            if (place(t))
            {
            	vector<vector<int> > d=fc(t,domain);
            	if(d.empty())
            	{
            		vector<int>::iterator it=domain[t-1].begin();
            		for(it;it!=domain[t-1].end();)
            		{
            			if(*it == i)
            			{
            				domain[t-1].erase(it);break;
            			}
            			it++;
            		}
            	}
            	else
            		backtrack(t + 1,d);
            }
                       
		}
}

int main()
{
	vector<vector<int> > domain(5);
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			domain[i].push_back(j+1);
		}
	}
    for (int i = 0; i <= num; i++)
        x[i] = 0;
    backtrack(1,domain);
    //cout << "共有" << sum << "种方案" << endl;
    return 0;
}
