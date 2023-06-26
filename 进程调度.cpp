// 进程调度算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//非抢占式多道批处理
#include <iostream>
using namespace std;
struct time
{
	int h; //小时
	int m;  //分钟
};
typedef struct PCB
{
	int ID;						//进程号(标识号）
	struct time refer_t;		//提交时间
	int length;					//需要执行时间
	struct time start_t;		//开始执行时间
	struct time end_t;			//完成时间	
	int		turnover_time;				//周转时间=完成时间-提交时间
	double weight_turnover_time;					//带权周转时间=周转时间/执行时间
	int state = 0;				//进程状态，0表示等待，1表示真正执行，2表示已经完成
}PCB;
struct time  t;					//当前时间
double average_turnover = 0;           		//平均周转时间=所有进程的周转时间除以进程的个数
double average_weight_time = 0;					//平均带权周转时间
int n = 0;						//进程数量

//时间相加函数(time +int )
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
//时间相减函数 返回分钟
int time_m(struct time t1, struct time t2)
{
	int tmp;
	tmp = 60 * t1.h + t1.m - (60 * t2.h + t2.m);
	return tmp;
}

//创建进程表
void create(int* n, PCB*& p)
{
	cout << "请输入进程个数 n ：";
	cin >> *n;
	p = new PCB[*n];
	cout << *n << " 个进程的进程号:";
	for (int i = 0; i < *n; i++)
	{
		cin >> p[i].ID;
	}
	cout << *n << " 个进程的提交时间";
	for (int i = 0; i < *n; i++)
	{
		scanf(" %d %d", &p[i].refer_t.h, &p[i].refer_t.m);
	}

	cout << *n << " 个进程需要的执行时间(单位分钟）";
	for (int i = 0; i < *n; i++)
	{
		cin >> p[i].length;
	}
}


//时间输出
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
	cout << endl << " 进程号\t  提交时间\t  执行时间\t  开始时间\t  结束时间\t  周转时间\t  带权周转时间\t" << endl;
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
	cout << "平均周转时间为：" << endl;
	cout << average_turnover << endl;
	cout << "平均带权周转时间为：" << endl;
	cout << average_weight_time << endl;

}

int refer_time_min_id(int n, PCB* p, struct time  t)
/*
* 在提交时间小于等于当前时间且未执行过的进程中找到执行时间最小的进程，返回进程号
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
	* 先来先服务算法FCFS
	*  开始执行时间=当前时间
	* 完成时间=开始时间+执行时间
	* 当前时间初始值为第一个进程的提交时间，
	* 周转时间=完成时间-提交时间
	*带权周转时间=周转时间/执行时间
	*执行完一个进程调度，当前时间+进程执行时间
	* 进程状态置（label)为1 
	*非抢占模式一次调度执行完一个进程，
	*
	*/
	int n;
	PCB* p = NULL;
	create(&n, p);
	struct time t = p[0].refer_t;	// 当前时刻, 初始化为第一个进程的开始时刻
	int i = 0;
	for (int i = 0;i < n;i++)//顺序执行
	{
		int id = refer_time_min_id(n, p, t);
		if (p[id].state == 0)
		{
			p[id].state = 1;
			p[id].start_t = t;																		// 开始时间
			p[id].end_t = time_add(t, p[id].length);													//完成时间
			p[id].turnover_time = 60 * (p[id].end_t.h - p[id].refer_t.h) + (p[id].end_t.m - p[id].refer_t.m);		//周转时间(单位分钟）
			p[id].weight_turnover_time = double(p[id].turnover_time) / double(p[id].length);														//带权周转时间
			t = p[id].end_t;																			//设置当前时间
			p[id].state = 2;																			////用状态置2加判断条件模拟出队
		}
	}
	//计算平均周转时间和平均带权周转时间
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
* 在提交时间小于等于当前时间且未执行过的进程中找到执行时间最小的进程，返回进程号
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
* 最短作业优先算法 SJF
* 考虑执行时间
* 另外要考虑提交时间与当前时间的比较，再提交时间小于当前时间的进程中去找执行时间最小的；
*/
{  
	int n;
	PCB* p = NULL;
	create(&n, p);
	t = p[0].refer_t;																							// 当前时刻, 初始化为第一个进程的开始时刻
	for (int i = 0; i < n; i++)
	{
		int id;
		id = length_min_id(n, p, t);
		p[id].state = 1;
		p[id].start_t = t;																						// 开始时间
		p[id].end_t = time_add(t, p[id].length);																//完成时间
		p[id].turnover_time = 60 * (p[id].end_t.h - p[id].refer_t.h) + (p[id].end_t.m - p[id].refer_t.m);		//周转时间(单位分钟）
		p[id].weight_turnover_time = double(p[id].turnover_time) / double(p[id].length);							//带权周转时间
		t = p[id].end_t;
		p[id].state = 2;																						//用状态置2模拟出队
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
	cout << "菜单" << endl;
	cout << "1.先来先服务算法(FCFS)" << endl;
	cout << "2.最短作业优先算法(SJF)" << endl;
	cout << "请选择要实现的算法：";
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

