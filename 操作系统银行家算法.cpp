
//避免死锁算法，银行家算法
#include <iostream>
using namespace std;
#define p 5 //进程数量
#define r 4 //资源种类数量

int ID[p] = { 0, 1, 2, 3, 4 };                                                                   //进程号
int Available[r] = { 1, 6, 2, 2 };                                                               //可用资源向量
int Allocation[p][r] = { {0, 0, 3, 2}, {1, 0, 0, 0}, {1, 3, 5, 4}, {0, 3, 3, 2}, {0, 0, 1, 4} }; //每个进程的分配资源
int Need[p][r] = { {0, 0, 1, 2}, {1, 7, 5, 0}, {2, 3, 5, 6}, {0, 6, 5, 2}, {0, 6, 5, 6} };       //每个进程还需要的资源数
int Work[r];                                                                                   //系统可用资源
int Request[p][r] = { 0 };
void out();//输出当前状态
bool is_safe();//安全性算法
int bank(int i, int Request[][r]);//银行家算法
void out() //输出当前状态
{
    cout << "当前状态:" << endl;
    cout << "Process" << '\t' << "Allpcation" << '\t' << "Need" << "\t" << "Available" << endl;
    for (int i = 0; i < p; i++)
    {
        cout << ID[i];
        cout << '\t';
        for (int j = 0; j < r; j++)
        {
            cout << Allocation[i][j] << ' ';
        }
        cout << '\t';
        for (int j = 0; j < r; j++)
        {
            cout << Need[i][j] << ' ';
        }
        cout << '\t';
        if (i == 0)
        {
            for (int i = 0; i < r; i++)
                cout << Available[i] << ' ';
        }
        cout << endl;
    }
}
bool is_safe()
{
    int i, j;
    int n = 0;
    int m = 0;
    int Finish[p] = { 0 };
    int Work[r];                //系统当前可用资源数
    int list[p];                //存储执行序列
    for (int i = 0; i < r; i++) //将可用资源数目赋给工作向量Work
        Work[i] = Available[i];
    for (i = 0; i < p; i++)
    {
        if (Finish[i] == 1) //工作向量等于1,进程已经执行，跳过
            continue;
        else
        {
            for (j = 0; j < r; j++)
            {
                if (Need[i][j] > Work[j])
                    break;
            }
            if (j == r) // j=r表示四个资源的need都小于work
            {
                Finish[i] = 1;
                for (int k = 0; k < r; k++)
                    Work[k] = Work[k] + Allocation[i][k]; //直至完成，并释放出分配给它的资源，故应执行可提供资源数量更新
                list[n++] = i;                            //存储执行次序
                i = -1;
            }
        }
    }
    for (int i = 0; i < p; i++)
    {
        if (Finish[i])
            m++;
    }
    if (m == p)
    {
        cout << "该状态是安全的,可行的执行序列：" << endl;
        for (int i = 0; i < p; i++)
            cout << list[i] << "，";
        cout << endl;
        return 1;
    }
    else
    {
        cout << "该状态不安全,";
        return 0;
    }
}
//银行家算法
int bank(int i, int Request[][r])
{
    for (int j = 0; j < r; j++)
    { //请求资源数不能大于最大需求数，也不能大于当前可用资源数
        if (Request[i][j] > Need[i][j])
        {
            cout << "请求资源数大于宣布的最大值" << endl;
            return 0;
        }
        else if (Request[i][j] > Available[j])
        {
            cout << "资源不足,p[" << i << "]需等待!" << endl;
            return 0;
        }
    }
    //没有上述两种情况，分配资源
    for (int j = 0; j < r; j++)
    {
        Available[j] = Available[j] - Request[i][j];
        Allocation[i][j] = Allocation[i][j] + Request[i][j];
        Need[i][j] = Need[i][j] - Request[i][j];
    }

    //执行安全性算法
    out();
    bool n = is_safe();
    if (n)
    { //该状态是安全的，分配成功
        cout << "可以将分配资源给"
            << "P[" << i << "]!" << endl;
    }
    else //不安全，分配失败，返回分配前状态
    {
        for (int j = 0; j < r; j++)
        {
            Available[j] = Available[j] + Request[i][j];
            Allocation[i][j] = Allocation[i][j] - Request[i][j];
            Need[i][j] = Need[i][j] + Request[i][j];
        }
        cout << "系统不能 将资源分配给"<< "P[" << i << "]!" << endl;
    }
    return n;
}

int main()
{

    out();
    int i;
    is_safe();
    cout << "输入请求的进程:";
    cin >> i;
    cout << "输入请求的资源数:";
    for (int j = 0; j < r; j++)
    {
        cin >> Request[i][j];
    }
    bank(i, Request);
    system("pause");
}
