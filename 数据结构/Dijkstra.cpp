#include<iostream>
#include<cstdio>
#include<cstring>
#include<conio.h>
#define MAXLEN 500
#define MAX 0x7FFFFFFF
using namespace std;


string CityList[MAXLEN];
int map[MAXLEN][MAXLEN]= {0};


int N;

bool check_input(int x,int y,int w,int N){
	if (w<0 || x==y || x>N || y>N || (map[x][y]!=0 && map[x][y]!=MAX)|| (map[x][y]!=0 && map[x][y]!=MAX)){
		cout<<"�������ݲ����Ϲ淶������������"<<endl;
		getch();
		return true;
	}
	return false;
}

void Readin() {
	int M,x,y,w;
	memset(map,sizeof(map),0);
	cout<<"�������������:";
	cin>>N;
	cout<<"������·������:";
	cin>>M;
	
	if (M>(N+1)*N/2){
		cout<<"�������·����������������·������"<<endl;
		getch();
		return;
	}
	
	cout<<endl;
	for (int i=1; i<=N; i++) {
		printf("��%d����������:",i);
		cin>>CityList[i];
	}
	printf("����x��� ����y��� ·������\n");
	printf("-----------------------------\n");
	for (int i=1; i<=M; i++) {
		do{
			printf("��%d��:",i);
			cin>>x>>y>>w;
		}while(check_input(x,y,w,N));
		map[x][y]=w;
		map[y][x]=w;
	}
	for (int i=1; i<=N; i++) {
		for (int j=1; j<=N; j++)
			if (i!=j && map[i][j]==0) map[i][j]=MAX;
	}
}

void Mapprint(int n=N) {
	if (N==0) return;
	cout<<"\t";
	for (int i=1; i<=n; i++) cout<<CityList[i]<<"\t";
	cout<<endl;
	for (int i=1; i<=n*9; i++) cout<<'-';
	cout<<endl;
	for (int i=1; i<=n; i++) {
		cout<<CityList[i]<<"\t";
		for (int j=1; j<=n; j++)
			if (map[i][j]!=MAX) cout<<map[i][j]<<"\t";
			else cout<<"-\t";
		cout<<endl;
	}
}

void Mapadd() {
	int n,x,y,w,m;
	cout<<"���������ӵĳ��и���:";
	cin>>n;
	cout<<"������������·������:";
	cin>>m;
//	if (m>(N*n+(n+1)*n/2)){
//		cout<<"�������·����������������·������"<<endl;
//		getch();
//		return;
//	}
	cout<<endl;
	for(int i=N+1; i<=N+n; i++) {
		printf("��%d�����е�����:",i);
		cin>>CityList[i];
	}
	printf("\n����x��� ����y��� ·������\n");
	printf("-----------------------------\n");
	for (int i=1; i<=m; i++) {
		do{
			printf("��%d��:",i); 
			cin>>x>>y>>w;
		}while (check_input(x,y,w,N+n));
		map[x][y]=w;
		map[y][x]=w;
	}
	for (int i=1;i<=N+n;i++)
		for(int j=1;j<=N+n;j++)
		if (i!=j && map[i][j]==0) map[i][j]=MAX;
	N=N+n;
}

void Delcol(int x) {
	int i,j;
	if (x>N or x<1) return;
	for (i=1; i<=N; i++) {
		for (j=x; j<N; j++)
			map[i][j]=map[i][j+1];
		map[i][j]=0;
	}
}

void Delrow(int x) {
	int i;
	if (x>N or x<1) return;
	for (i=x; i<N; i++)
		memcpy(map[i],map[i+1],sizeof(int)*(N));
	memset(map[i],0,N-1);
}

void Delname(int x) {
	int i;
	for (i=x; i<N; i++) CityList[i]=CityList[i+1];
	CityList[i]= {0};
}

void Mapdel() {
	int x;
	cout<<"��������Ҫɾ���ĳ��б��:";
	cin>>x;
	Delname(x);
	Delcol(x);
	Delrow(x);
	N--;
}

void Mapmod(){
	string x,y; 
	int i,j,w;
	cout<<"��������Ҫ�޸ĵ��������е�����"<<endl;
	cout<<"����A:"; cin>>x;
	cout<<"����B:";	cin>>y;
	cout<<"�������޸�ֵ(����ֵ<=0ɾ��·��):"; cin>>w; 
	for (i=1;i<=N;i++)
	if (x==CityList[i]) break;
	for (j=1;i<=N;j++)
	if (y==CityList[j]) break; 
	if (i==N && CityList[i]!=x){
		cout<<"�޷��ҵ�����A"<<endl;
		getch();
		return; 
	}
	if (j==N && CityList[j]!=y){
		cout<<"�޷��ҵ�����B"<<endl;
		getch();
		return;
	}
	if (w<=0) {
		map[i][j]=MAX;
		map[j][i]=MAX;
	} 
	else{
		map[i][j]=w;
		map[j][i]=w;
	}
	
} 

bool check(bool* arr,int n){
	for (int i=1;i<=n;i++)
	if (!arr[i]) return true;
	return false;
}


void Dijkstra(){
	int d,s=1,pos,m;
	cout<<"������Ŀ�ĵس��У�Ĭ�ϳ������м����Ϊ1�ĳ��У�"<<endl;
	cin>>d;
	if (d>N){
		cout<<"������ĳ��г�����Χ"<<endl;
		getch();
		return;
	}
	
	int dis[MAXLEN]={0};
	bool is_v[MAXLEN];
	string route[MAXLEN];
	memset(is_v,0,sizeof(bool)*MAXLEN);
	
	for (int i=1;i<=N;i++){
		dis[i]=map[s][i];
		route[i]=CityList[s]+"-->"+CityList[i];
	}
		
	dis[s]=0;
	is_v[s]=true;
	
	while (check(is_v,N)){
		pos=0;
		m=MAX;
		for (int i=1;i<=N;i++)
		if (!is_v[i] && m>dis[i]){
			m=dis[i];
			pos=i;
		}
		is_v[pos]=true;
		
		for (int i=1;i<=N;i++)
		if (!is_v[i] && dis[pos]+map[pos][i]>=0) {
			if (dis[i]>dis[pos]+map[pos][i]){
				dis[i]=dis[pos]+map[pos][i];
				route[i]=route[pos]+"-->"+CityList[i];
			}
		}
	}
	if (dis[d]==0){
		cout<<"�����ڵִ�ó��е�·��"<<endl;
		getch();
		return; 
	}
	cout<<"���·������:"; 
	cout<<dis[d]<<endl;
	cout<<route[d]<<endl;
	getch();
}

void logo(){
	system("cls");
	printf("	    ____ _   _ __        __            \n");
	printf("	   / __ \(_) (_) /_______/ /__________ _\n");
	printf("	  / / / / / / / //_/ ___/ __/ ___/ __ `/\n");
	printf("	 / /_/ / / / / ,< (__  ) /_/ /  / /_/ / \n");
	printf("	/_____/_/_/ /_/|_/____/\\__/_/   \\__,_/  \n");
	printf("	       /___/                            \n");

	cout<<"============================================="<<endl;
	Mapprint(); 
	cout<<"============================================="<<endl;
	cout<<"	         1.¼�����·��             "<<endl;
	cout<<"	         2.���ӳ���·��             "<<endl;
	cout<<"		 3.�༭����·��             "<<endl; 
	cout<<"	         4.ɾ������                 "<<endl;
	cout<<"	         5.�������·��             "<<endl;
	cout<<"	         0.�˳�                     "<<endl;
}

void init(){
	N=6;
	CityList[1]="�Ͼ�";
	CityList[2]="��";
	CityList[3]="����";
	CityList[4]="����";
	CityList[5]="����";
	CityList[6]="�Ϻ�";
	map[1][2]=1;
	map[2][1]=1;
	map[2][4]=3;
	map[4][2]=3;
	map[4][6]=15;
	map[6][4]=15;
	map[5][6]=4;
	map[6][5]=4;
	map[5][3]=5;
	map[3][5]=5;
	map[1][3]=12;
	map[3][1]=12;
	map[2][3]=9;
	map[3][2]=9;
	map[3][4]=4;
	map[4][3]=4;
	map[4][5]=13;
	map[5][4]=13;
	for (int i=1;i<=N;i++)
		for (int j=1;j<=N;j++)
		if (i!=j && map[i][j]==0) map[i][j]=MAX;
}

int main() {
	string choice;
	N=0;
	init();
	while (true){
		logo();
		cin>>choice;
		switch(choice[0]){
			case '1': Readin(); break;
			case '2': Mapadd(); break;
			case '3': Mapmod(); break;
			case '4': Mapdel(); break;
			case '5': Dijkstra(); break;
			case '0': return 0;
			default:
				continue;
		}
	}
	return 0;
}
