#include "BusLine.h"

BusLine::BusLine()
{
}

//���캯����ʼ��������Ϣ 
BusLine::BusLine(string n,string t,vector<string> s){
	name=n;
	timezone=t;
	stops=s;
}

BusLine::~BusLine()
{
}


//�ж��Ƿ���ĳ��վ�� 
bool BusLine::hasStop(string stop){
	
	for (int i=0;i<stops.size();i++)
		if (stop==stops[i]) return true;
	return false;
}



//վ����Ϣ��ӡ 
void BusLine::print(){
	int t=0;
	cout<<name<<"\t"<<timezone<<"\t"<<stops.size()<<endl;
	for (int i=0;i<stops.size();i++)
		if (i!=stops.size()-1) {
			cout<<stops[i]<<"--";
			t++;
			if (t % 8==0) cout<<endl;
		}
		else cout<<stops[i]<<endl;
	cout<<endl; 
	return;
}

//��ȡ��·���� 
string BusLine::getname(){
	return name;
}

//��ȡ��·����վ̨��Ϣ 
vector<string> BusLine::getstops(){
	return stops;
}


//��ӡ��վ̨a��վ̨b��·�� 
int BusLine::zone_print(string a,string b){
	int i=0;
	int j=0;
	while (stops[i]!=a && i<stops.size()) i++;
	while (stops[j]!=b && j<stops.size()) j++;
	if (i>j){
		for (int k=i;k>=j;k--)
		if (k!=j) cout<<stops[k]<<"-->";
		else cout<<stops[k]<<endl;
	}
	else{
		for (int k=i;k<=j;k++)
		if (k!=j) cout<<stops[k]<<"-->";
		else cout<<stops[k]<<endl;
	}
	return abs(i-j);
}
