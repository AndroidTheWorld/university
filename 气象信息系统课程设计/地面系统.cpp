#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int str2int(char *ch,int k,int n);
void dmdisp(char *ch);  

void logo(){
	system("cls");
	printf(
	"=============================================\n"
	"	       ������Ϣ����ϵͳ \n"
	"=============================================\n" 
	);
}

int main() {
	int year,month,day,hour,n,p;
	char station[6],name[]="AAXX0000.T00",ch[400];
	char file[21]="./data/";
	FILE *fp;

	while (1){
		logo();
		printf("��������,��,��[YYYY MM DD]:\n");
		scanf("%d%d%d",&year,&month,&day);
		name[4]='0'+month/10;
		name[5]='0'+month%10;
		name[6]='0'+day/10;
		name[7]='0'+day%10;
	
		printf("�������������ʱ[0,3,6,9,12,15,18,21]:");
		scanf("%d",&hour);
		name[10]='0'+hour/10;
		name[11]='0'+hour%10;
	 
		printf("������̨վ��[Ĭ���Ͼ�Ϊ58238]:");
		scanf("%s",station);
		
		strcat(file,name); 
		if (fp=fopen(file,"rt")) {
			fgets(ch,80,fp);
			fgets(ch,80,fp);
			if (p==1) fgets(ch,80,fp);
			while(!feof(fp)) {
				fgets(ch,80,fp);
				n=strlen(ch);
				while (n<300 && ch[n-1] != '=' && !feof(fp)) {
					ch[n]= ' ';
	
					fgets(&ch[n+1],80,fp);
					n=strlen(ch)-1;
				}
				if (!strncmp(&ch[p-1],station,5)) {
					dmdisp(ch);
					p=0;
					break;
				}
			}
			fclose(fp);
			if (p!=0) printf("%s--̨վδ�ҵ��������������ݣ�\n",station);
		} else  printf("%s--�ļ������ڣ������������ݣ�\n" ,name);
		system("pause");
	}
	
}

int str2int(char *ch,int k,int n) {
	int i,m=0;
	for(i=0; i<n; i++) {
		if (ch[k+i]<'0' || ch[k+i]>'9') {
			m=-1;
			break;
		}
		m=m*10+ch[k+i]-'0';
	}
	return m;
}

void dmdisp(char *ch) {
	int i;
	long int vv;
	int dd,ff,x,y,ww,m,n;
	printf("\n==============================");
	printf("[̨վ��]:");
	for(i=0; i<5; i++)
		printf("%c",ch[i]);
	printf("\n\t�Ʋ�߶�\t");
	switch(ch[8]) {
		case '0' :
			printf("<50��");
			break;
		case '1' :
			printf("50-<100��");
			break;
		case '2' :
			printf("100-<200��");
			break;
		case '3' :
			printf("200-<300��");
			break;
		case '4' :
			printf("300-<600��");
			break;
		case '5' :
			printf("600-<1000��");
			break;
		case '6' :
			printf("1000-<1500��");
			break;
		case '7' :
			printf("1500-<2000��");
			break;
		case '8' :
			printf("2000-<2500��");
			break;
		case '9' :
			printf(">=2500��");
			break;
		default:
			printf("ȱ��");
	}
	printf("\n\t��Ч�ܼ���\t");
	vv=str2int(ch,9,2);
	if (vv==0)
		printf("<100��");
	else if (vv<=50) {
		vv=vv*100;
		printf("%d��",vv);
	} else if(vv<=55)
		printf("����");
	else if (vv<=79) {
		vv=vv-50;
		printf("%dǧ��",vv);
	} else if (vv==80)
		printf(">=30ǧ��");
	else if (vv<=88) {
		vv=(vv-80)*5+30;
		printf("%dǧ��",vv);
	} else if (vv==89)
		printf(">70ǧ��");
	else if (vv==90)
		printf("<50��");
	else if (vv==91)
		printf("50��");
	else if (vv==92)
		printf("200��");
	else if (vv==93)
		printf("500��");
	else if (vv==94)
		printf("1ǧ��");
	else if (vv==95)
		printf("2ǧ��");
	else if (vv==96)
		printf("4ǧ��");
	else if (vv==97)
		printf("10ǧ��");
	else if (vv==98)
		printf("20ǧ��");
	else if (vv==99)
		printf(">=50ǧ��");
	printf("\n\t������\t\t");
	switch(ch[12]) {
		case '0' :
			printf("����");
			break;
		case '1' :
			printf("1");
			break;
		case '2' :
			printf("2-3");
			break;
		case '3' :
			printf("4");
			break;
		case '4' :
			printf("5");
			break;
		case '5' :
			printf("6");
			break;
		case '6' :
			printf("7-8");
			break;
		case '7' :
			printf("9");
			break;
		case '8' :
			printf("10");
			break;
		case '9' :
			printf("����");
			break;
		default:
			printf("ȱ��");
	}
	printf("\n\t����\t\t");
	dd=str2int(ch,13,2);
	m=dd%10;
	n=dd/10;
	if(m<5)
		dd=n*10;
	else
		dd=(n+1)*10;
	if (dd==0)
		printf("��ֹ��");
	else {
		dd=dd*10;
		printf("����%d��",dd);
	}
	printf("\n\t����\t\t");
	ff=str2int(ch,15,2);
	m=ff%10;
	n=ff/10;
	if(m<5)
		ff=n*10;
	else
		ff=(n+1)*10;
	ff=ff/10*10;
	printf("%d��/��",dd);
	n=18;
	if(ch[n]=='1') {
		printf("\n\t��������\t");
		switch(ch[n+1]) {
			case'0':
				break;
			case'1':
				printf("-");
				break;
			default:
				printf("���ݳ���");
		}
		x=str2int(ch,n+2,2);
		y=str2int(ch,n+4,1);
		printf("%d.%d��",x, y);
		n+=6;
	}
	
	if(ch[n]=='2') {
		printf("\n\t¶���¶�\t");
		switch(ch[n+1]) {
			case'0':
				break;
			case'1':
				printf("-");
				break;
			default:
				printf("���ݳ���");
		}
		x=str2int(ch,n+2,2);
		y=str2int(ch,n+4,1);
		printf("%d.%d��",x,y);
		n+=6;
	}
	
	if(ch[n]=='3') {
		printf("\n\t��ѹ����\t");
		x=str2int(ch,n+1,3);
		y=str2int(ch,n+4,1);
		printf("%d.%d����",x,y);
		n+=6;
	}
	
	if(ch[n]=='4') {
		printf("\n\t��ƽ����ѹ\t");
		x=str2int(ch,n+1,3);
		y=str2int(ch,n+4,1);
		if (x<5)
			x=x+10;
		printf("%d.%d����",x,y);
		n+=6;
	}
	
	if(ch[n]=='5') {
		printf("\n\t��ȥ��Сʱ��ѹ�仯��\t");
		if (ch[n+1]>4)
			printf("����");
		else  printf("�½�");
		x=str2int(ch,n+2,2);
		y=str2int(ch,n+4,1);
		printf("%d.%d����",x,y);
		n+=6;
	}
	
	if(ch[n]=='6') {
		printf("\n\t��ȥ��Сʱ��ˮ\t\t");
		x=str2int(ch,n+1,3);
		if (x==0)
			printf("��ˮ����");
		else if (x<=998)
			printf("��ˮ��%d����",x);
		else if(x==990)
			printf("��ˮ��΢��");
		else if(x<=999)
			printf("��ˮ��%d����",(x-990)/10);
		else printf("��ˮ����");
		n+=6;
	}
	
	if(ch[n]=='7') {
		printf("\n\n\t�۲�ʱ�͹�ȥ��������������:");
		ww=str2int(ch,n+1,2);
		if ((ww==00)||(ww==01)||(ww==02)||(ww==03))
			printf("��");
		else if (ww==4)
			printf("��");
		else if (ww==5)
			printf("��");
		else if (ww<=9)
			printf("ɳ��");
		else if (ww<=12)
			printf("�ᡢǳ��");
		else if (ww==13)
			printf("����");
		else if (ww<=16)
			printf("��ˮ");
		else if (ww==17)
			printf("�ױ�");
		else if (ww==18)
			printf("�");
		else if (ww==19)
			printf("����");
		else if (ww==20)
			printf("ëë��");
		else if (ww==21)
			printf("��");
		else if (ww==22)
			printf("ѩ����ѩ");
		else if (ww==23)
			printf("���ѩ");
		else if (ww==24)
			printf("�ꡢ��ڡ");
		else if (ww==25)
			printf("��ѩ");
		else if (ww==26)
			printf("�����ѩ");
		else if (ww==27)
			printf("����");
		else if (ww==28)
			printf("����");
		else if (ww==29)
			printf("�ױ�");
		else if (ww<=35)
			printf("ɳ����");
		else if (ww<=39)
			printf("��ѩ");
		else if (ww<=49)
			printf("Ũ��");
		else if (ww<=59)
			printf("Ũëë��");
		else if (ww<=61)
			printf("С��");
		else if (ww<=63)
			printf("����");
		else if (ww<=65)
			printf("����");
		else if (ww<=67)
			printf("��ڡ");
		else if (ww<=69)
			printf("���꽵ˮ");
		else if (ww<=71)
			printf("Сѩ");
		else if (ww<=73)
			printf("��ѩ");
		else if (ww<=75)
			printf("��ѩ");
		else if (ww==76)
			printf("����");
		else if (ww==77)
			printf("��ѩ");
		else if (ww==78)
			printf("ѩ��");
		else if (ww==79)
			printf("����");
		else if (ww==80)
			printf("С����");
		else if (ww==81)
			printf("������");
		else if (ww==82)
			printf("������");
		else if (ww==83)
			printf("С�������ѩ");
		else if (ww==84)
			printf("���������ѩ");
		else if (ww==85)
			printf("С��ѩ");
		else if (ww==86)
			printf("�л����ѩ");
		else if (ww==87)
			printf("С������");
		else if (ww==88)
			printf("�л��������");
		else if (ww==89)
			printf("�����");
		else if (ww==90)
			printf("�л�ǿ����");
		else if (ww==91)
			printf("�ױ���С��");
		else if (ww==92)
			printf("�ױ�������");
		else if (ww==93)
			printf("�ױ���Сѩ");
		else if (ww==94)
			printf("�ױ����ѩ");
		else if (ww==95)
			printf("С�ױ�����ѩ");
		else if (ww==96)
			printf("С�ױ������");
		else if (ww==97)
			printf("���ױ�����ѩ");
		else if (ww==98)
			printf("�ױ���ɳ����");
		else if (ww==99)
			printf("���ױ������");
		printf("\n\t��Ҫ��ȥ��Сʱ��������:");
		switch(ch[n+3]) {
			case'0':
				printf("��");
				break;
			case'3':
				printf("ɳ����");
				break;
			case'4':
				printf("��");
				break;
			case'5':
				printf("ëë��");
				break;
			case'6':
				printf("��������");
				break;
			case'7':
				printf("���彵ˮ");
				break;
			case'8':
				printf("����");
				break;
			case'9':
				printf("�ױ�");
				break;
			default:
				printf("���ݴ���");
		}
		printf("\n\t��Ҫ��ȥ��Сʱ��������:");
		switch(ch[n+4]) {
			case'0':
				printf("��");
				break;
			case'3':
				printf("ɳ����");
				break;
			case'4':
				printf("��");
				break;
			case'5':
				printf("ëë��");
				break;
			case'6':
				printf("��������");
				break;
			case'7':
				printf("���彵ˮ");
				break;
			case'8':
				printf("����");
				break;
			case'9':
				printf("�ױ�");
				break;
			default:
				printf("���ݴ���");
		}
		n+=6;
	}
	
	if(ch[n]=='8') {
		printf("\n\t�Ƶ�����:");
		switch(ch[n+1]) {
			case '0' :
				printf("����");
				break;
			case '1' :
				printf("������Ϊ1");
				break;
			case '2' :
				printf("�Ƶ׸߶�������Ϊ2-3");
				break;
			case '3' :
				printf("������Ϊ4");
				break;
			case '4' :
				printf("������Ϊ5");
				break;
			case '5' :
				printf("������Ϊ6");
				break;
			case '6' :
				printf("������Ϊ7-8");
				break;
			case '7' :
				printf("������Ϊ9");
				break;
			case '8' :
				printf("������Ϊ10");
				break;
			case '9' :
				printf("����");
				break;
			default:
				printf("ȱ��");
		}
		switch(ch[n+2]) {
			case '0' :
				printf("�޵���");
				break;
			case '1' :
				printf("����״Ϊ������");
				break;
			case '2' :
				printf("����״ΪŨ����");
				break;
			case '3' :
				printf("����״Ϊ������");
				break;
			case '4' :
				printf("����״Ϊ������");
				break;
			case '5' :
				printf("����״Ϊ������");
				break;
			case '6' :
				printf("����״Ϊ������");
				break;
			case '7' :
				printf("����״Ϊ������");
				break;
			case '8' :
				printf("����״Ϊ����");
				break;
			case '9' :
				printf("����״Ϊ�׻���");
				break;
			default:
				printf("���ݴ���");
		}
		switch(ch[n+3]) {
			case '0' :
				printf("������");
				break;
			case '1' :
				printf("����״Ϊ�߲���");
				break;
			case '2' :
				printf("����״Ϊ�����");
				break;
			case '3' :
				printf("����״Ϊ�߻���");
				break;
			case '4' :
				printf("����״Ϊ��״��");
				break;
			case '5' :
				printf("����״Ϊ�����");
				break;
			case '6' :
				printf("����״Ϊ������");
				break;
			case '7' :
				printf("����״Ϊ������");
				break;
			case '8' :
				printf("����״Ϊ����");
				break;
			case '9' :
				printf("����״Ϊɢ����");
				break;
			default:
				printf("���ݴ���");
		}
		switch(ch[n+4]) {
			case '0' :
				printf("�޵���");
				break;
			case '1' :
				printf("����״Ϊë����");
				break;
			case '2' :
				printf("����״Ϊ�ܾ���");
				break;
			case '3' :
				printf("����״Ϊα����");
				break;
			case '4' :
				printf("����״Ϊ������");
				break;
			case '5' :
				printf("����״Ϊ����");
				break;
			case '6' :
				printf("����״Ϊ������");
				break;
			case '7' :
				printf("����״Ϊ�����");
				break;
			case '8' :
				printf("����״Ϊ����");
				break;
			case '9' :
				printf("����״Ϊ�����");
				break;
			default:
				printf("���ݴ���");
		}
		n+=6;
	}
	
	if(ch[n]=='9') {
		printf("\n\tʵ�ʹ۲�ʱ��:");
		x=str2int(ch,n+1,2);
		y=str2int(ch,n+3,2);
		printf("%dСʱ%d����",x,y);
		n+=6;
	}
	printf("\n\t");

}


