//�ڴʷ������Ļ�����ʵ���﷨����������Ϊ��Ԫ����������Ƿ����﷨����,�д���Ļ��������λ��
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
//���� �Ӻ���
int n;//�к�
int c;//�ֱ���
char s[10];
void program(FILE* fp);//����
void statement_block(FILE* fp);//����
void statement_string(FILE* fp);//��䴮����
void statement(FILE* fp);//��亯��
void condition(FILE* fp);//����
void expression(FILE* fp);//���ʽ
void item(FILE* fp);//��
void relational(FILE* fp);//��ϵ�����
void factor(FILE* fp);//����

void program(FILE* fp)
{
    fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
    if (c != 1)//���ʱ�����ء�0������ִ�и���䣬
    {
        printf("��%d�С�%s��ǰȱ��    ��main��\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
    if (c != 26)
    {
        printf("��%d�С�%s��ǰȱ  ��  ��(��\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
    if (c != 27)
    {
        printf("��%d�С�%s��ǰȱ  ��  ��)��\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���

    statement_block(fp);
}
void statement_block(FILE* fp)//����
{

    if (c != 28)
    {
        printf("��%d�С�%s��ǰȱ  ��  ��{��\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
    statement_string(fp);//��䴮

    if (c != 29)
    {
        printf("��%d�С�%s��ǰ ȱ �١�}��\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
}

void statement_string(FILE* fp)//��䴮����
{
    statement(fp);
    while (1) {
        if (c == 29) return;
        if (c != 31)
        {
            printf("��%d�С�%s��ǰȱ  ��  ��;��\n",n,s);
        }
        else  fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
        statement(fp);

    }
    fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
    if (c != 31)
    {
        printf("��%d��%sǰȱ �� ��;��\n",n,s);
    }
}

void statement(FILE* fp)//��亯��
{
    if (c == 10)//��ֵ���
    {
        fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
        if (c != 21)
        {
            printf("��%d�С�%s��ȱ  �١�=��\n",n,s);
        }
        else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
        expression(fp);
    }
    else if (c == 4 || c == 6)//���������ж�ѭ�����
    {
        fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
        if (c != 26)
        {
            printf("��%d�С�%s��ȱ  �١�(��\n",n,s);
        }
        else  fscanf(fp, "%d,%d,%s  ", &n, &c, &s);
        condition(fp);
        if (c != 27)
        {
            printf("��%d�С�%s��ǰ ȱ �١�)��\n",n,s);
        }
        else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);
        statement_block(fp);

    }
}

void condition(FILE* fp)//����
//����
{
    expression(fp);
    relational(fp);
    expression(fp);
}
void expression(FILE* fp)//���ʽ
{
    item(fp);
    while (c == 22 || c == 23)
    {
        item(fp);
    }
}
void item(FILE* fp)//��
{
    factor(fp);
    while (c == 24 || c == 25)
    {
        factor(fp);
    }
}
void factor(FILE* fp)//����
{
    if (c == 26)
    {
        expression(fp);
        fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
        if (c != 27)
        {
            printf("��%d�С�%s��ȱ  �١�)��\n",n,s);
        }
        else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
    }
    if (c != 10 && c != 20)
    {
        printf("��%d�С�%s��ǰȱ �� ���������ӡ�\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
}
void relational(FILE* fp)//��ϵ�����
{
    if (c < 32)
    {
        printf("��%d�С�%s��ǰȱ �� ����ϵ�������\n",n,s);
    }
    else fscanf(fp, "%d,%d,%s  ", &n, &c, &s);//nΪҳ�룬cΪ�ֱ���
}

int main()
{
    FILE* fp, * fr;
    fopen_s(&fp, "F:\\c.txt", "r");//�ʷ�����������ļ�
    if (fp == NULL)
    {
        cout << "��ȡ�ļ�ʧ��";
    }
    char token[10];
    cout << "�����ʽ:���n��sǰȱ��;(���s�ǵ�n�еĵ�һ���ַ������������һ�н�β):\n";
    program(fp);
    cout << "�﷨�������";
    cout << endl;
    system("pause");
}