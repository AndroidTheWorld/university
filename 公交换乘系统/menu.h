#ifndef MENU_H
#define MENU_H

using namespace std;

class menu
{
	public:
		menu();
		~menu();
		//��̬������ӡ�˵����� 
		static void print(vector<BusLine> lines); 
		//��̬���������û�ѡ�� 
		static void getchoice(vector<BusLine> lines);
	private:
		//�����·��Ϣ 
		vector<BusLine> lines;
};

#endif
