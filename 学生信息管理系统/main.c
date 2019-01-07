#include<stdio.h>
#include<windows.h>
#include<math.h>
#include<process.h>
#include<conio.h>

#define N 3
int num;
typedef struct {
	char no[10];      /*ѧ��*/
	char name[20];    /*����*/
	int score[N];     /*N�Ź��γɼ�*/
	double total;     /*�ܷ�*/
	double aver;      /*ƽ����*/
	int order;        /*����*/
} STU;

typedef struct node { //�������
	STU data;
	struct node *next;
} Node;

typedef struct {         //��������
	Node *head,*tail;   //ָ������ĵ�һ�������һ�����
	int len;        //ָʾ�����н��ĸ���
} LinkList;
LinkList *L;
void ShowMenu(LinkList *L);
void input(LinkList *L);
void output(LinkList *L);
void query(LinkList *L);
void querybyname(LinkList *L);
void querybyid(LinkList *L);
void Delete(LinkList *L);
void change(LinkList *L);
void addStu(LinkList *L);



int main() {
	LinkList *L = (LinkList *)malloc(sizeof(LinkList));
	do {
		system("cls");
		ShowMenu(L);
	} while(1);


	return 0;
}

//�˵�չʾ
void ShowMenu(LinkList *L) {
	int i;
	char s[10];

	char *p[7]= {"1����Ϣ¼��","2����Ϣ���","3����Ϣ��ѯ","4������ѧ����Ϣ","5��ɾ��ѧ����Ϣ","6���޸�ѧ����Ϣ","7���˳�����"};
	for(i=0; i<20; i++) {
		printf("*");
		if(i==10)
			printf("Menu");
		if(i==19)
			printf("\n");

	}
	for(i=0; i<7; i++) {
		printf("%s\n",p[i]);
	}
	for(i=0; i<20; i++) {
		printf("-");
		if(i==10)
			printf("Menu");
		if(i==19)
			printf("\n");

	}
	printf("��ѡ�������");
	do {
		scanf("%s",s);
		i=atoi(s);
		if(i<1||i>7)
			printf("������������Ч������");
	} while(i<1||i>7);

	switch(i) {
		case 1:system("cls");input(L);break;
		case 2:system("cls");output(L);break;
		case 3:system("cls");query(L);break;
		case 4:system("cls");addStu(L);break;
		case 5:system("cls");Delete(L);break;
		case 6:system("cls");change(L);break;
		case 7:exit(0);
	}
}

//������Ϣ
void input(LinkList *L) {
	int i;
	Node *p,*q;
	L->len=0;
	printf("������ѧ��������");
	scanf("%d",&num);
	printf("������ѧ������Ϣ��");
	for(i=0; i<num; i++) {
		p=(Node*)malloc(sizeof(Node));
		p->next=NULL;
		if (i==0) {
			L->head=p;
			q=p;
		}
		else{
			q->next=p;
			q=p;/*   �޸ĵĲ���    ������һ��   */
		}
		printf("��%d��ѧ����",i+1);
		printf("\nѧ�ţ�");
		scanf("%s",p->data.no);
		printf("\n������");
		scanf("%s",p->data.name);
		printf("\n���ĳɼ���");
		scanf("%d",&p->data.score[1]);
		printf("\n��ѧ�ɼ���");
		scanf("%d",&p->data.score[2]);
		printf("\nӢ��ɼ���");
		scanf("%d",&p->data.score[3]);
		L->len++;
		L->tail=p;
	}
}

//�����Ϣ
void output(LinkList *L) {
	int i;
	Node *p;
	p=L->head;
	//p=L->head->next;
	printf("ѧ����Ϣ���£�\n");
	printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\t\tƽ����\n");
	for(i=0; i<L->len; i++) {/*   �޸ĵĲ���    ��num�޸�ΪL->len   */
		p->data.total=p->data.score[1]+p->data.score[2]+p->data.score[3];
		p->data.aver=p->data.total/N;
		printf("%s\t%s\t%d\t%d\t%d\t%lf\t%lf\n",p->data.no,p->data.name,p->data.score[1],p->data.score[2],p->data.score[3],p->data.total,p->data.aver);
		p=p->next;
	}
	getch();

}

//����
void query(LinkList *L) {
	int i;
	char x[10];
	Node *p;
	p=L->head->next;
	printf("�����������������롰1��������ѧ�Ų��������롰2����");
	do {
		scanf("%s",x);
		i=atoi(x);
		if(i<1||i>5)
			printf("������������Ч������");
	} while(i<1||i>2);
	switch(i) {
		case 1:querybyname(L);break;
		case 2:querybyid(L);break;
	}

}

//����������
void querybyname(LinkList *L) {
	char xingming[15];
	Node *p;
	p=L->head;/*   �޸ĵĲ���    ��L->head->next�޸�ΪL->head   */
	printf("��������Ҫ���ҵ�������");
	scanf("%s",xingming);
	while(p) {
		if(strcmp(p->data.name,xingming)==0) {
			printf("��Ҫ���ҵ�ѧ����Ϣ���£�\n");
			printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\t\tƽ����\n");
			printf("%s\t%s\t%d\t%d\t%d\t%f\t%f\n",p->data.no,p->data.name,p->data.score[1],p->data.score[2],p->data.score[3],p->data.total,p->data.aver);
			getch();
			return 0;
		} else
			p=p->next;
	}
	printf("���޴��ˣ�");
	getch();
}

//��ѧ�Ų���
void querybyid(LinkList *L) {
	char sid[10];
	Node *p;
	p=L->head;/*   �޸ĵĲ���    ��L->head->next�޸�ΪL->head   */
	p->data.total=p->data.score[1]+p->data.score[2]+p->data.score[3];
	p->data.aver=p->data.total/N;
	printf("��������Ҫ���ҵ�ѧ�ţ�");
	scanf("%s",sid);
	while(p) {
		if(strcmp(p->data.no,sid)==0) {
			printf("��Ҫ���ҵ�ѧ����Ϣ���£�\n");
			printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\t\tƽ����\n");
			printf("%s\t%s\t%d\t%d\t%d\t%f\t%f\n",p->data.no,p->data.name,p->data.score[1],p->data.score[2],p->data.score[3],p->data.total,p->data.aver);
			getch();
			return 0;
		} else
			p=p->next;
	}
	printf("���޴��ˣ�\n");
	getch();
}

//������Ϣ
void addStu(LinkList *L) {/*     �޸ĵĲ���    �޸��˺�������*/

	Node *p,*q,*s;
	int count=1,n;
	p=(Node *)malloc(sizeof(Node));
	printf("��������ѧ������Ϣ��\n");
	printf("\nѧ�ţ�");
	scanf("%s",&p->data.no);
	printf("\n������");
	scanf("%s",&p->data.name);
	printf("\n���ĳɼ���");
	scanf("%d",&p->data.score[1]);
	printf("\n��ѧ�ɼ���");
	scanf("%d",&p->data.score[2]);
	printf("\nӢ��ɼ���");
	scanf("%d",&p->data.score[3]);
	p->next=NULL;
	printf("��������Ҫ�����λ�ã�");
	scanf("%d",&n);
	if (n<1) {
		free(p);
		return ;
	}
	q=L->head;
	s=L->head;
	while (count<n&&q->next!=NULL){
		count++;
		s=q;
		q=q->next;
	}
	if (count==1){
		p->next=L->head;
		L->head=p;
		L->len++;
	}
	else if (q->next==NULL){
		q->next=p;
		p->next=NULL;
		L->tail=p;
		L->len++;
	} 
	else{
		s->next=p;
		p->next=q;
		L->len++;
	}
}

//ɾ����Ϣ
void Delete(LinkList *L) {
	int x,y,count;
	Node *p,*q;
	printf("��������Ҫɾ����ѧ��:");
	scanf("%d",&x); 
	p=L->head;
	q=p;
	count=1;
	while (count<=L->len){
		if (x==atoi(p->data.no)){
			if (L->head==p){
				L->head=p->next;
				L->len--;
				free(p);
				printf("ɾ���ɹ���");
				getch();
				return;
			}
			else{
				q->next=p->next;
				L->len--;
				free(p);
				printf("ɾ���ɹ���");
				getch();
				return;
			}
		}
		else{
			q=p;
			p=p->next;
			count++;
		}
	}
	printf("�������ѧ������");
	getch();
	return; 
}

//�޸���Ϣ
void change(LinkList *L) {

}
