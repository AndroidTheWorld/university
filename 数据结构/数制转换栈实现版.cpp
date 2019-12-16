#include<iostream>
#include<string.h>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<cmath>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAXSIZE 256
using namespace std;

//ջ�Ĵ洢�ṹ���� 
struct STACK {
	int* top;
	int* base;
	int size;
};

//ջ��ʼ������ 
int init(STACK &s) {
	s.base=(int*) malloc(STACK_INIT_SIZE* sizeof(int));
	if (!s.base) {
		printf("[INFO] Malloc error!\n");
		return -1;
	}
	s.top=s.base;
	s.size=STACK_INIT_SIZE;
}

//��ȡջ��Ԫ�غ��� 
int GetTop(STACK s) {
	if (s.top==s.base) {
		printf("[INFO] Stack empty!\n");
		return -1;
	}
	return *(s.top-1);
}

//��ջ��ѹ�����ݺ��� 
int push(STACK &s,int x) {
	if (s.top-s.base>=s.size) {
		s.base=(int*)realloc(s.base,(s.size+STACKINCREMENT)*sizeof(int));
		if (!s.base) {
			printf("[INFO] Realloc error!\n");
			return -1;
		}
		s.top=s.base+s.size;
		s.size+=STACKINCREMENT;
	}
	*s.top++=x;
	return 0;
}

//��ջ���������ݺ��� 
int pop(STACK &s) {
	if (s.top==s.base) {
		printf("[INFO] Stack empty!\n");
		return -1;
	}
	return *(--s.top);
}

//�ж�ջ�Ƿ�Ϊ�� 
bool IsEmpty(STACK s) {
	if (s.base==s.top) return true;
	else return false;
}

//��ӡջ���� 
int print(STACK s) {
	for (int* i=s.base; i!=s.top; i++) printf("%d ",*i);
	printf("\n");
}

//�˵���ӡ 
void logo() {
	system("cls");
	printf("+===============================+\n");
	printf("+       ����ת��-ջʵ�ְ�       +\n");
	printf("+===============================+\n");
	printf("               - code by �������\n\n");
	return;
}

int main() {
	while (true) {
		logo();				//�˵���ӡ 
		string temp;		
		char q[MAXSIZE];
		int M,len,MD,target;
		STACK s;			//���Դ洢�����ջ������ 

		cout<<"���������ֵĽ���(2-16):";
		cin>>temp;
		M=atoi(temp.c_str());
		if (M<=1) {
			cout<<"��������ݲ����Ϲ淶"<<endl;
			getch();
			return 0;
		}

		cout<<"�����������:";
		cin>>q;
		len=strlen(q);
		strupr(q);

		MD=0;
		for (int i=len-1; i>=0; i--) {
			if (q[i]<='9' && q[i]>='0') MD=MD+(q[i]-48)*pow(M,len-i-1);
			else if (q[i]>='A' && q[i]<='F') MD=MD+(q[i]-55)*pow(M,len-i-1);
		}
		cout<<"ת��Ϊ10���ƽ��:"<<MD<<endl;

		cout<<"�����Ŀ�����(2-16):";
		cin>>temp;
		target=atoi(temp.c_str());
		if (target<2 && target >16) {
			cout<<"��������ݲ��Ϸ�"<<endl;
			getch();
			return 0;
		}
		
		init(s);	//ջ��ʼ�� 
		int t;		//�ݴ��ջ��������Ԫ�� 
		printf("ת�����:");
		while(MD){
			push(s,MD%target);
			MD=MD/target;
		}
		while (!IsEmpty(s)){
			if ((t=pop(s))>9) printf("%c",t+55);
			else printf("%d",t);
		}
		printf("\n");
		getch();
	}
	return 0;
}
