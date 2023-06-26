// ���̵����㷨.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//����ռʽ���������
#include <iostream>
using namespace std;
struct time
{
	int h; //Сʱ
	int m;  //����
};
typedef struct PCB
{
	int ID;						//���̺�(��ʶ�ţ�
	struct time refer_t;		//�ύʱ��
	int length;					//��Ҫִ��ʱ��
	struct time start_t;		//��ʼִ��ʱ��
	struct time end_t;			//���ʱ��	
	int		turnover_time;				//��תʱ��=���ʱ��-�ύʱ��
	double weight_turnover_time;					//��Ȩ��תʱ��=��תʱ��/ִ��ʱ��
	int state = 0;				//����״̬��0��ʾ�ȴ���1��ʾ����ִ�У�2��ʾ�Ѿ����
}PCB;
struct time  t;					//��ǰʱ��
double average_turnover = 0;           		//ƽ����תʱ��=���н��̵���תʱ����Խ��̵ĸ���
double average_weight_time = 0;					//ƽ����Ȩ��תʱ��
int n = 0;						//��������

//ʱ����Ӻ���(time +int )
struct time time_add(struct time t1, int t2)
{
	t1.m = t1.m + t2;
	if (t.m >= 60)
	{
		t.h++;
		t.m = t.m - 60;
	}
	return t1;
}
//ʱ��������� ���ط���
int time_m(struct time t1, struct time t2)
{
	int tmp;
	tmp = 60 * t1.h + t1.m - (60 * t2.h + t2.m);
	return tmp;
}

//�������̱�
void create(int* n, PCB*& p)
{
	cout << "��������̸��� n ��";
	cin >> *n;
	p = new PCB[*n];
	cout << *n << " �����̵Ľ��̺�:";
	for (int i = 0; i < *n; i++)
	{
		cin >> p[i].ID;
	}
	cout << *n << " �����̵��ύʱ��";
	for (int i = 0; i < *n; i++)
	{
		scanf(" %d %d", &p[i].refer_t.h, &p[i].refer_t.m);
	}

	cout << *n << " ��������Ҫ��ִ��ʱ��(��λ���ӣ�";
	for (int i = 0; i < *n; i++)
	{
		cin >> p[i].length;
	}
}


//ʱ�����
void out_time(struct time p)
{
	if (p.m >= 60)
	{
		p.h++;
		p.m = p.m - 60;
	}
	cout << p.h << ":" << p.m << "\t\t";
}

void out(int* n, PCB*& p)
{
	cout << endl << " ���̺�\t  �ύʱ��\t  ִ��ʱ��\t  ��ʼʱ��\t  ����ʱ��\t  ��תʱ��\t  ��Ȩ��תʱ��\t" << endl;
	for (int i = 0; i < *n; i++)
	{
		cout << p[i].ID << " \t\t";
		out_time(p[i].refer_t);
		cout << p[i].length << "\t\t";
		out_time(p[i].start_t);
		out_time(p[i].end_t);
		cout << p[i].turnover_time << "\t\t";
		cout << p[i].weight_turnover_time << "\t\t";
		cout << endl;
	}
	cout << "ƽ����תʱ��Ϊ��" << endl;
	cout << average_turnover << endl;
	cout << "ƽ����Ȩ��תʱ��Ϊ��" << endl;
	cout << average_weight_time << endl;

}

int refer_time_min_id(int n, PCB* p, struct time  t)
/*
* ���ύʱ��С�ڵ��ڵ�ǰʱ����δִ�й��Ľ������ҵ�ִ��ʱ����С�Ľ��̣����ؽ��̺�
*/
{
	int  id = 0;
	int  min = 10000;
	for (int i = 0; i < n; i++)
	{
		if (time_m(t, p[i].refer_t) >= 0 && p[i].state == 0)
		{
			if ((p[i].refer_t.h * 60 + p[i].refer_t.m) < min)
			{
				min = p[i].refer_t.h * 60 + p[i].refer_t.m;
				id = i;
			}
		}
	}
	return id;
}
void FCFS()
{
	/*
	* �����ȷ����㷨FCFS
	*  ��ʼִ��ʱ��=��ǰʱ��
	* ���ʱ��=��ʼʱ��+ִ��ʱ��
	* ��ǰʱ���ʼֵΪ��һ�����̵��ύʱ�䣬
	* ��תʱ��=���ʱ��-�ύʱ��
	*��Ȩ��תʱ��=��תʱ��/ִ��ʱ��
	*ִ����һ�����̵��ȣ���ǰʱ��+����ִ��ʱ��
	* ����״̬�ã�label)Ϊ1 
	*����ռģʽһ�ε���ִ����һ�����̣�
	*
	*/
	int n;
	PCB* p = NULL;
	create(&n, p);
	struct time t = p[0].refer_t;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	int i = 0;
	for (int i = 0;i < n;i++)//˳��ִ��
	{
		int id = refer_time_min_id(n, p, t);
		if (p[id].state == 0)
		{
			p[id].state = 1;
			p[id].start_t = t;																		// ��ʼʱ��
			p[id].end_t = time_add(t, p[id].length);													//���ʱ��
			p[id].turnover_time = 60 * (p[id].end_t.h - p[id].refer_t.h) + (p[id].end_t.m - p[id].refer_t.m);		//��תʱ��(��λ���ӣ�
			p[id].weight_turnover_time = double(p[id].turnover_time) / double(p[id].length);														//��Ȩ��תʱ��
			t = p[id].end_t;																			//���õ�ǰʱ��
			p[id].state = 2;																			////��״̬��2���ж�����ģ�����
		}
	}
	//����ƽ����תʱ���ƽ����Ȩ��תʱ��
	for (int i = 0; i < n; i++)
	{
		average_turnover += p[i].turnover_time;
		average_weight_time += p[i].weight_turnover_time;
	}
	average_turnover = double(average_turnover / n);
	average_weight_time = double(average_weight_time / n);
	out(&n, p);
	delete[] p;
}


int length_min_id(int n, PCB* p, struct time  t)
/*
* ���ύʱ��С�ڵ��ڵ�ǰʱ����δִ�й��Ľ������ҵ�ִ��ʱ����С�Ľ��̣����ؽ��̺�
*/
{
	int  id = 0;
	int  min = 10000;
	for (int i = 0; i < n; i++)
	{
		if (time_m(t, p[i].refer_t) >= 0 && p[i].state == 0)
		{
			if (p[i].length < min)
			{
				min = p[i].length;
				id = i;
			}
		}
	}
	return id;
}
void SJF()
/*
* �����ҵ�����㷨 SJF
* ����ִ��ʱ��
* ����Ҫ�����ύʱ���뵱ǰʱ��ıȽϣ����ύʱ��С�ڵ�ǰʱ��Ľ�����ȥ��ִ��ʱ����С�ģ�
*/
{  
	int n;
	PCB* p = NULL;
	create(&n, p);
	t = p[0].refer_t;																							// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	for (int i = 0; i < n; i++)
	{
		int id;
		id = length_min_id(n, p, t);
		p[id].state = 1;
		p[id].start_t = t;																						// ��ʼʱ��
		p[id].end_t = time_add(t, p[id].length);																//���ʱ��
		p[id].turnover_time = 60 * (p[id].end_t.h - p[id].refer_t.h) + (p[id].end_t.m - p[id].refer_t.m);		//��תʱ��(��λ���ӣ�
		p[id].weight_turnover_time = double(p[id].turnover_time) / double(p[id].length);							//��Ȩ��תʱ��
		t = p[id].end_t;
		p[id].state = 2;																						//��״̬��2ģ�����
	}
	for (int i = 0; i < n; i++)
	{
		average_turnover += p[i].turnover_time;
		average_weight_time += p[i].weight_turnover_time;
	}
	average_turnover = double(average_turnover / n);
	average_weight_time = double(average_weight_time / n);
	out(&n, p);
}

int main()
{
	cout << "�˵�" << endl;
	cout << "1.�����ȷ����㷨(FCFS)" << endl;
	cout << "2.�����ҵ�����㷨(SJF)" << endl;
	cout << "��ѡ��Ҫʵ�ֵ��㷨��";
	int ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		FCFS();
		break;
	case 2:
		SJF();
		break;
	}
	system("pause");
	return 0;
}

