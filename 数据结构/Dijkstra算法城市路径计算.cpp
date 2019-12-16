#include<iostream>
#include<vector>
#include<string>

using namespace std;

#define MaxVertexNum 100

int main() {
	char pause = '\n';
	cout<<"----------------�������·��-----------------\n";

	cout<<"--------------------------------���س�������-----------------------------------\n";

	cin.get(pause);
	cout<< "--------------------------------1 - ֱ����'�Ͼ�', '����', '����', '�Ϻ�', '���Ƹ�', '����'(Ĭ��Ϊ���Ͼ�������Ϊһ��ͨ·��ÿ��·�����ȶ�Ϊ1) ��ֱ�ӳ�ʼ��-----------------\n";

	cout<< "--------------------------------2 - �Զ����ʼ��-----------------\n";
	vector<string> citymin;
	int choice;
	vector<string> citytest = { "�Ͼ�", "����", "����", "�Ϻ�", "���Ƹ�", "����" };
	cout << endl;
	cin >> choice;

	typedef string VertexType;//�������������
	typedef int EdgeType;//��Ȩͼ�б���Ȩֵ����������
	typedef struct {
		vector<VertexType> Vex;//�����
		EdgeType Edge[MaxVertexNum][MaxVertexNum];//�ڽӾ��󣬱߱�
		int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���

	} MGragh;
	MGragh A;
	if (choice == 1) {
		for (int i = 0; i < MaxVertexNum; i++)
			for (int j = 0; j < MaxVertexNum; j++)
				A.Edge[i][j] = 65536;
		for (int i = 0; i < citytest.size(); i++)
			for (int j = 0; j <citytest.size(); j++) {
				if (i == j - 1) {
					A.Edge[i][j] = 1;
				}
			}
		for (int i = 0; i < citytest.size(); i++) {
			A.Vex.push_back(citytest[i]);
		}
		int p = citytest.size();
		A.vexnum = 6;
		A.arcnum = 5;

	}
	if (choice == 2) {
		for (int i = 0; i < MaxVertexNum; i++)
			for (int j = 0; j < MaxVertexNum; j++)
				A.Edge[i][j] = 65536;
		int  e;
		string city, city1, city2;
		int num = 0;
		cout << "����������е����ƣ�ÿһ�λس�������������һ�γ��У���һ������ĳ���Ĭ��ΪԴ�㣬���г������������������\"ֹͣ\"�������룩��";
		cin >> city;
		A.Vex.push_back(city);
		while (city != "ֹͣ") {
			cin >> city;
			num++;
			A.Vex.push_back(city);
			A.vexnum = num + 1;
		}
		cout << "������һ��int����������ͼ֮��ı�����";
		cin >> e;
		A.arcnum = e;

		cout << "�����������������ƺ�һ��int����������������Щ��������������֮�䣨�ߵķ���Ϊ���򣬴�ǰһ����ָ���һ�������Ҹ�����߼���Ȩֵ��";
		for (int i = 0; i < A.arcnum; i++) {
			int o, p, q;
			cin >> city1;
			cin >> city2;
			cin >> q;
			for (int i = 0; i < A.vexnum; i++) {
				if (A.Vex[i] == city1)
					o = i;
			}
			for (int i = 0; i < A.vexnum; i++) {
				if (A.Vex[i] == city2)
					p = i;
			}
			A.Edge[o][p] = q;
		}
	}
	string choice2;
	cout << "�Ƿ���ı���������Լ���Ӧ��·��������'YES'����ı�ģʽ������'NO'��ֱ�ӽ������";
	cout << endl;
	cin >> choice2;
	cout << endl;
	if (choice2 == "YES") {
		int choice3;
		cout << "���ȼ��ٳ��У�����0���룬�ٴ�����0�������٣������ӽ׶�(���ٳ��к󣬳��е�·Ҳ��֮ɾȥ���ɽ����޸�·���׶��޸�),����2�����޸�·���׶�";
		cout << endl;
		cin >> choice3;
		if (choice3 == 0) {
			string citymin1;
			int temp;
			cout << "����������Ҫɾ�����ٳ��У�����0������";
			cin >> temp;
			cout << endl;
			cout << "��������Ҫɾ���ĳ��У�ÿ����һ����һ���س���ʾ������ϣ���";
			for (int i = 0; i < temp; i++) {
				cin >> citymin1;
				citymin.push_back(citymin1);
				for (int i = 0; i < A.vexnum; i++) {
					if (A.Vex[i] == citymin1) {
						for (int k = 0; k < MaxVertexNum; k++)
							for (int j = 0; j < MaxVertexNum; j++)
								if (j == i || k == i) {
									A.Edge[j][k] = 65536;
								}
					}
				}
			}

			cout << "���������ٽ������ֽ���������ӽ׶�";
			cout << endl;
			int temp2;
			cout << "�������������Ӷ��ٳ��У�����0������";
			cin >> temp2;
			cout << endl;
			cout << "��������Ҫ���ӵĳ��У�ÿ����һ����һ���س���ʾ������ϣ���";
			cout << endl;
			for (int i = 0; i < temp2; i++) {
				string citymax;
				cin >> citymax;
				A.Vex.push_back(citymax);
				A.vexnum += 1;
			}
			cout << "�������޸Ľ��������ڽ���·���������Լ��޸Ľ׶�,��������ı�·��������������0��������";
			cout << endl;
			int temp3;
			cin >> temp3;
			cout << endl;
			cout << "�����������������ƺ�һ��int�����������޸�·��";
			cout << endl;
			for (int i = 0; i < temp3; i++) {
				string city7;
				string city8;
				int u, l, m;
				cin >> city7;
				cin >> city8;
				cin >> m;
				cout << endl;
				for (int i = 0; i < A.vexnum; i++) {
					if (A.Vex[i] == city7)
						u = i;
				}
				for (int i = 0; i < A.vexnum; i++) {
					if (A.Vex[i] == city8)
						l = i;
				}
				A.Edge[u][l] = m;


			}
		}
		if (choice3 == 2) {
			int temp3;

			cout << "����������Ҫ�ı������·��";
			cin >> temp3;
			cout << endl;
			cout << "�����������������ƺ�һ��int�����������޸�·��";
			cout << endl;
			for (int i = 0; i < temp3; i++) {
				string city7;
				string city8;
				int u, l, m;
				cin >> city7;
				cin >> city8;
				cin >> m;
				for (int i = 0; i < A.vexnum; i++) {
					if (A.Vex[i] == city7)
						u = i;
				}
				for (int i = 0; i < A.vexnum; i++) {
					if (A.Vex[i] == city8)
						l = i;
				}
				A.Edge[u][l] = m;


			}


		}

	}

	int s[100];
	for (int i = 0; i < 100; i++) {
		s[i] = 65536;
	}

	int dist[100], min = 65536;
	for (int i = 0; i < 100; i++) {
		dist[i] = A.Edge[0][i];
	}

	int count = 0;
	vector<int> T;
	T.push_back(0);
	while (count < A.vexnum - 1) {
		int temper[100];
		for (int i = 0; i < 100; i++) {
			temper[i] = dist[i];
		}
		for (int i = 0; i < 100; i++) {
			if (s[i] == i) {
				temper[i] = 65536;
			}
		}
		int j;
		for (int i = 0; i < A.vexnum; i++) {
			if (temper[i + 1] < temper[i]) {
				min = temper[i + 1];
			}
		}

		for (int i = 0; i < A.vexnum; i++) {
			if (dist[i] == min) {
				s[i] = i;
				j = i;
			}

		}

		for (int k = 0; k < A.vexnum; k++) {
			if (dist[j] + A.Edge[j][k] < dist[k]) {
				dist[k] = dist[j] + A.Edge[j][k];
				T.push_back(j);
			}
		}
		count += 1;
	}

	string citytest1;
	cout << "Դ��Ĭ��Ϊ��һ������ĳ��У�����������һ�����У������Դ�㵽������·����";
	cin >> citytest1;
	cout << endl;
	int tes;
	for (int i = 0; i <A.vexnum; i++) {
		if (A.Vex[i] == citytest1) {
			cout << "Դ�㵽�ó��е����·������Ϊ��";
			cout << dist[i];
			cout << endl;
			cout << "���������65536����˵��û�е��˳��е�·.";
			cout << endl;
			tes = i;
		}
	}
	cout << "������·��Ϊ�� ";
	for (int i = 0; i < tes; i++) {
		cout << A.Vex[T[i]];
		cout << "��";
	}
	cout << citytest1;
	cout << endl;


}



