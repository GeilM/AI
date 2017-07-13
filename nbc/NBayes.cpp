#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>
#include<Windows.h>
using namespace std;

map<string, vector<string> > conf;
vector<string> attributes;
vector<vector<string> > training_set;
vector<double> targets_prob;
map<pair<string, string>, double> attr_target_prob;

//属性与其熵一一对应
//读取文件信息
//读取属性以及属性取值
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
//读入训练集,局部变量
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

void calPrior()
{
	int t_pos = attributes.size() - 1;
	vector<string> target_attr = conf[attributes[t_pos]];
	vector<int> target_value(target_attr.size(),0);
	int tot_sum = 0;
	//统计目标分类的概率P(target_i)
	for (int row = 0; row < training_set.size(); row++)
	{
		for (int j = 0; j < target_attr.size(); j++)
		{
			if (training_set[row][t_pos] == target_attr[j])
			{
				target_value[j]++;
			}
		}
	}
	for (int i = 0; i < target_attr.size(); i++)
	{
		targets_prob.push_back(0);
	}
	//计算目标分类的概率P(target_i)
	for (int i = 0; i < target_attr.size(); i++)
	{
		cout << "P(" << target_attr[i] << ")=" << target_value[i] * 1.0 / training_set.size() << endl;
		targets_prob[i] = target_value[i]*1.0 / training_set.size();
	}
	//统计每个属性的
	map<pair<string, string>, int> attr_target;
	for (int row = 0; row < training_set.size(); row++)
	{
		//注意修改
		for (int col = 1; col < training_set[row].size() - 1; col++)
		{
			attr_target[make_pair(training_set[row][col], training_set[row][t_pos])]++;
		}
	}
	//计算每个属性的条件概率
	map<pair<string, string>, int>::iterator it = attr_target.begin();
	for (it; it != attr_target.end(); it++)
	{
		for (int k = 0; k < target_attr.size(); k++)
		{
			//条件概率
			if (it->first.second == target_attr[k])
			{
				cout << "P(" << it->first.first << "|" << it->first.second << ")=" << it->second*1.0 / target_value[k] << endl;
				attr_target_prob[make_pair(it->first.first, it->first.second)] = it->second*1.0 / target_value[k];
			}	
		}
	}
	return;
}
string classify(vector<string> test)
{
	//计算每个分类的概率
	int t_pos = attributes.size() - 1;
	vector<string> target_attr = conf[attributes[t_pos]];
	vector<double> prior(target_attr.size(),1);
	for (int k = 0; k < target_attr.size(); k++)
	{
		//cout <<"类别："<< target_attr[k] << endl;
		for (int t = 0; t < test.size(); t++)
		{
			pair<string, string> tmp = make_pair(test[t], target_attr[k]);
		//	cout << "P(" << test[t] << "|" << target_attr[k] << ")=" << attr_target_prob[tmp] << endl;
			prior[k] = prior[k] * attr_target_prob[tmp];
		}
		prior[k] *= targets_prob[k];
	//	cout << "其概率为：" << prior[k] << endl;
	}
	double max = -1;
	int index;
	for (int m = 0; m < prior.size(); m++){
		if (max < prior[m])
		{
			max = prior[m];
			index = m;
		}
	}
	return target_attr[index];
}
vector<vector<string> > read_validate()
{
	vector<vector<string> > validation_set;
	ifstream read_vali;
	read_vali.open("validationSet.txt");
	vector<string> tmp;
	string line;
	stringstream ss;
	string buff;
	int row = 0;

	while (getline(read_vali, line))
	{
		ss.clear();
		ss << line;
		while (ss >> buff)
		{
			tmp.push_back(buff);
		}
		if (tmp.size() != 0)
		{
			validation_set.push_back(tmp);
			tmp.clear();
		}
	}
	read_vali.close();
	return validation_set;
}
int main()
{
	input();
	read_training();
	calPrior();

	vector<vector<string> > validation_set;
	validation_set = read_validate();
	string category = "";
	for (int i = 0; i < validation_set.size(); i++)
	{
		//for (int j = 0; j < validation_set[i].size(); j++)
		//	cout << validation_set[i][j] << " ";
		//cout << endl;
		category = classify(validation_set[i]);
		cout << "第" << i+1 << "个数据的分类结果为：" << category << endl;
		category = "";
	}
	system("pause");
}