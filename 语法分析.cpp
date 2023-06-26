//在词法分析的基础上实现语法分析，输入为二元组序列输出是否有语法错误,有错误的话输出错误位置
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
//程序 子函数
int n;//行号
int c;//种别码
char s[10];
void program(FILE* fp);//程序
void statement_block(FILE* fp);//语句块
void statement_string(FILE* fp);//语句串函数
void statement(FILE* fp);//语句函数
void condition(FILE* fp);//条件
void expression(FILE* fp);//表达式
void item(FILE* fp);//项
void relational(FILE* fp);//关系运算符
void factor(FILE* fp);//因子

void program(FILE* fp)
{
    fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
    if (c != 1)//相等时，返回“0”，不执行该语句，
    {
        printf("第%d行【%s】前缺少    【main】\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
    if (c != 26)
    {
        printf("第%d行【%s】前缺  少  【(】\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
    if (c != 27)
    {
        printf("第%d行【%s】前缺  少  【)】\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码

    statement_block(fp);
}
void statement_block(FILE* fp)//语句块
{

    if (c != 28)
    {
        printf("第%d行【%s】前缺  少  【{】\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
    statement_string(fp);//语句串

    if (c != 29)
    {
        printf("第%d行【%s】前 缺 少【}】\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
}

void statement_string(FILE* fp)//语句串函数
{
    statement(fp);
    while (1) {
        if (c == 29) return;
        if (c != 31)
        {
            printf("第%d行【%s】前缺  少  【;】\n",n,s);
        }
        else  fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
        statement(fp);

    }
    fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
    if (c != 31)
    {
        printf("第%d行%s前缺 少 【;】\n",n,s);
    }
}

void statement(FILE* fp)//语句函数
{
    if (c == 10)//赋值语句
    {
        fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
        if (c != 21)
        {
            printf("第%d行【%s】缺  少【=】\n",n,s);
        }
        else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
        expression(fp);
    }
    else if (c == 4 || c == 6)//条件语句和判断循环语句
    {
        fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
        if (c != 26)
        {
            printf("第%d行【%s】缺  少【(】\n",n,s);
        }
        else  fscanf(fp, "%d,%d,%s  ", &n, &c, &s);
        condition(fp);
        if (c != 27)
        {
            printf("第%d行【%s】前 缺 少【)】\n",n,s);
        }
        else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);
        statement_block(fp);

    }
}

void condition(FILE* fp)//条件
//条件
{
    expression(fp);
    relational(fp);
    expression(fp);
}
void expression(FILE* fp)//表达式
{
    item(fp);
    while (c == 22 || c == 23)
    {
        item(fp);
    }
}
void item(FILE* fp)//项
{
    factor(fp);
    while (c == 24 || c == 25)
    {
        factor(fp);
    }
}
void factor(FILE* fp)//因子
{
    if (c == 26)
    {
        expression(fp);
        fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
        if (c != 27)
        {
            printf("第%d行【%s】缺  少【)】\n",n,s);
        }
        else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
    }
    if (c != 10 && c != 20)
    {
        printf("第%d行【%s】前缺 少 【运算因子】\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
}
void relational(FILE* fp)//关系运算符
{
    if (c < 32)
    {
        printf("第%d行【%s】前缺 少 【关系运算符】\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//n为页码，c为种别码
}

int main()
{
    FILE* fp, * fr;
    fopen_s(&fp, "F:\\c.txt", "r");//词法分析的输出文件
    if (fp == NULL)
    {
        cout << "读取文件失败";
    }
    char token[10];
    cout << "报错格式:如第n行s前缺少;(如果s是第n行的第一个字符串则错误在上一行结尾):\n";
    program(fp);
    cout << "语法分析完成";
    cout << endl;
    system("pause");
}