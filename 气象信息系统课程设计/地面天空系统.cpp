#include <stdio.h>
#include <stdio.h>
#include <string.h>
int str2int(char *ch,int k,int n);
void dmdisp(char *ch); //  ��ch���е�������Ĺ��ܺ�����ѧ���������
void updisp(char *ch); //  ��ch���и߿�����Ĺ��ܺ�����ѧ���������
void main(void) {
	int year,month,day,hour,n,p;
	char station[6],name[]="AAXX0000.T00",ch[400];
	FILE *fp;

	printf("�������ꡢ�¡���\n");
	scanf("%d%d%d",&year,&month,&day);
	name[4]='0'+month/10;
	name[5]='0'+month%10;
	name[6]='0'+day/10;
	name[7]='0'+day%10;

	printf("��ѡ��1-���棻2-�߿�\n");
	scanf("%d",&p);
	if (p!=1) {
		name[0]='T';
		name[1]='T';
		name[2]='A';
		name[3]='A';
		p=13;
	}

	if (p!=1) printf("������߿�����ʱ����ѡ��0��6��12��18\n");
	else printf("�������������ʱ����ѡ��0��3��6��9��12��15��18��21\n");
	scanf("%d",&hour);
	name[10]='0'+hour/10;
	name[11]='0'+hour%10;

	printf("������̨վ�ţ��Ͼ�Ϊ58238\n");
	scanf("%s",station);

	if (fp=fopen(name,"rt")) {
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
				if (p==1) dmdisp(ch);
				else updisp(ch);
				p=0;
				break;
			}
		}
		fclose(fp);
		if (p!=0) printf("%s--̨վδ�ҵ������飡����\n",station);
	} else  printf("%s--�ļ������ڣ����飡����\n" ,name);
}
//����Ϊn���ַ���ת��Ϊ����ֵ�����ں��з������ַ����򷵻ظ�1��
//k���ַ�������ʼλ��
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
//���ַ�������ch�������룬����������Ҫ�ص�ֵ������ʾ��
void dmdisp(char *ch) {
	int i;
	long int vv;
	int dd,ff,x,y,ww,m,n;
//  ��ch�������룬��ѧ���������
	//puts(ch);  // ��ʾ�������ַ�����������
	printf("̨վ�ţ�");
	for(i=0; i<5; i++)
		printf("%c",ch[i]);
	printf("\n");
	switch(ch[8]) {
		case '0' :
			printf("�Ƶ׸߶�<50��");
			break;
		case '1' :
			printf("�Ƶ׸߶�50-<100��");
			break;
		case '2' :
			printf("�Ƶ׸߶�100-<200��");
			break;
		case '3' :
			printf("�Ƶ׸߶�200-<300��");
			break;
		case '4' :
			printf("�Ƶ׸߶�300-<600��");
			break;
		case '5' :
			printf("�Ƶ׸߶�600-<1000��");
			break;
		case '6' :
			printf("�Ƶ׸߶�1000-<1500��");
			break;
		case '7' :
			printf("�Ƶ׸߶�1500-<2000��");
			break;
		case '8' :
			printf("�Ƶ׸߶�2000-<2500��");
			break;
		case '9' :
			printf("�Ƶ׸߶�>=2500��");
			break;
		default:
			printf("ȱ��");
	}
	printf("\n");
	vv=str2int(ch,9,2);
	if (vv==0)
		printf("��Ч�ܼ���<100��");
	else if (vv<=50) {
		vv=vv*100;
		printf("��Ч�ܼ���%d��",vv);
	} else if(vv<=55)
		printf("����");
	else if (vv<=79) {
		vv=vv-50;
		printf("��Ч�ܼ���%dǧ��",vv);
	} else if (vv==80)
		printf("��Ч�ܼ���>=30ǧ��");
	else if (vv<=88) {
		vv=(vv-80)*5+30;
		printf("��Ч�ܼ���%dqǧ��",vv);
	} else if (vv==89)
		printf("��Ч�ܼ���>70ǧ��");
	else if (vv==90)
		printf("��Ч�ܼ���<50��");
	else if (vv==91)
		printf("��Ч�ܼ���Ϊ50��");
	else if (vv==92)
		printf("��Ч�ܼ���Ϊ200��");
	else if (vv==93)
		printf("��Ч�ܼ���Ϊ500��");
	else if (vv==94)
		printf("��Ч�ܼ���Ϊ1ǧ��");
	else if (vv==95)
		printf("��Ч�ܼ���Ϊ2ǧ��");
	else if (vv==96)
		printf("��Ч�ܼ���Ϊ4ǧ��");
	else if (vv==97)
		printf("��Ч�ܼ���Ϊ10ǧ��");
	else if (vv==98)
		printf("��Ч�ܼ���Ϊ20ǧ��");
	else if (vv==99)
		printf("��Ч�ܼ���>=50ǧ��");
	printf("\n");
	switch(ch[12]) {
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
	printf("\n");
	dd=str2int(ch,13,2);
	m=dd%10;
	n=dd/10;
	if(m<5)
		dd=n*10;
	else
		dd=(n+1)*10;
	if (dd==0)
		printf("Ϊ��ֹ��");
	else {
		dd=dd*10;
		printf("����Ϊ%d��",dd);
	}
	printf("\n");
	ff=str2int(ch,15,2);
	m=ff%10;
	n=ff/10;
	if(m<5)
		ff=n*10;
	else
		ff=(n+1)*10;
	ff=ff/10*10;
	printf("����Ϊ%d��/��",dd);
	printf("\n");
	n=18;
	if(ch[n]=='1') {
		printf("��������Ϊ��");
		switch(ch[n+1]) {
			case'0':
				printf(" ");
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
	printf("\n");
	if(ch[n]=='2') {
		printf("¶���¶�����Ϊ��");
		switch(ch[n+1]) {
			case'0':
				printf(" ");
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
	printf("\n");
	if(ch[n]=='3') {
		printf("��վ��ѹ����Ϊ:");
		x=str2int(ch,n+1,3);
		y=str2int(ch,n+4,1);
		printf("��վ��ѹΪ%d.%d����",x,y);
		n+=6;
	}
	printf("\n");
	if(ch[n]=='4') {
		printf("��ƽ����ѹ����Ϊ:");
		x=str2int(ch,n+1,3);
		y=str2int(ch,n+4,1);
		if (x<5)
			x=x+10;
		printf("��ѹֵΪ%d.%d����",x,y);
		n+=6;
	}
	printf("\n");
	if(ch[n]=='5') {
		printf("��ȥ��Сʱ��վ��ѹ�仯��Ϊ:");
		if (ch[n+1]>4)
			printf("����");
		else  printf("�½�");
		x=str2int(ch,n+2,2);
		y=str2int(ch,n+4,1);
		printf("%d.%d����",x,y);
		n+=6;
	}
	printf("\n");
	if(ch[n]=='6') {
		printf("��ȥ��Сʱ��ˮ�����ϣ�");
		x=str2int(ch,n+1,3);
		if (x==0)
			printf("��ˮ����");
		else if (x<=998)
			printf("��ˮ��Ϊ%d����",x);
		else if(x==990)
			printf("��ˮ��΢��");
		else if(x<=999)
			printf("��ˮ��Ϊ%d����",(x-990)/10);
		n+=6;
	}
	printf("\n");
	if(ch[n]=='7') {
		printf("�۲�ʱ�͹�ȥ��������������Ϊ��");
		ww=str2int(ch,n+1,2);
		if ((ww==00)||(ww==01)||(ww==02)||(ww==03))
			printf("�۲�ʱ����������");
		else if (ww==4)
			printf("�۲�ʱ��������Ϊ��");
		else if (ww==5)
			printf("�۲�ʱ��������Ϊ��");
		else if (ww<=9)
			printf("�۲�ʱ��������Ϊɳ��");
		else if (ww<=12)
			printf("�۲�ʱ��������Ϊ�ᡢǳ��");
		else if (ww==13)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww<=16)
			printf("�۲�ʱ��������Ϊ��ˮ");
		else if (ww==17)
			printf("�۲�ʱ��������Ϊ�ױ�");
		else if (ww==18)
			printf("�۲�ʱ��������Ϊ�");
		else if (ww==19)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww==20)
			printf("�۲�ʱ��������Ϊëë��");
		else if (ww==21)
			printf("�۲�ʱ��������Ϊ��");
		else if (ww==22)
			printf("�۲�ʱ��������Ϊѩ����ѩ");
		else if (ww==23)
			printf("�۲�ʱ��������Ϊ���ѩ");
		else if (ww==24)
			printf("�۲�ʱ��������Ϊ�ꡢ��ڡ");
		else if (ww==25)
			printf("�۲�ʱ��������Ϊ��ѩ");
		else if (ww==26)
			printf("�۲�ʱ��������Ϊ�����ѩ");
		else if (ww==27)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww==28)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww==29)
			printf("�۲�ʱ��������Ϊ�ױ�");
		else if (ww<=35)
			printf("�۲�ʱ��������Ϊɳ����");
		else if (ww<=39)
			printf("�۲�ʱ��������Ϊ��ѩ");
		else if (ww<=49)
			printf("�۲�ʱ��������ΪŨ��");
		else if (ww<=59)
			printf("�۲�ʱ��������ΪŨëë��");
		else if (ww<=61)
			printf("�۲�ʱ��������ΪС��");
		else if (ww<=63)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww<=65)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww<=67)
			printf("�۲�ʱ��������Ϊ��ڡ");
		else if (ww<=69)
			printf("�۲�ʱ��������Ϊ���꽵ˮ");
		else if (ww<=71)
			printf("�۲�ʱ��������ΪСѩ");
		else if (ww<=73)
			printf("�۲�ʱ��������Ϊ��ѩ");
		else if (ww<=75)
			printf("�۲�ʱ��������Ϊ��ѩ");
		else if (ww==76)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww==77)
			printf("�۲�ʱ��������Ϊ��ѩ");
		else if (ww==78)
			printf("�۲�ʱ��������Ϊѩ��");
		else if (ww==79)
			printf("�۲�ʱ��������Ϊ����");
		else if (ww==80)
			printf("�۲�ʱ��������ΪС����");
		else if (ww==81)
			printf("�۲�ʱ��������Ϊ������");
		else if (ww==82)
			printf("�۲�ʱ��������Ϊ������");
		else if (ww==83)
			printf("�۲�ʱ��������ΪС�������ѩ");
		else if (ww==84)
			printf("�۲�ʱ��������Ϊ���������ѩ");
		else if (ww==85)
			printf("�۲�ʱ��������ΪС��ѩ");
		else if (ww==86)
			printf("�۲�ʱ��������Ϊ�л����ѩ");
		else if (ww==87)
			printf("�۲�ʱ��������ΪС������");
		else if (ww==88)
			printf("�۲�ʱ��������Ϊ�л��������");
		else if (ww==89)
			printf("�۲�ʱ��������Ϊ�����");
		else if (ww==90)
			printf("�۲�ʱ��������Ϊ�л�ǿ����");
		else if (ww==91)
			printf("�۲�ʱ��������Ϊ�ױ���С��");
		else if (ww==92)
			printf("�۲�ʱ��������Ϊ�ױ�������");
		else if (ww==93)
			printf("�۲�ʱ��������Ϊ�ױ���Сѩ");
		else if (ww==94)
			printf("�۲�ʱ��������Ϊ�ױ����ѩ");
		else if (ww==95)
			printf("�۲�ʱ��������ΪС�ױ�����ѩ");
		else if (ww==96)
			printf("�۲�ʱ��������ΪС�ױ������");
		else if (ww==97)
			printf("�۲�ʱ��������Ϊ���ױ�����ѩ");
		else if (ww==98)
			printf("�۲�ʱ��������Ϊ�ױ���ɳ����");
		else if (ww==99)
			printf("�۲�ʱ��������Ϊ���ױ������");
		printf("\n");
		switch(ch[n+3]) {
			case'0':
				printf("��Ҫ��ȥ��Сʱ����������");
				break;
			case'3':
				printf("��Ҫ��ȥ��Сʱ��������Ϊɳ����");
				break;
			case'4':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ��");
				break;
			case'5':
				printf("��Ҫ��ȥ��Сʱ��������Ϊëë��");
				break;
			case'6':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ��������");
				break;
			case'7':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ���彵ˮ");
				break;
			case'8':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ����");
				break;
			case'9':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ�ױ�");
				break;
			default:
				printf("���ݴ���");
		}

		switch(ch[n+4]) {
			case'0':
				printf("��Ҫ��ȥ��Сʱ����������");
				break;
			case'3':
				printf("��Ҫ��ȥ��Сʱ��������Ϊɳ����");
				break;
			case'4':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ��");
				break;
			case'5':
				printf("��Ҫ��ȥ��Сʱ��������Ϊëë��");
				break;
			case'6':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ��������");
				break;
			case'7':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ���彵ˮ");
				break;
			case'8':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ����");
				break;
			case'9':
				printf("��Ҫ��ȥ��Сʱ��������Ϊ�ױ�");
				break;
			default:
				printf("���ݴ���");
		}
		n+=6;
	}
	printf("\n");
	if(ch[n]=='8') {
		printf("�Ƶ�����Ϊ��");
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
	printf("\n");
	if(ch[n]=='9') {
		x=str2int(ch,n+1,2);
		y=str2int(ch,n+3,2);
		printf("ʵ�ʹ۲�ʱ��Ϊ%dСʱ%d����",x,y);
		n+=6;
	}
	printf("\n");

}
//���ַ�������ch�������룬������߿ո����Ҫ�ص�ֵ������ʾ��
void updisp(char *ch) {
	//  ��ch�������룬��ѧ���������
	//puts(ch);  // ��ʾ�������ַ�����������
	int n,i,p,y,t,d,f;
	n=(ch[10]==' ')?11:12;
	y=str2int(ch,n-6,2);
	printf("��վ�� ��\n");
	for(i=0; i<5; i++)printf("%c",ch[n+i]);
	printf("\n");
	while(1) {
		n+=6;
		p=str2int(ch,n+2,3);
		if(ch[n]=='9'&&ch[n+1]=='9') {
			if(p<=100) printf("�����վ��ѹ��λ���ף�%d",(p+1000));
			else printf("�����վ��ѹ��λ���ף�%d",p);
		} else if(ch[n]=='0'&&ch[n+1]=='0') {
			if(p>500)p=500-p;
			printf("��ѹ1000hPaλ����:%d",p);
		} else if(ch[n]=='9'&&ch[n+1]=='2') {
			printf("925hPaλ���ף�%d",p);
		} else if(ch[n]=='8'&&ch[n+1]=='5')
			printf("850hPaλ���ף�%d",(p+1000));
		else if(ch[n]=='7'&&ch[n+1]=='0') {
			if(p>300) p+=2000;
			else p+=3000;
			printf("700hPaλ���ף�%d",p);
		} else if(ch[n]=='5'||ch[n]=='4'&&ch[n+1]=='0') {
			printf("500hPa��400hPa λ���ף�%d",p*10);
		} else if((ch[n]=='3'&&ch[n+1]=='0')||(ch[n]=='2'&&ch[n+1]=='5')) {
			if(p<500) p=(p+1000)*10;
			else p=p*10;
			printf("300hPa��250hPa λ���ף�%d",p);
		} else if((ch[n]=='2'&&ch[n+1]=='0')||(ch[n]=='1'&&ch[n+1]=='5')||(ch[n]=='1'&&ch[n+1]=='0'))
			printf("200hPa��150hPa��100hPa λ���ף�%d",(p+1000)*10);
		else break;
		printf("\n");
		n+=6;
		t=str2int(ch,n,3);
		if(t%2==0)printf("���£� ");
		else printf("���£�-");
		printf("%.1f��\n",p/10.0);
		d=str2int(ch,n+3,2);
		if(d>50) d=d-50;
		else d=d/10;
		printf("¶���¶Ȳ%d��\n",d);
		n+=6;
		d=str2int(ch,n,3);
		f=str2int(ch,n+3,2);
		if(d%5==0) printf("����%d",d);
		printf("\n");
		if(y>50) printf("���٣�%d��/��",f*0.5);
		else printf("���٣�%d��/��",f);
		printf("\n");
	}
}
}

