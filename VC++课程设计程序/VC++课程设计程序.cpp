/*��5��	�绰������--Դ����ע�����£�*/
#include<fstream>       
#include<conio.h>
#include<iostream>     
#include<iomanip>
#include<string.h>
#include<stdlib.h>
#include<time.h>

using namespace std;
 
class Base
{
	public:
	char date[20];
	char time[20];
    char szLName[20];
	char szFName[20];
    char szNumber[20];
};
 
class CTelRecord:public Base
{
public:
    CTelRecord();                                //ȱʡ�Ĺ��캯��
	~CTelRecord(){};                            //��������
    CTelRecord(char *name,char *number,char *,char*,char*);        //���캯��   
    void SetRecord(char *name,char *number,char *,char *D,char *T);   //���������͵绰����
	void SetDate_Time(char *dd,char*tt){strcpy(date,dd);strcpy(time,tt);}
	char *GetLName(){return szLName;}                //�������
	char *GetFName(){return szFName;}               //�������
	char *GetNumber(){return szNumber;}             //��õ绰����
	char *GetDate(){return date;}
	char *GetTime(){return time;}
    int Compare(CTelRecord &);                      //���������Ƚ�������ֵΪ�㣬���������
    void Show();                                    //��ʾ���� 
    void Modify(char*number);                       //�޸ĵ绰����
    int LookChar(char*szLName);                     //�������ϲ��ң�������ֵΪ1�����ʾ�鵽������û�в鵽
};

class CNode
{
private:
	CTelRecord*pData;
    CNode*pNext;
public:
    CNode(){pData=new CTelRecord;pNext=0;}    //ȱʡ�Ĺ��캯��
	CNode(CTelRecord ctelrecord,CNode node){pData=&ctelrecord,pNext=&node;}//���캯��
    CNode(CNode&node);//���ؿ������캯��
	~CNode(){};
    void InputData(CTelRecord*pdata){pData=pdata;}//����¼�뺯��
    void ShowNode(){pData->Show();}              //�ڵ���ʾ����
    CTelRecord *GetData(){return pData;}         //��ýڵ���Ϣ����
	CNode *GetpNext(){CNode *p=pNext;return p;}  //�����һ���ڵ�
    friend class CList;        //��Ԫ��
};

CNode *current_ptr=NULL;  //ȫ�̱���������ָ����ǰ�������е�λ��
char pause;
class CList
{
	CNode *pHead;
public:
    CList(CNode *node=NULL){pHead=node;}       //���캯��
    ~CList(){DeleteList();}                   //��������
	void SetpHead(CNode*node){pHead=node;}    //��������ͷ����
    void AddNode(CNode *pnode);               //�ѽӵ���ӵ�ͷ���ĺ���
    CNode *DeleteNode(CNode *);               //ɾ���ڵ㺯��
    CNode *LookUp(CTelRecord &);              //�����������ܲ�ѯ����
    void ShowList();                         //��ʾ������
    void DeleteList();                       //ɾ��������
    CNode *GetListHead(){return pHead;}      //�������ͷ������
	CNode *GetListEnd();                     //�������β������
	CNode *GetListNextNode(CNode *);         //���������ָ���ڵ���¸��ڵ㺯��
    void Insert(CNode *pnode);               //������뺯��
	int load_list_from_file();               //���ļ��������ݺ���
	void delete_record();                    //ɾ����¼����
	int verify_delete();                     //ȷ��ɾ���ĺ���
	void write_list_to_file();               //����Ϣд���ļ��ĺ���
	void handle_choice(int choice);          //ѡ������
	void help_me();                         //��������
};


CTelRecord::CTelRecord()
{
	strcpy(date,"date");
	strcpy(time,"time");
	strcpy(szLName,"����");
	strcpy(szFName,"����");
	strcpy(szNumber,"�绰����");
}

CTelRecord::CTelRecord(char *lastname,char *firstname,char *number,char *DD,char *TT)
{  
	strcpy(date,DD);
	strcpy(time,TT);
	strcpy(szLName,lastname);
	strcpy(szNumber,number);
    strcpy(szFName,firstname);
}
		 
void CTelRecord::SetRecord(char *lastname,char *firstname,char *number,char *DD,char *TT)
{
	strcpy(date,DD);
	strcpy(time,TT);
	strcpy(szLName,lastname);
	strcpy(szNumber,number);
	strcpy(szFName,firstname);
}

int CTelRecord::Compare(CTelRecord &ctelrecord)
{  
	if(strcmp(ctelrecord.szLName,szLName)==0||strcmp(ctelrecord.szFName,szFName)==0)
		return 0;
	else return 1;
}

void CTelRecord::Show()
{
	char name[40]="";
	strcpy(name,szLName);
	strcat(name,szFName);
	cout<<setw(40)<<name<<setw(20)<<szNumber<<setw(20)<<date<<setw(10)<<time<<'\n';
}

void CTelRecord::Modify(char *number)
{
	strcpy(szNumber,number);
}

int CTelRecord::LookChar(char szlastName[])
{
	if(strcmp(szLName,szlastName)==0)
		return 1;
	else
		return 0;
}

CNode::CNode(CNode &node)
{
	if(node.pData!=NULL)
	pData=node.pData,pNext=node.pNext;
}

void CList::AddNode(CNode *pnode)
{
	pHead=pnode;
	pHead->pNext=pnode->pNext=NULL;
}

CNode *CList::GetListNextNode(CNode *pnode)
{
	return pnode->pNext;
}

void CList::Insert(CNode *pnode)
{        // �������ϣ��������������е���ȷλ�á��½ڵ㼴������˵㡣
  char temp_name[20];
  CNode *temp_node;
  int tempint(1);
  if(pHead!=NULL)           // ȷ������ͷ��Ϊ�㣡����
  {                           
	  temp_node=current_ptr = pHead;   
      if(GetListNextNode(current_ptr)==NULL)                                //������Ϊһ���ڵ�ʱ
          if(strcmp(pnode->GetData()->GetLName(),pHead->GetData()->GetLName())<=0)   //������ͷ�����ϵ�ֵ��
			                                                                           //Ҫ��������ϵ�ֵ��ʱ
		  {
                pnode->pNext=pHead;
                pHead=pnode;
		  }
          else                                                      //��ʱ������ͷ�����ϵ�ֵ��Ҫ��������ϵ�ֵС
	   	 pHead->pNext=pnode,pnode->pNext=0;
         else                                                      //������Ϊһ���ڵ��ʱ��
		 {
            tempint = strcmp(pnode->pData->GetLName(),temp_name);
            while(tempint >= 0 && temp_node->pNext!=NULL)          //ѭ����Ҫ����Ľڵ�
			{ 
			    current_ptr=temp_node;
                temp_node =GetListNextNode(current_ptr);
                strcpy(temp_name, temp_node->GetData()->GetLName());
                tempint = strcmp(pnode->pData->GetLName(),temp_name);
			}
			if(temp_node==pHead)                                  //���ͷ�ڵ������ֵ��Ҫ���������ֵ��ʱ
			{
                  pnode->pNext=pHead;                             //���µĽڵ���Ϊ����ͷ
                  pHead=pnode;
			}
			else
			{
	            if(tempint<0&&temp_node->pNext==0)         //�պ�ѭ��������β��������ֵ��ǰһ���ڵ��

					temp_node->pNext=pnode,pnode->pNext=0;
				else
				{
					if(tempint<0&&temp_node->pNext!=0)         //�������в���ӽڵ�  
						pnode->pNext=temp_node,current_ptr->pNext=pnode;

				      else 
						  if(tempint >=0&&temp_node->pNext==0)        //������β����ӽڵ�
							  temp_node->pNext=pnode,pnode->pNext=0;
				}
			}	
		 }					 
  }
}  // ���뺯������ 

int CList::load_list_from_file()     // 	�������ļ�FRIENDS.TXT�ж�ȡ�����ؽ���������
{
	current_ptr=pHead;
	//fstream infile("FRIENDS.TXT",ios::in|ios::nocreate);
	fstream infile("FRIENDS.TXT",ios::in);
    CNode *new_rec_ptr;
    int end_loop = 0;
    if (!!infile)                // ����ɹ����ļ�
	{                           // ���ļ���������
		cout<<"�ѳɹ���\"FRIENDS.txt\"�ļ�!\n";
		char dd[20];
		char tt[20];
		char LName[20];
	    char FName[20];
        char Number[20];
        for(;end_loop==0 ;)
		{
			new_rec_ptr=new CNode;  
		    if(new_rec_ptr->GetData()==NULL)
			{
				end_loop=1;
			    continue;
			}
		    if(new_rec_ptr != NULL) // ȷ��new_rec_ptrָ�벻ΪNULL
			{
				if(!infile.eof())   //����ļ��������ݿɶ���
				{
					infile.getline(LName,20);             
		            infile.getline(FName,20);
				    infile.getline(Number,20);
					infile.getline(dd,20);
					infile.getline(tt,20);
					if(strlen(LName) != 0 &&strcmp(LName, "END OF FILE") != 0)//������ϵĳ��Ȳ�Ϊ��
					{
						if(new_rec_ptr->GetData()!=NULL)
                        new_rec_ptr->GetData()->SetRecord(LName,FName,Number,dd,tt);
					    if(pHead==NULL)               //��ͷָ��Ϊ��
						    AddNode(new_rec_ptr);
					    else
                            Insert(new_rec_ptr);         
					    strcpy(LName,"");
					    strcpy(FName,"");
					    strcpy(Number,"");
						strcpy(dd,"");
						strcpy(tt,"");
					}
			        else                                          
						end_loop = 1;					
				}
		        else  
				{ 
			       cout << "�������¼��!\n";
                   end_loop = 1;
				}
			}
		}
	    return 1;
	    infile.close(); // �ر��ļ�
	}
    else  // ���ļ�ʧ��
	{
	     cout << "���ļ�ʧ��!��ȷ���ѽ���\"FRIENDS.txt\"�ļ�!\n";
         return 0;
	}
} // �ļ�¼�뺯������ 

void CList::delete_record()
{
	system("cls");
	char search_string[20];
	CNode *cnode;
	cnode = NULL;     
	current_ptr = pHead;  // ������ͷ����ʼ                         
	cin.ignore(20,'\n');
	cout << "\n��������ɾ����¼������(һ��ֻ��ɾ��һ����¼):\n ";
	cin.getline(search_string,20);
	cin.ignore(20,'\n');
    while((current_ptr != NULL) && current_ptr->GetData()!=NULL&&
	   strncmp(search_string,current_ptr->GetData()->GetLName(),strlen(search_string)) !=0&&
	   strncmp(search_string,current_ptr->GetData()->GetLName(),strlen(current_ptr->GetData()->GetLName())) !=0)
	{
		cnode = current_ptr;      
		current_ptr = current_ptr->pNext; 
	}                                 
   if(current_ptr != NULL&&current_ptr->GetData()!=NULL) 
	{                      
		cout << "\n���ϵļ�¼:\n";
		cout << current_ptr->GetData()->GetLName() 
			<< current_ptr->GetData()->GetFName()<< endl;
         
		cout << current_ptr->GetData()->GetNumber() << endl;
		if(verify_delete()) 
		{                               
			DeleteNode(cnode);     
			cout << "\n��ɾ����¼!\n";  
		}
		else                            
		{
			cout << "\n��û��ɾ���κμ�¼!\n";
		}
   }
   else 
   {
		cout << "\n�Ҳ����ڵ㣬��û��ɾ���κμ�¼!\n";
   }
    system("cls");
    system("date /t");
    system("time /t");
} //ɾ����¼��������
 
CNode *CList::DeleteNode(CNode *cnode)
{
	system("date /t");
	system("time /t");
	if(current_ptr == pHead)  
	{                           
		current_ptr = pHead;  
		if(pHead->pNext != NULL)                            
			pHead = current_ptr->pNext;   
	} 
   else                        
	{                           
		if(current_ptr->pNext == NULL)       
		{                                  
			delete current_ptr; 
			cnode->pNext = NULL; 
			current_ptr = pHead; 
		}
		else                       
		{                                          
			cnode->pNext = current_ptr->pNext;			
		}                        
   } 
   return current_ptr;
}                       //ɾ���ӵ㺯������
                               

void CList::DeleteList()
{
	CNode*temp_ptr;  
    current_ptr=pHead;  
    do    
	{
		temp_ptr=current_ptr->GetpNext();
		if(current_ptr->GetpNext()==NULL)
			 current_ptr=NULL;	 
      else
		  current_ptr=temp_ptr;                                      
	}while(temp_ptr!= NULL);       
}                              // ɾ������������
 
void CList::ShowList()
{
	char fullname[30];
	char date_time[30];
	current_ptr = pHead;   
    if(current_ptr != NULL&&current_ptr->GetData()!=NULL)
	{
		cout << endl;
        cout << "����:                     �绰����:                       ¼��ʱ�������:      \n";
        cout << "-------------------------------------------------------------------------------\n";
        do
		{
			strcpy(fullname,""); // ��� fullname������.
            strcat(fullname, current_ptr->GetData()->GetLName());                                 
            strcat(fullname, current_ptr->GetData()->GetFName());
			strcpy(date_time,current_ptr->GetData()->GetDate());
			strcat(date_time,current_ptr->GetData()->GetTime());
            cout.setf(ios::left);
            cout << setw(30) << fullname;	    
            cout << setw(20) << current_ptr->GetData()->GetNumber()<<setw(30)<<date_time<< endl;
            current_ptr = current_ptr->pNext;                  
	        cout <<  endl;
		} 
		while(current_ptr != NULL); 
		cout << "Press Enter to continue \n";
	    cin.get(pause);
	    cin.ignore(1,pause);  
	}
  else 
  {
    cout << "\n��δ��������!\n";
  }
} // ��ʾ��Ϣ��������

int CList::verify_delete()
{
	char YesNo;
  cout << "\nAre you sure (Y/N) ";
  cin >> YesNo;
  if((YesNo == 'Y') || (YesNo == 'y'))
   {
    return(1); 
   }
  else
   {
    return(0); 
   }
 } // ɾ��ȷ�Ϻ���
 
void  CList::write_list_to_file()
{
	fstream outfile;
	//outfile.open("FRIENDS.TXT",ios::out|ios::nocreate);
	outfile.open("FRIENDS.TXT",ios::out);
    if (!!outfile)  
	{            
		current_ptr = pHead;  
        if(pHead != NULL&&current_ptr->GetData()!=0)  
		{                    
           do    
		   {

              outfile<<setiosflags(ios::left)<<current_ptr->GetData()->GetLName()<<'\n';
              outfile<<setiosflags(ios::left)<<current_ptr->GetData()->GetFName()<<'\n';
              outfile<<setiosflags(ios::left)<<current_ptr->GetData()->GetNumber()<<'\n';
			  outfile<<setiosflags(ios::left)<<current_ptr->GetData()->GetDate()<<'\n';
			  outfile<<setiosflags(ios::left)<<current_ptr->GetData()->GetTime()<<'\n';
              current_ptr = current_ptr->pNext;  
		   } while(current_ptr != NULL); 
		}
        outfile.close(); 
	}
    else 
	   {
          cout << "û�д��ļ�!\n";
	   }
} //�ļ�¼�뺯������

CNode * CList::LookUp(CTelRecord &ctelrecord)
{
	int i(0);
	system("cls");
	char search_string[20];  
	CNode *cc=current_ptr;
    current_ptr = pHead;  
    strcpy(search_string,ctelrecord.GetLName());   
	while(current_ptr!=NULL)
	{
		if(current_ptr->GetData()->LookChar(search_string)!=0)
		
		{
			if (i==0)
				cout<<"����:-----------------------------------"<<"�绰����:--------------\n"; 
			current_ptr->ShowNode();
			i++;
		}
		
		current_ptr=current_ptr->pNext;
	}
	if(i)
		cout<<"���!\n";
	else 
		cout<<"�Ҳ�����Ҫ�ҵļ�¼!\n";
	current_ptr=cc;
	return current_ptr;
}//���ܲ��Һ�������

void CList::help_me()
{
	help:
	int choice2;
	system("cls");
	cout << "��ӭ��������Ϣ������ѡ������Ҫ�İ���!\n";
	cout << "1: �ҵļ�¼��ô��?\n";
	cout << "2: ��������¼?\n";
	cout << "3: ʲôʱ����ʾ���¼�¼?\n";
	cout << "4: ����ʾ����ʲô?\n";
	cout << "5: �˳�!\n";
	cin >>  choice2;
	switch(choice2) //����
	{
	case 1:
		cout << "ȷ����һ��FRIENDS���ļ�!\n";
		cout << "�����û����ʧ����������ΪFRIENDS!\n";
		cout << "���س�������!\n";
		pause=getch();
		system("cls");
		goto help;
		break;
	case 2:
		cout << "ɾ���ļ�����!\n";
		cout << "���س�������!\n";
		pause=getch();
		system("cls");
		goto help;
		break;
	case 3:
		cout << "�ȵ�����ʱ��ɣ�����Ƚ�æ~~~\n";
		cout << "���س�������!\n";
		pause=getch();
		system("cls");
		goto help;
		break;
	case 4:
		cout << "����������¹���:\n";
		cout << "1.������������\n";
		cout << "2.һ��ɾ�������¼\n";
		cout << "3.�绰�����ܹ���\n";
		cout << "���س�������!\n";
		pause=getch();
		system("cls");
		goto help;
		break;
	default:
		cout << "���س����˳�!\n";
		cout << "���س�������!\n";
		break;
	}
} //������������

CNode *CList::GetListEnd()
{
	current_ptr = pHead;  
    while(current_ptr!= NULL)
	{                             
    current_ptr = current_ptr->pNext;
	}
	CNode * current_ptr_end=current_ptr;
	return current_ptr_end;
} 

void CList::handle_choice(int choice)
{
	switch(choice) 
	{
	case 1: 
		{
	    char ch;
	    system("cls");
		do{  
			CNode *pnode;
		    pnode=new CNode;
		    char first_name[20];
	    	char last_name[20];
	    	char phone_num[20];
			char dd[20];
			char tt[20];
    		
	    	if(pnode!=NULL)
			
			{
				CTelRecord *ctelrecord=new CTelRecord;
		        cin.ignore(20,'\n');             
				cout << "������Ҫ��ӵ�����:\n ";
                cin.get(first_name,20);
                cin.ignore(20,'\n');
      	        cout << "������Ҫ��ӵ�����:\n ";
                cin.get(last_name,20);
                cin.ignore(20,'\n');
                cout << "������Ҫ��ӵĵ绰����:\n ";
                cin.get(phone_num,20);
                cin.ignore(20,'\n');
				system("date /t>d:\\translate.txt");
				//fstream trf("d:\\translate.txt",ios::in|ios::nocreate);
				fstream trf("d:\\translate.txt",ios::in);
				trf.getline(dd,20);
				trf.close();
				system("time /t>d:\\translate.txt");
			    //trf.open("d:\\translate.txt",ios::in|ios::nocreate);
			    trf.open("d:\\translate.txt",ios::in);
				trf.getline(tt,20);
				trf.close();
		  	    ctelrecord->SetRecord(last_name,first_name,phone_num,dd,tt);
	   		    pnode->InputData(ctelrecord);
				if(pHead!=NULL)
					Insert(pnode);
				else 
					AddNode(pnode);
				system("date /t");
                system("time /t");
				cout<<"��Ҫ������?(y/n)\n";
				cin.get(ch);
				system("cls");
			} 
			else cout<<"you can not add a node!\n";
		}while(ch=='y'||ch=='Y');
		}
        break;
    case 2: 
		system("cls");
		system("date /t");
        system("time /t");
        ShowList();                      
        break; 
	case 3:
		char ch;
		do{
			char lastname[20],firstname[20];
            CTelRecord ctelrecord;
		    cout<<"��������Ҫ���ҵ�����:\n";
	        cin.getline(lastname,20);
		    cin.ignore(20,'\n');
			cout<<"��������Ҫ���ҵ�����:\n";
	    	cin.getline(firstname,20);
	    	cin.ignore(20,'\n');
            ctelrecord.SetRecord(lastname,firstname," "," " ," ");
	    	current_ptr=pHead;
	    	while(current_ptr!=NULL&&current_ptr->GetData()->Compare(ctelrecord)!=0)
			current_ptr=current_ptr->pNext;
	    	if(current_ptr==NULL)
				cout<<"�Բ���,û���ҵ���Ҫ�ҵļ�¼.\n";
	    	else
			{
				cout<<"��Ҫ�ҵļ�¼��\n";
			    current_ptr->ShowNode();
			}
			cout<<"�����ҵ�ʱ���ǣ�\n";
			system("date /t");
            system("time /t");
			cout<<"��Ҫ������(y/n)\n";
			cin.get(ch);
		}while(ch=='y'||ch=='Y');
		system("cls");
		break;

	case 4:                            
		{                            
			system("cls");
		    char LName[20];
            cout<<"��������Ҫ���ҵ���:\n";
			cin.get();
            cin.getline(LName,20);
	    	cin.ignore(20,'\n');
			cout<<"����ǰ���ҵ�ʱ���ǣ�\n";
			system("date /t");
            system("time /t");
	    	CTelRecord ctelrecord(LName,"","","","");
	    	LookUp(ctelrecord);
		}
        break; 
	
    case 5:  
    delete_record();
    break;	 
	case 6:
		{
		   fstream trf;
		   do 
		   {
			  char ch,lastname[20],firstname[20],dd[20],tt[20];
			  int ch1;
		   	CTelRecord ctelrecord;
		    cout<<"��������Ҫ�޸ĵ�����:\n";
	        cin.getline(lastname,20);
		    cin.ignore(20,'\n');
			cout<<"��������Ҫ�޸ĵ�����:\n";
	    	cin.getline(firstname,20);
	    	cin.ignore(20,'\n');
            ctelrecord.SetRecord(lastname,firstname," ","","");
	    	current_ptr=pHead;
	    	while(current_ptr!=NULL&&current_ptr->GetData()->Compare(ctelrecord)!=0)
			current_ptr=current_ptr->pNext;
	    	if(current_ptr==NULL)
				cout<<"�Բ���û���ҵ���Ҫ�ҵļ�¼!\n";
	    	else
			{
				cout<<"��Ҫ�ҵļ�¼:\n";
			    current_ptr->ShowNode();
			    cout<<"��ѡ����Ҫ�޸ĵ���Ŀ:\n";
			    cout<<"---1---�޸ĵ绰����!\n";
			    cout<<"---2---�޸������͵绰����!(����Ҫ�Ȱ������¼ɾ���ٽ��в���)\n";
		    	cin>>ch1;
			    switch(ch1)
				{
			    case 1:
				char number[20];
				cout<<"���������µĵ绰����:\n";
				cin.get();
				cin.getline(number,20);
				current_ptr->GetData()->Modify(number);
				system("date /t>translate.txt");
				//trf.open("d:\\translate.txt",ios::in|ios::nocreate);     
				trf.open("d:\\translate.txt",ios::in); 
				trf.getline(dd,20);
				trf.close();
				system("time /t>d:\\translate.txt");
				//trf.open("d:\\translate.txt",ios::in|ios::nocreate);
				trf.open("d:\\translate.txt",ios::in);
				trf.getline(tt,20);
				trf.close();
                current_ptr->GetData()->SetDate_Time(dd,tt);
				break;
			case 2:
				if(verify_delete())
				{
					DeleteNode(current_ptr);
				    CNode *pnode;
		            pnode=new CNode;
		            char first_name[20];
	    	        char last_name[20];
	    	        char phone_num[20];
    		
	    	       if(pnode!=NULL)
			
				   {
			    	    CTelRecord *ctelrecord=new CTelRecord;
			            system("cls");
		                cin.ignore(20,'\n');             
			        	cout << "������Ҫ��ӵ�����:\n ";
                        cin.get(first_name,20);
                        cin.ignore(20,'\n');
      	                cout << "������Ҫ��ӵ�����:\n ";
                        cin.get(last_name,20);
                        cin.ignore(20,'\n');
                        cout << "������Ҫ��ӵĵ绰����:\n ";
                        cin.get(phone_num,20);
                        cin.ignore(20,'\n');
						system("date /t>d:\\translate.txt");
						//trf.open("d:\\translate.txt",ios::in|ios::nocreate);
						trf.open("d:\\translate.txt",ios::in);
				        trf.getline(dd,20);
						trf.close();
				        system("time /t>d:\\translate.txt");
						//trf.open("d:\\translate.txt",ios::in|ios::nocreate);
						trf.open("d:\\translate.txt",ios::in);
				        trf.getline(tt,20);
						trf.close();
		  	            ctelrecord->SetRecord(last_name,first_name,phone_num,dd,tt);
	   		            pnode->InputData(ctelrecord);
			        	if(pHead!=NULL)
						    Insert(pnode);
				        else 
				    	    AddNode(pnode);
				   }
				   cout<<"���޸���һ����¼!\n";
				}
				else
					cout<<"��û���޸��κμ�¼!\n";
				break;
			default:
				cout<<"�������˴����ѡ��!\n";
				break;
				}
			cout<<"���޸ļ�¼��ʱ����:";cout<<endl;
		    system("date /t");
            system("time /t");
			cout<<"��Ҫ������?(y/n)\n";
			cin.get(ch);
			}
		   }while(ch=='y'||ch=='Y');
		   trf.close();
		}
		break;

	case 7:  
    help_me();
	break;
	case 0:  
	cout<<"лл�����ٵ绰������ϵͳ!�ټ�!!!\n";
	system("date /t");
    system("time /t");
    if(pHead != NULL)   // �������ͷ��Ϊ��
	{ 
		write_list_to_file();
		DeleteList(); 
	}
    break;
	default : // ��������������
		cout <<"ѡ�����!\n"; 
    break;
	}
} // ѡ����������

int main()
{
	int choice;
	CNode node;
	CList ClassNumberList;
	cout<<"---------------------------��ӭʹ�õ绰������ϵͳ-----------------------------!\n";
	cout<<"--------------------------------���س�������-----------------------------------\n";
	cin.get(pause);
	cout<<"���ߣ����������ųۡ���������ʫȻ������̨\n";
    cout<<"ѧ�ţ�20178314037\n";
    cout<<"�༶����Ϣ��ȫ1��\n";
    cout<<"--------------------------------���س�������-----------------------------------\n";
	cin.get(pause);
	system("cls"); //ִ��ϵͳ���cls-����
    ClassNumberList.load_list_from_file(); // ���ļ���������
    current_ptr=ClassNumberList.GetListEnd();
	do
	{  
		system("cls");//   ���˵���ʾ
		system("date /t");
		system("time /t");
		cout<< "--------------------------------1 - ��Ӽ�¼!-----------------------------------\n";
		cout<< "--------------------------------2 - ��ʾ��¼!-----------------------------------\n";
		cout<< "--------------------------------3 - ����ȫ������!-------------------------------\n";
		cout<< "--------------------------------4 - ���ܲ���!-----------------------------------\n";
		cout<< "--------------------------------5 - ɾ����¼!-----------------------------------\n";
		cout<< "--------------------------------6 - �޸ļ�¼!-----------------------------------\n";
		cout<< "--------------------------------7 - ����!---------------------------------------\n";
		cout<< "--------------------------------0 - �˳�����!-----------------------------------\n";
		cout<<"����������ѡ��:\n";
		cin>>choice;
        ClassNumberList.handle_choice(choice);
	}
	while(choice!=0);
	return 0;
}
