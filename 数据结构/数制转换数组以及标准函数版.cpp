#include<iostream>
#include<string.h>	//strlen��atoi��itoa�Ⱥ�����ͷ�ļ� 
#include<cstdio>	//c�Ļ����������������ͷ�ļ� 
#include<cstdlib>	//system������ͷ�ļ� 
#include<conio.h>	//getch����ͷ�ļ� 
#include<math.h>	//��ѧ����powͷ�ļ� 
#define MAXSIZE 256	//���������Լ��ַ�������󳤶� 
using namespace std;

//�˵���ӡ���� 
void menu(){
	system("cls");	//����̨��� 
    printf("+==========================================+\n");
    printf("+           �γ����-����ת��              +\n");
	printf("+==========================================+\n");
	printf("+             1.����ʵ�ְ�                 +\n");
	printf("+             2.c++�Դ�����                +\n");
	printf("+             0.�˳�                       +\n"); 
	printf("+==========================================+\n");
	printf("                        code by �������    \n");
	return;                                      
}


//����ת������ʵ�ְ汾���� 
void arrayVersion(){
	string temp;			//�����ݴ��û������룬ʹ��string�ͷ�ֹ�û���������ʹ�����˳� 
	char q[MAXSIZE];		//����û���������� 
	int M,len,MD,target;	//M���ֽ��ƣ�len�û��������ֵĳ��ȣ�MDת��Ϊʮ���ƺ�Ľ����	
							//targetĿ����� 
	int ans[MAXSIZE];		//ת��Ϊ������ƺ�Ľ���洢 
	
	 
	cout<<"���������ֵĽ���(2-16):"; cin>>temp;
	M=atoi(temp.c_str());
	//�������������Ƿ�Ϸ� 
	if (M<=1){
		cout<<"��������ݲ����Ϲ淶"<<endl;
		getch();
		return;
	}
	
	cout<<"�����������:"; cin>>q;
	//��ȡ�����ֳ��� 
	len=strlen(q);
	//�������е�Сд�ַ�תΪ��д�ַ������������ 
	strupr(q);
	
	//ת��Ϊʮ���� 
	MD=0;
	for (int i=len-1;i>=0;i--){
		if (q[i]<='9' && q[i]>='0') MD=MD+(q[i]-48)*pow(M,len-i-1);
		else if (q[i]>='A' && q[i]<='F') MD=MD+(q[i]-55)*pow(M,len-i-1);
	}
	cout<<"ת��Ϊ10���ƽ��:"<<MD<<endl;
	
	//ת��Ŀ����� 
	cout<<"�����Ŀ�����(2-16):"; cin>>temp;
	target=atoi(temp.c_str());
	if (target<2 && target >16){
		cout<<"��������ݲ��Ϸ�"<<endl;
		getch();
		return;
	} 
	int p=0;	//������±� 
	while (MD!=0){
		ans[p++]=MD%target;
		MD=MD/target;
	}
	cout<<"ת�����:";
	for (int i=p-1;i>=0;i--)
	if (ans[i]>9) printf("%c",ans[i]+55);
	else cout<<ans[i];
	cout<<endl;
	getch();	//�ȴ��û��Ӽ��̶�ȡһ���ַ���������ͣ����̨չʾ��� 
	return;
}

//c++�Դ�����ʵ�ְ汾 
void funcVersion(){
	string temp;
	char q[MAXSIZE];
	int M,len,MD,target;
	char ans[MAXSIZE];
	
	cout<<"���������ֵĽ���(2-16):"; cin>>temp;
	M=atoi(temp.c_str());
	if (M<=1){
		cout<<"��������ݲ����Ϲ淶"<<endl;
		getch();
		return;
	}
	
	cout<<"�����������:"; cin>>q;
	len=strlen(q);
	strupr(q);
	
	MD=0;
	for (int i=len-1;i>=0;i--){
		if (q[i]<='9' && q[i]>='0') MD=MD+(q[i]-48)*pow(M,len-i-1);
		else if (q[i]>='A' && q[i]<='F') MD=MD+(q[i]-55)*pow(M,len-i-1);
	}
	cout<<"ת��Ϊ10���ƽ��:"<<MD<<endl;
	
	cout<<"�����Ŀ�����(2-16):"; cin>>temp;
	target=atoi(temp.c_str());
	if (target<2 && target >16){
		cout<<"��������ݲ��Ϸ�"<<endl;
		getch();
		return;
	}
	//itoa��������һ��ʮ��������ת��ΪtargetĿ����Ƶ���
	//�����ַ��������ʽ������洢�����Ｔ��������ans�� 
	itoa(MD,ans,target);
	cout<<"ת�����:"; cout<<ans<<endl;
	getch();
	return;
	
}

int main(){
	string choice;	//�洢�û��˵�ѡ����string�ͷ�ֹ�û�����Ƿ����ݴ�ϳ��� 
	while (true){
		menu();		//��ӡ�˵� 
		cin>>choice;
		switch(choice[0]){
			case '1': arrayVersion(); break;
			case '2': funcVersion(); break;
			case '0': return 0;
			default: continue;
		}
	}
	return 0;
}
