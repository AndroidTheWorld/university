#include<iostream>
#include <string>
#include<fstream>
#include "banfei.h"
using namespace std;

void banfei::initdata()
{
	ifstream infile("income.txt",ios::in);//�������ļ�
	if(!infile)
	{
		cerr<<"��ȡ����,��income.txt!"<<endl;
		return;
	}
	int n=0,i=0;
	icount =0;
	while(!infile.eof())
	{	
		infile>>im[i].id;
		infile>>im[i].money;
		infile>>im[i].name;
		infile>>im[i].date;
		infile>>im[i].remark;
		//cout<<im[i].id<<" "<<im[i].money<<" "<<im[i].name<<" "<<im[i].date<<" "<<im[i].remark<<endl;
		icount++;
		i++;
	}
	
	infile.close();
	cout<<"��ȡincome.txt����!"<<endl;

	ifstream exfile("expend.txt",ios::in);//��֧���ļ�
	if(!exfile)
	{
		cerr<<"��ȡ����,��expend.txt!"<<endl;
		return;
	}
	ecount =0;
	i=0;
	while(!exfile.eof())
	{	
		exfile>>ed[i].id;
		exfile>>ed[i].money;
		exfile>>ed[i].name;
		exfile>>ed[i].date;
		exfile>>ed[i].remark;
		//cout<<ed[i].id<<" "<<ed[i].money<<" "<<ed[i].name<<" "<<ed[i].date<<" "<<ed[i].remark<<endl;
		ecount++;
		i++;
	}
	
	exfile.close();
	cout<<"��ȡexpend.txt����!"<<endl;


};

void banfei::savedata()
{
	ofstream imfile("income.txt",ios::out);
	ofstream edfile("expend.txt",ios::out);
	int n=0;
	for(n=0;n<icount;n++)
	{	
		cout<<"����ɹ�"<<endl;
		imfile<<im[n].id<<"  ";
		imfile<<im[n].money<<"  ";
		imfile<<im[n].name<<"  ";
		imfile<<im[n].date<<"  ";
		imfile<<im[n].remark;
		imfile<<endl;
	}
	imfile.close();

	for(n=0;n<ecount;n++)
	{
		edfile<<ed[n].id<<"  ";
		edfile<<ed[n].money<<"  ";
		edfile<<ed[n].name<<"  ";
		edfile<<ed[n].date<<"  ";
		edfile<<ed[n].remark;
		edfile<<endl;
	} 
    edfile.close();
	cout<<"����ɹ�"<<endl;
	

};

void banfei::fixed_expend()
{
	int id,i;
	cout<<"��������Ҫ�޸ĵı��"<<endl;
	cin>>id;
	for(i=0;i<icount;i++)
	{
		if(ed[i].id==id)
		{	
			cout<<"�ñ�ŵľ�����Ϣ����"<<endl;
			ed[i].myprintf();
			cout<<"�������޸Ľ��:"<<endl;
			cin>>ed[i].money;
			cout<<"�������޸ľ���������:"<<endl;
			cin>>ed[i].name;
			cout<<"�������޸�����:"<<endl;
			cin>>ed[i].date;
			cout<<"�������޸ı�ע:"<<endl;
			cin>>ed[i].remark;
			cout<<"�޸ĳɹ�"<<endl;
			return;

		}
	}
	cout<<"��������û����Ӧ�ı��"<<endl;
};

void banfei::fixed_income()
{
	int id,i;
	cout<<"��������Ҫ�޸ĵı��"<<endl;
	cin>>id;
	for(i=0;i<icount;i++)
	{
		if(im[i].id==id)
		{	
			cout<<"�ñ�ŵľ�����Ϣ����"<<endl;
			im[i].myprintf();
			cout<<"�������޸Ľ��:"<<endl;
			cin>>im[i].money;
			cout<<"�������޸ľ���������:"<<endl;
			cin>>im[i].name;
			cout<<"�������޸�����:"<<endl;
			cin>>im[i].date;
			cout<<"�������޸ı�ע:"<<endl;
			cin>>im[i].remark;
			cout<<"�޸ĳɹ�"<<endl;
			return;

		}
	}
	cout<<"��������û����Ӧ�ı��"<<endl;


};

void banfei::search_expend()
{
	int i;
	string name;
	cout<<"�����뾭��������"<<endl;
	cin>>name;
	for(i=0;i<ecount;i++)
	{	
		if(name==ed[i].name)
			ed[i].myprintf();
	}
};

void banfei::search_income()
{
	int i;
	string name;
	cout<<"�����뾭��������"<<endl;
	cin>>name;
	for(i=0;i<icount;i++)
	{	if(name==im[i].name)
			im[i].myprintf();
	}
};

void banfei::display_expend()
{
	int i;
	for(i=0;i<ecount;i++)
	{
		ed[i].myprintf();
	}
};

void banfei::display_income()
{
	int i;
	for(i=0;i<icount;i++)
	{
		im[i].myprintf();
	}
};

void banfei::add_expend()
{	
	
	ed[ecount].id = ecount+1;
	cout<<"��������:"<<endl;
	cin>>ed[ecount].money;
	cout<<"�����뾭��������:"<<endl;
	cin>>ed[ecount].name;
	cout<<"����������:"<<endl;
	cin>>ed[ecount].date;
	cout<<"�����뱸ע:"<<endl;
	cin>>ed[ecount].remark;
	cout<<"��ӳɹ�"<<endl;
	ecount++;
};

void banfei::add_income()
{
	;
	im[icount].id = icount+1;
	cout<<"��������:"<<endl;
	cin>>im[icount].money;
	cout<<"�����뾭��������:"<<endl;
	cin>>im[icount].name;
	cout<<"����������:"<<endl;
	cin>>im[icount].date;
	cout<<"�����뱸ע:"<<endl;
	cin>>im[icount].remark;
	cout<<"��ӳɹ�"<<endl;
	icount++;
};

void banfei::Menu()
{
	int choice;
	system("cls");
	cout<<endl<<"��������Ӧ�Ĳ�����Ž��в���:"<<endl;
	cout<<"�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I"<<endl;
	cout<<"�I                                                        �I"<<endl;
	cout<<"�I       1.����¼��                 2.֧��¼��            �I"<<endl;
	cout<<"�I                                                        �I"<<endl;
	cout<<"�I       3.������ʾ                 4.֧����ʾ            �I"<<endl;
	cout<<"�I                                                        �I"<<endl;
    cout<<"�I       5.�������                 6.֧������            �I"<<endl;
	cout<<"�I                                                        �I"<<endl;
	cout<<"�I       7.�����޸�                 8.֧���޸�            �I"<<endl;
	cout<<"�I                                                        �I"<<endl;
	cout<<"�I       9.��������                 10.�˳�ϵͳ           �I"<<endl;
	cout<<"�I                                                        �I"<<endl;
	cout<<"�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I"<<endl;
	cout<<"��";
	cin>>choice;
	while(choice<1||choice>10)
   { 
       cout<<"����������������ȷ�Ĳ������!"<<endl;
       cout<<"��";
       cin>>choice;
   }
	switch(choice)
    {
    case 1: add_income();
        break;
    case 2:add_expend();
		break;
    case 3: display_income();
        break;
	case 4:display_expend();
		break;
    case 5: search_income();//�������
        break;
	case 6: search_expend();//֧������
        break;
    case 7:fixed_income();//�����޸�
		break;
    case 8: fixed_expend();//֧���޸�
        break;
	case 9:savedata();//�������ݵ��ļ�
		break;
    case 10: exit(0);
        break;
	default:
		break;
	
   }
	cout<<"...������ص����˵�..."<<endl;
	cin.get();
	cin.get();
	Menu();

};



void income::myprintf()
{
	cout<<"##############����##################"<<endl;
	cout<<"#                                   #"<<endl;
	cout<<" ���� ��ţ�"<<id<<"   ���: "<<money<<endl;
	cout<<"#                                   #"<<endl;
	cout<<" ���� �����ˣ�"<<name<<"   ʱ��: "<<date<<endl;
	cout<<"#                                   #"<<endl;
	cout<<" ���� ��ע:��"<<remark<<endl;
	cout<<"#                                   #"<<endl;
	cout<<"#####################################"<<endl;
};
void expend::myprintf()
{
	cout<<"##############֧��##################"<<endl;
	cout<<"#                                   #"<<endl;
	cout<<" ���� ��ţ�"<<id<<"   ���: "<<money<<endl;
	cout<<"#                                   #"<<endl;
	cout<<" ���� �����ˣ�"<<name<<"   ʱ��: "<<date<<endl;
	cout<<"#                                   #"<<endl;
	cout<<" ���� ��ע:��"<<remark<<endl;
	cout<<"#                                   #"<<endl;
	cout<<"#####################################"<<endl;
};