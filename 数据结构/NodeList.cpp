#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

/*
���嵥������ڵ�ṹ�� 
value	�洢����ڵ�����
next	�洢ָ����һ������ڵ��ָ�� 
*/
struct Node{
	int value;
	Node* next;
};

/*
��������ṹ��
header	�洢����ͷ�ڵ�
length 	�洢����Ԫ�ظ��� 
*/
struct LinkList{
	Node* header;
	int length;
};

/*
������������ڵ�
������ڵ�ֵ��ʼ��Ϊ�������v��ֵ
������ڵ�ָ����һ������ڵ��ָ����ΪNULL(0) 
*/
Node* createNode(int v){
	Node* node=new Node;
	node->value=v;
	node->next=NULL;
	return node;
}

/*
��������
���ݴ������length��������length���ڵ������ 
*/
LinkList createLinkList(int length){ 
	LinkList list;
	list.header=createNode(0);
	list.length=length;
	Node* p=list.header;
	int i=0;
	while (i<length-1){
		p->next=createNode(++i);
		p=p->next;
	}
	return list;
}


/*
��ӡ���������нڵ�
*/
void print(LinkList list){
	Node* p=list.header;
	cout<<"NodeList length:"<<list.length<<endl;
	int i=0;
	while(p){
		printf("Node %d\t\tValue:%d\n",i++,p->value);
		p=p->next;
	}
	cout<<"========================"<<endl<<endl;;
	return;
}

/*
��������ڵ�
��list����posλ�ô���������ڵ�node 
*/
LinkList insertNode(LinkList list,Node* node,int pos){
	if (pos<=0){
		node->next=list.header;
		list.header=node;
	}
	else if (pos>=list.length){
		Node* p=list.header;
		for (int i=0;i<list.length-1;i++) p=p->next;
		p->next=node;
	}
	else {
		Node* p=list.header;
		for (int i=0;i<list.length && i<pos-1;i++) p=p->next;
		Node* temp=p->next;
		p->next=node;
		node->next=temp;
	}
	list.length++;
	return list;
}


/*
��������ڵ�
��list����posλ�ò���һ���ڵ���ֵΪvalue 
*/
LinkList insertNode(LinkList list,int value,int pos){
	Node* node=createNode(value);
	if (pos<=0){
		node->next=list.header;
		list.header=node;
	}
	else if (pos>=list.length){
		Node* p=list.header;
		for (int i=0;i<list.length-1;i++) p=p->next;
		p->next=node;
	}
	else{
		Node* p=list.header;
		for (int i=0;i<list.length && i<pos-1;i++) p=p->next;
		Node* temp=p->next;
		p->next=node;
		node->next=temp;
	}
	list.length++;
	return list;
}

/*
ɾ������ڵ�
ɾ������list��posλ�ô��Ľڵ� 
*/
LinkList deleteNode(LinkList list,int pos){
	if (pos<=0){
		Node* temp=list.header;
		list.header=list.header->next;
		delete temp;
	}
	else if (pos>=list.length){
		Node* p=list.header;
		for (int i=0;i<list.length-1;i++) p=p->next;
		delete p->next;
		p->next=NULL;
	}
	else{
		Node* p=list.header;
		for (int i=0;i<list.length && i<pos-1;i++) p->next;
		Node* temp=p->next;
		p->next=temp->next;
		delete temp;
	}
	list.length--;
	return list;
}

/*
�޸�����ڵ� 
�޸�����list��posλ�õ�ֵΪvalue 
*/
void updateNode(LinkList list,int value,int pos){
	Node* p=list.header;
	for(int i=0;i<list.length-1 && i<pos;i++) p=p->next;
	p->value=value;
}

/*
��ѯ����list��posλ�õ�ֵ����ӡ��ֵ 
*/
void queryNode(LinkList list,int pos){
	if (pos<0 || pos>=list.length){
		cout<<"Position out of range!"<<endl;
		cout<<"========================"<<endl<<endl;;
		return;
	}
	Node* p=list.header;
	for (int i=0;i<list.length-1 && i<pos;i++) p=p->next;
	printf("Node %d\t\tvalue %d\n",pos,p->value);
	cout<<"========================"<<endl<<endl;;
	return; 
}
 
/*
��ѯ����list��ֵΪvalue�Ľڵ㣬����ӡ�ڵ� 
*/
void queryValue(LinkList list,int value){
	Node* p=list.header;
	bool flag=true;
	for (int i=0;i<list.length;i++){
		if (p->value==value){
			printf("Node %d\t\tvalue %d\n",i,p->value);
			flag=false;
		}
		p=p->next;
	}
	if (flag) {
		cout<<"No Node's value="<<value<<endl;
		cout<<"========================"<<endl<<endl;;
	}
}


int main(){
	cout<<"Create linklist:"<<endl;
	cout<<"------------------------"<<endl;
	LinkList list=createLinkList(10);
	print(list);
	
	cout<<"Insert node into list:"<<endl;
	cout<<"------------------------"<<endl;
	list=insertNode(list,createNode(10),10);
	print(list);
	
	cout<<"Insert value into list:"<<endl;
	cout<<"------------------------"<<endl;
	list=insertNode(list,2,2);
	print(list);
	
	cout<<"Delete node from list"<<endl;
	cout<<"------------------------"<<endl;
	list=deleteNode(list,5);
	print(list);
	
	cout<<"Update Node in list"<<endl;
	cout<<"------------------------"<<endl;
	updateNode(list,5,0);
	print(list);
	
	cout<<"Query Node in list"<<endl;
	cout<<"------------------------"<<endl;
	queryNode(list,2);
	
	cout<<"Query value in list"<<endl;
	cout<<"------------------------"<<endl;
	queryValue(list,0);
	return 0;
} 
