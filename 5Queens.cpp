#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
const int num = 5; //�ʺ����
int x[num + 1] = { 0 };//�洢��(�ʺ��λ�ã�
int sum = 0;//�洢��ĸ���

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
//�жϽ��Ƿ����
bool place(int k)
{
    for (int j = 1; j < k; j++)
        if (abs(x[k] - x[j]) == abs(k - j) || x[j] == x[k])
            return false;
    return true;

}
//�жϽ��Ƿ����
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
    if (t > num) //numΪ�ʺ����Ŀ
    {
        sum++;//sumΪ���еĿ��еĽ�
        for (int m = 1; m <= num; m++)
        {
            cout << x[m];//��һ����������ݹ鵽Ҷ�ڵ��ʱ��һ�����н�
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
    //cout << "����" << sum << "�ַ���" << endl;
    return 0;
}
