#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<conio.h>
#include<set>
#include "BusLine.h"
#include "menu.h"

menu::menu()
{
}

menu::~menu()
{
}


//logo��ӡ���� 
void logo(){
	cout<<"888888b.                      .d8888b.                    888                          "<<endl;
	cout<<"888  '88b                    d88P  Y88b                   888                          "<<endl;
	cout<<"888  .88P                    Y88b.                        888                          "<<endl;
	cout<<"8888888K.  888  888 .d8888b   'Y888b.   888  888 .d8888b  888888 .d88b.  88888b.d88b.  "<<endl;
	cout<<"888  'Y88b 888  888 88K          'Y88b. 888  888 88K      888   d8P  Y8b 888 '888 '88b "<<endl;
	cout<<"888    888 888  888 'Y8888b.       '888 888  888 ;Y8888b. 888   88888888 888  888  888 "<<endl;
	cout<<"888   d88P Y88b 888      X88 Y88b  d88P Y88b 888      X88 Y88b. Y8b.     888  888  888 "<<endl;
	cout<<"8888888P\"   \"Y88888  88888P'  '8888P'   'Y88888  88888P'  'Y888 ''Y8888  888  888  888 "<<endl;
	cout<<"                                             888                                       "<<endl;
	cout<<"                                        Y8b d88P                                       "<<endl;
	cout<<"                                         'Y88P'                                        "<<endl;
	return;
}


//��·վ̨��ӡ������n���ƴ�ӡ��������·��Ĭ��0��ӡȫ����· 
void stops_print(vector<BusLine> lines,int n=0){
	if (n==0){
		for (int i=0;i<lines.size();i++) lines[i].print();
		return;
	}
	for (int i=0;i<n && i<lines.size();i++)
	lines[i].print();
	return;
} 

//��̬������ӡ�˵�ѡ����� 
void menu::print(vector<BusLine> lines){
	system("cls");
	logo();
	cout<<"======================================================================================="<<endl;
	stops_print(lines,2);
	cout<<"======================================================================================="<<endl;
	cout<<">                                                         --code by ������            <"<<endl;
	cout<<"======================================================================================="<<endl;
	cout<<"=                                1.��ѯ��·                                           ="<<endl;
	cout<<"=                                2.��ѯվ��                                           ="<<endl;
	cout<<"=                                3.���й滮                                           ="<<endl;
	cout<<"=                                4.ȫ����·                                           ="<<endl;
	cout<<"=                                0.�˳�                                               ="<<endl;
	cout<<"======================================================================================="<<endl;
	cout<<"=>Choice:";
	return;
}

//ȫ��·�ߴ�ӡ���� 
void allLinePrint(vector<BusLine> lines){
	system("cls");
	stops_print(lines,0);
	cout<<"�����������"<<endl;
	getch();
}

//��ѯ��·���� 
void inquireLine(vector<BusLine> lines){
	string name;
	cout<<"\n��������Ҫ��ѯ����·���ƣ�"; cin>>name;
	if (name.find("·")==string::npos) name=name+"·";
	for (int i=0;i<lines.size();i++){
		if (lines[i].getname()==name) {
			lines[i].print();
			cout<<"Ϊ���ҵ�������Ϣ�������������"<<endl;
			getch();
			return;
		}
	}
	cout<<"\n��Ǹδ���ҵ�����·�������������"<<endl;
	getch();
	return;
}

//��ѯվ̨���� 
void inquireStop(vector<BusLine> lines){
	string name;
	bool flag=true;
	cout<<"\n��������Ҫ��ѯ��վ�����ƣ�"; cin>>name;
	cout<<"\n��ѯ�������:"<<endl;
	
	for (int i=0;i<lines.size();i++)
		if (lines[i].hasStop(name)) {
			lines[i].print();
			flag=false;
		}
	
	if (flag) cout<<"\n��Ǹ·�߾�����վ�㣬�����������"<<endl;
	else cout<<"������·������վ�������������"<<endl;
	getch();
	return;
}

//��·�滮���������˺����� 
void routePlan(vector<BusLine> lines){
	string outset;
	string destination;
	BusLine a;
	BusLine b;
	bool flag=true;
	
	//��������յ���Ϣ 
	cout<<"\n������������㣺"; cin>>outset;
	cout<<"�����������յ㣺"; cin>>destination;
	cout<<endl;
	
	//�ж�����յ��Ƿ���� 
	for (int i=0;i<lines.size();i++)
	if (lines[i].hasStop(outset)){
		flag=false;
		a=lines[i];
		break;
	}
	
	if (flag){
		cout<<"\n��Ǹ��δ���ҵ����������ʼվ��"<<endl;
		getch();
		return;
	}
	flag=true;
	
	for (int i=0;i<lines.size();i++)
	if (lines[i].hasStop(destination)){
		flag=false;
		b=lines[i];
		break; 
	}
	
	if (flag){
		cout<<"\n��Ǹ��δ���ҵ���������յ�վ��"<<endl;
		getch();
		return; 
	}
	
	
//	·���滮ԭ��
//	�����ж�����յ��Ƿ���ͬһ�����ϣ������ֱ�������·
//	�������
//	ѡȡ��������ܹ������վ����Ϊ����A 
//	ѡȡ�յ������ܹ������վ����Ϊ����B
//	����AB�Ľ������ڣ���ô�������ǻ���վ��
	 
	//����·���滮 
	if (a.getname()==b.getname()){
		cout<<"\nΪ���滮·������"<<endl;
		cout<<"��� "<<a.getname()<<endl;
		a.zone_print(outset,destination);
		getch();
		return;
	} 
	else{
		vector<string> node;				//��Ž���Ԫ�� 
		vector<string> tempA=a.getstops();	//��ų������ܹ����������վ�� 
		vector<string> tempB=b.getstops();	//����յ��ܹ����������վ�� 
		
		//��վ����Ϣ����Ϊ�����󽻼���׼�� 
		sort(tempA.begin(),tempA.end()); 
		sort(tempB.begin(),tempB.end());
		//�󽻼� 
		set_intersection(
			tempA.begin(),
			tempA.end(),
			tempB.begin(),
			tempB.end(),
			back_inserter(node)
		);
		
		//�������Ϊ�գ�����Ϊ�����ڻ��˷�����������Ϊ�գ���ӡ���ɷ����� 
		if (node.empty()){
			cout<<"\n��Ǹ��δ���ҵ����ʵĻ���·�ߣ������������"<<endl;
			getch();
			return;
		}
		cout<<"\nΪ���ҵ�����·����ѡ��,�����������"<<endl;
		for (int i=0;i<node.size();i++){
			//cout<<node[i]<<endl;
			int x,y;

			printf("��%d��·��\n",i+1);
			cout<<"========================================================="<<endl;
			cout<<"�� "<<outset<<" ��� "<<a.getname()<<" �� "<<node[i]<<endl<<endl;
			x=a.zone_print(outset,node[i]);
			cout<<endl;
			cout<<"�� "<<node[i]<<" ���� "<<b.getname()<<" �� "<<destination<<endl<<endl; 
			y=b.zone_print(node[i],destination);
			printf("\n����%dվ·��\n\n\n",x+y); 
		}
		getch();
		return;
	}

	
}


//��ȡ�û�ѡ���Լ���ش����� 
void menu::getchoice(vector<BusLine> lines){
	string choice;
	cin>>choice;
	switch (choice[0]){
		case '1': inquireLine(lines); break;	//��·��ѯ 
		case '2': inquireStop(lines); break;	//վ̨��ѯ 
		case '3': routePlan(lines); break;		//·���滮 
		case '4': allLinePrint(lines); break;	//��ӡ������·��Ϣ 
		case '0':  exit(0);						//�˳� 
	}
	
	
}

