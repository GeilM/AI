#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;


struct node{
	string attribute;
	string attribute_value;
	double entropy;
	vector<node*> childs;

	node(string attr_value = "", string attr = ""){ attribute = attr; attribute_value = attr_value, childs.clear(); }
};

map<string, vector<string> > conf;
vector<string> attributes;
vector<vector<string> > training_set;
node* root;

//����������һһ��Ӧ
//��ȡ�ļ���Ϣ
//��ȡ�����Լ�����ȡֵ
void input()
{
	ifstream read_conf;
	read_conf.open("conf.txt");
	string line;
	stringstream ss;
	string buff;
	vector<string> tmp;
	while (getline(read_conf, line))
	{
		tmp.clear();
		ss.clear();
		ss << line;
		//	cout << "temp";
		while (ss >> buff)
		{
			//		cout << " " << buff;
			tmp.push_back(buff);
		}
		//	cout << endl;
		buff = tmp[0];
		tmp.erase(tmp.begin());
		conf[buff] = tmp;
	}
	read_conf.close();
}
//����ѵ����,�ֲ�����
void read_training()
{
	ifstream readTrSet;
	readTrSet.open("trainingSet.txt");

	vector<string> tmp;
	string line;
	stringstream ss;
	string buff;
	int row = 0;

	while (getline(readTrSet, line))
	{
		ss.clear();
		ss << line;
		while (ss >> buff)
		{
			if (row == 0)
			{
				attributes.push_back(buff);
			}
			else
			{
				tmp.push_back(buff);
			}
		}
		if (tmp.size() != 0)
		{
			training_set.push_back(tmp);
			tmp.clear();
		}
		row++;
	}
	readTrSet.close();
}

//����������Ե�ȡֵ�ĸ���target������ȡֵҲӦ����conf�ļ���
//������Ϣ�����������ԣ�����Ϣ����С
string getMaxAttribute(vector<vector<string> > sub_trainSet,vector<string> remain_attribute)
{

	int cnt = 0;
	int p_target = attributes.size() - 1;
	vector<string> target_values = conf[attributes[p_target]];
	double* entropy = new double[remain_attribute.size()];
	int pos;
	double min = 999;
	string chosen = "";
	//i��j��
	int n = sub_trainSet.size();
	int tot_for_attr = 0;
	//string Ϊ����ȡֵ �����Ϊ����ȡֵ����Ӧ��ͳ�����Լ���sub����Ŀ��ͳ��
	map<string, vector<int> >   map_attrvalues_num;
	for (int i = 0; i < remain_attribute.size(); i++)
	{
		pos = 0;
		while (attributes[pos] != remain_attribute[i])
			pos++;
		map_attrvalues_num.clear();
		for (int cnt = 0; cnt < conf[remain_attribute[i]].size(); cnt++)
		{
			map_attrvalues_num[conf[remain_attribute[i]][cnt]].clear();
		}

		for (int row = 0; row < sub_trainSet.size(); row++)
		{
			//map�еĳ�ʼ����0-ͳ�Ƹ÷����µ������������Ϊ�Է�������ͳ��
			if (map_attrvalues_num[sub_trainSet[row][pos]].size() == 0)
			{
				for (int cnt = 0; cnt < target_values.size() + 1; cnt++)
					map_attrvalues_num[sub_trainSet[row][pos]].push_back(0);
			}
			//��֧��������
			map_attrvalues_num[sub_trainSet[row][pos]][0]++;
			for (int cnt = 0; cnt < target_values.size(); cnt++)
			{

				if (sub_trainSet[row][p_target] == target_values[cnt])
				{
					map_attrvalues_num[sub_trainSet[row][pos]][cnt + 1]++;
					break;
				}
			}
		}
		map<string, vector<int> >::iterator it = map_attrvalues_num.begin();
		//��sub_trainset�ﵽһ������֮����Ҫ�ٽ���㣬����Ҷ��㣬���������
		//ͳ����ѵ���������ԵĲ�ͬȡֵ�ĸ���֮��������Ϣ��
		entropy[i] = 0;
		it = map_attrvalues_num.begin();
		for (it; it != map_attrvalues_num.end(); it++)
		{
			for (int cnt = 0; cnt < target_values.size(); cnt++)
			{
				if (it->second[cnt + 1] != 0)
					entropy[i] = entropy[i] + (it->second[0] * 1.0 / n)*((-1)*it->second[cnt + 1] * 1.0 / it->second[0] * log(it->second[cnt + 1] * 1.0 / it->second[0]) / log(2.0));
			}
		}

		if (min > entropy[i])
		{
			min = entropy[i];
			chosen = remain_attribute[i];
		}

	}
	//�ҵ�����С�Լ����Ӧ�����ԣ���Ϣ����Խ���ڸ���parents�������
	return chosen;
}
string checkLeaf2(vector<vector<string> > sub_trainSet)
{
	string target = attributes[attributes.size() - 1];
	int n = conf[target].size();
	vector<int> counts(n, 0);
	for (int i = 0; i < sub_trainSet.size(); i++)
	{
		for (int j = 0; j < conf[target].size(); j++)
		{
			if (sub_trainSet[i][attributes.size() - 1] == conf[target][j])
				counts[j]++;
		}
	}
	int max = 0;
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		if (max < counts[i])
		{
			max = counts[i];
			index = i;
		}
	}
	return  conf[target][index];
}
bool checkLeaf(vector<vector<string> > sub_trainSet)
{
	int p_target = attributes.size() - 1;
	vector<string> target_value = conf[attributes[p_target]];
	set<string> t_set;
	bool flag = 0;
	for (int row = 0; row < sub_trainSet.size(); row++)
	{
		t_set.insert(sub_trainSet[row][p_target]);
	}
	if (t_set.size() == 1)//ֻ��һ�ַ���
		return 1;
	else
		return 0;
}
node* formTree(node* p, vector<vector<string> > sub_trainSet,vector<string> remain_attribute)
{
	int t_pos = attributes.size() - 1;
	if (p == NULL)
		p = new node();
	if (checkLeaf(sub_trainSet))
	{
		p->attribute = sub_trainSet[0][t_pos];
		return p;
	}
	if (remain_attribute.size() == 0)
	{
		p->attribute = checkLeaf2(sub_trainSet);
		return p;
	}
	string attr = getMaxAttribute(sub_trainSet, remain_attribute);
	p->attribute = attr;
	vector<string> new_attribute;
	vector<string>::iterator it2 = remain_attribute.begin();
	for (it2; it2 != remain_attribute.end(); it2++)
	{
		if (*it2 != attr)
			new_attribute.push_back(*it2);
	}
	
	vector<string> values = conf[attr];
	vector<vector<string> > new_trainSet;
	int pos = 1;
	while (attributes[pos] != attr)
		pos++;
	for (vector<string>::iterator it3 = values.begin(); it3 != values.end(); it3++)
	{
		for (int i = 0; i < sub_trainSet.size(); i++)
		{
			if (sub_trainSet[i][pos] == *it3)
			{
				new_trainSet.push_back(sub_trainSet[i]);
			}
		}
		node* new_node = new node();
		new_node->attribute_value = *it3;
		
		formTree(new_node, new_trainSet, new_attribute);
		p->childs.push_back(new_node);
		new_trainSet.clear();
	}
	return p;

}
//Ŀ�����Բ�������ࣿ��
//ѭ������ �м���Ҫ�ı�ѵ�������Լ�����Ѿ������������,p�ǵ�ǰ��Ҫ���ֵĽ��
void PrintTree(node *p, int depth){
	for (int i = 0; i < depth; i++) cout << "\t";//����������������tab  
	if (p->attribute_value!=""){
		cout << "{"<<p->attribute_value<<"}|";
		//for (int i = 0; i < depth + 1; i++) cout << '\t';//����������������tab  
	}
	if (p->childs.size() == 0)
	{
		cout << "��" << p->attribute << "��" << endl;
		return;
	}
	cout << "["<<p->attribute<<"]" << endl;
	for (vector<node*>::iterator it = p->childs.begin(); it != p->childs.end(); it++){
		PrintTree(*it, depth + 1);
	}
}
int main()
{
	input();
	read_training();
	vector<string> remain_attribute;
	//��Ҫ����������в���ҪĿ������ 
	for (int i = 1; i < attributes.size() - 1; i++)
		remain_attribute.push_back(attributes[i]);
	root = formTree(root, training_set,remain_attribute);
	PrintTree(root, 0);
	system("pause");

}


