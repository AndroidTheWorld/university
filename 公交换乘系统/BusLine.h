#ifndef BUSLINE_H
#define BUSLINE_H
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>


using namespace std;

class BusLine
{
	public:
		BusLine();
		//���캯����ʼ���������� 
		BusLine(string n,string t,vector<string> s); 
		~BusLine();
		//վ̨��Ϣ��ӡ���� 
		void print();
		//�жϸ���·���Ƿ���ĳ��վ̨stop 
		bool hasStop(string stop);
		//��ȡ��·���� 
		string getname();
		//��ȡ��·������վ̨��Ϣ 
		vector<string> getstops();
		//��ӡ��վ̨a ��b��·�� 
		int zone_print(string a,string b);
	private:
		string name;		//�洢��·��Ϣ 
		string timezone;	//�洢��·����ʱ�� 
		vector<string> stops;	//�洢վ̨��Ϣ 
		
};

#endif
