#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<conio.h>

#include "BusLine.h"
#include "menu.h"
using namespace std;

vector<BusLine> lines;

//�ָ��ַ�������������վ�����ݵĶ��봦�� 
vector<string> &split(const string &str, char delim, vector<string> &elems, bool skip_empty = true) {
    istringstream iss(str);
    for (string item; getline(iss, item, delim); )
        if (skip_empty && item.empty()) continue;
        else elems.push_back(item);
    return elems;
}

//���ļ��ж�ȡ��·���� 
void loadData(){
	string name;		//��·���� 
	string timezone;	//��·������ʱ�� 
	string temp;		//�ݴ�վ̨��Ϣ���ַ��� 
	char buf[1024];
	vector<string> stops;	//��temp�зָ����վ̨���ݵĴ�ŵ� 
	
	//����ļ��Ƿ���� 
	ifstream f("./lineData.txt");
	if (!f.is_open()){
		cout<<"���������ļ�������"<<endl;
		getch();
		exit(0); 
	}
	
	//��ȡ�ļ����� 
	while(!f.eof()){
		stops.clear();
		f.getline(buf,1024);
		name=string(buf);
		
		f.getline(buf,1024);
		timezone=string(buf);
		
		f.getline(buf,1024);
		temp=string(buf);
		split(temp,' ',stops);
		 
		lines.push_back(BusLine(name,timezone,stops));
		f.getline(buf,1024);
	}
	
	f.close();
	return;
}

int main(){
	
	loadData();
	
	//�����溯������ 
	while (true){
		menu::print(lines);
		menu::getchoice(lines);
	} 
	
	return 0;
}
