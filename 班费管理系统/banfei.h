#ifndef BANFEI_H

#define BANFEI_H

#include<iostream>
#include <string>
#include<fstream>
using namespace std;



class fee//������
{

public:
	fee(){};

public:
	int id;//���
	int money;//���
	string name;//����������
	string date;//ʱ��
	string remark;//��ע

	
};

class income:public fee//�����࣬�̳з�����
{
public:	
	void myprintf();//��ӡ����Ҫ����Ϣ

};

class expend:public fee//֧���࣬�̳з�����
{
public:	
	void myprintf();//��ӡ����Ҫ����Ϣ

};


class banfei
{
public:
	void Menu();//�˵�����
	void add_income();//����¼��
	void add_expend();//֧��¼��
	void display_income();//������ʾ
	void display_expend();//֧��¼��
	void search_income();//�������
	void search_expend();//֧������
	void fixed_income();//�����޸�
	void fixed_expend();//֧���޸�
	void savedata();//�������ݵ��ļ�
	void initdata();//��ʼ������,���ļ��ж�ȡ


public:
	income im[50];//��¼����
	expend ed[50]; //��¼֧��
	int icount;//�������
	int ecount;//֧������
};








#endif